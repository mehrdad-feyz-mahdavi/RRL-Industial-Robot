#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from std_msgs.msg import String, Bool
from geometry_msgs.msg import PoseStamped
import json
import time
import socket
import threading
import yaml
import os
from ament_index_python.packages import get_package_share_directory

class RefereeBoxNode(Node):
    def __init__(self):
        super().__init__('referee_box')
        
        # Load configuration
        self.load_configuration()
        
        # Game state
        self.game_state = "INITIAL"
        self.match_time = 0.0
        self.score = 0
        self.emergency_stop = False
        
        # Communication setup
        self.tcp_server = None
        self.connected_robots = {}
        self.setup_communication()
        
        # Publishers
        self.state_pub = self.create_publisher(String, '/referee/state', 10)
        self.score_pub = self.create_publisher(String, '/referee/score', 10)
        self.emergency_pub = self.create_publisher(Bool, '/referee/emergency', 10)
        
        # Subscribers
        self.create_subscription(PoseStamped, '/robot/pose', self.robot_pose_callback, 10)
        self.create_subscription(String, '/robot/status', self.robot_status_callback, 10)
        
        # Timer for game loop
        self.timer = self.create_timer(0.1, self.game_loop)
        
        self.get_logger().info('Referee Box initialized')

    def load_configuration(self):
        """Load configuration from YAML file"""
        config_path = os.path.join(
            get_package_share_directory('referee_box'),
            'referee_box',
            'config',
            'referee_config.yaml'
        )
        with open(config_path, 'r') as file:
            self.config = yaml.safe_load(file)
        
        # Extract communication parameters
        self.ip_address = self.config['communication']['ip_address']
        self.port = self.config['communication']['tcp_port']
        self.max_connections = self.config['communication']['max_connections']
        self.heartbeat_interval = self.config['communication']['heartbeat_interval']
        self.connection_timeout = self.config['communication']['connection_timeout']

    def setup_communication(self):
        """Setup TCP server for robot communication"""
        try:
            self.tcp_server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.tcp_server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.tcp_server.bind((self.ip_address, self.port))
            self.tcp_server.listen(self.max_connections)
            self.get_logger().info(f'Referee Box listening on {self.ip_address}:{self.port}')
            threading.Thread(target=self.accept_connections, daemon=True).start()
        except Exception as e:
            self.get_logger().error(f'Failed to setup communication: {e}')
            raise

    def accept_connections(self):
        """Accept incoming robot connections"""
        while True:
            try:
                client, addr = self.tcp_server.accept()
                if len(self.connected_robots) >= self.max_connections:
                    self.get_logger().warn(f'Connection limit reached. Rejecting connection from {addr}')
                    client.close()
                    continue
                
                self.get_logger().info(f'New connection from {addr}')
                threading.Thread(target=self.handle_robot_connection, args=(client, addr), daemon=True).start()
            except Exception as e:
                self.get_logger().error(f'Error accepting connection: {e}')

    def handle_robot_connection(self, client, addr):
        """Handle communication with a single robot"""
        robot_id = None
        try:
            while True:
                data = client.recv(1024)
                if not data:
                    break
                message = json.loads(data.decode())
                self.process_robot_message(message)
                
                # Update last communication time
                if robot_id in self.connected_robots:
                    self.connected_robots[robot_id]['last_update'] = time.time()
                
                # Send heartbeat response
                response = {'type': 'HEARTBEAT_RESPONSE', 'timestamp': time.time()}
                client.send(json.dumps(response).encode())
                
        except Exception as e:
            self.get_logger().error(f'Error handling robot connection from {addr}: {e}')
        finally:
            if robot_id in self.connected_robots:
                del self.connected_robots[robot_id]
            client.close()
            self.get_logger().info(f'Connection closed for robot {robot_id}')

    def process_robot_message(self, message):
        """Process messages from robots"""
        msg_type = message.get('type')
        if msg_type == 'REGISTER':
            self.handle_robot_registration(message)
        elif msg_type == 'STATUS':
            self.handle_robot_status(message)
        elif msg_type == 'TASK_COMPLETE':
            self.handle_task_completion(message)
        elif msg_type == 'HEARTBEAT':
            self.handle_heartbeat(message)

    def handle_heartbeat(self, message):
        """Handle heartbeat messages"""
        robot_id = message.get('robot_id')
        if robot_id in self.connected_robots:
            self.connected_robots[robot_id]['last_heartbeat'] = time.time()

    def handle_robot_registration(self, message):
        """Handle robot registration"""
        robot_id = message.get('robot_id')
        if robot_id:
            self.connected_robots[robot_id] = {
                'status': 'REGISTERED',
                'last_update': time.time(),
                'last_heartbeat': time.time()
            }
            self.get_logger().info(f'Robot {robot_id} registered')

    def handle_robot_status(self, message):
        """Handle robot status updates"""
        robot_id = message.get('robot_id')
        if robot_id in self.connected_robots:
            self.connected_robots[robot_id]['status'] = message.get('status')
            self.connected_robots[robot_id]['last_update'] = time.time()

    def handle_task_completion(self, message):
        """Handle task completion notifications"""
        robot_id = message.get('robot_id')
        task_id = message.get('task_id')
        if robot_id in self.connected_robots:
            self.score += self.calculate_task_points(task_id)
            self.publish_score()

    def robot_pose_callback(self, msg):
        """Handle robot pose updates"""
        # Check for collisions and workspace boundaries
        self.check_safety_violations(msg)

    def robot_status_callback(self, msg):
        """Handle robot status updates"""
        # Process robot status messages
        pass

    def check_safety_violations(self, pose):
        """Check for safety violations"""
        # Implement safety checks here
        if self.is_collision_detected(pose):
            self.trigger_emergency_stop()

    def is_collision_detected(self, pose):
        """Check for collisions"""
        # Implement collision detection logic
        return False

    def trigger_emergency_stop(self):
        """Trigger emergency stop"""
        self.emergency_stop = True
        msg = Bool()
        msg.data = True
        self.emergency_pub.publish(msg)
        self.get_logger().warn('Emergency stop triggered')

    def calculate_task_points(self, task_id):
        """Calculate points for completed task"""
        # Implement scoring logic
        return 10

    def publish_score(self):
        """Publish current score"""
        msg = String()
        msg.data = json.dumps({'score': self.score})
        self.score_pub.publish(msg)

    def game_loop(self):
        """Main game loop"""
        if self.game_state == "INITIAL":
            self.initialize_game()
        elif self.game_state == "RUNNING":
            self.run_game()
        elif self.game_state == "FINISHED":
            self.finish_game()

    def initialize_game(self):
        """Initialize the game"""
        if len(self.connected_robots) >= 1:  # Minimum required robots
            self.game_state = "RUNNING"
            self.match_time = 0.0
            self.score = 0
            self.publish_game_state()

    def run_game(self):
        """Run the game"""
        self.match_time += 0.1
        if self.match_time >= 300:  # 5 minutes match
            self.game_state = "FINISHED"
        self.publish_game_state()

    def finish_game(self):
        """Finish the game"""
        self.publish_final_score()
        self.get_logger().info('Game finished')

    def publish_game_state(self):
        """Publish current game state"""
        msg = String()
        msg.data = json.dumps({
            'state': self.game_state,
            'time': self.match_time,
            'score': self.score
        })
        self.state_pub.publish(msg)

    def publish_final_score(self):
        """Publish final score"""
        msg = String()
        msg.data = json.dumps({
            'final_score': self.score,
            'match_time': self.match_time
        })
        self.score_pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = RefereeBoxNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 