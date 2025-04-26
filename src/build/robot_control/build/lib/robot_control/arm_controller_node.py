import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy
import socket
import time
from zeroconf import ServiceInfo, Zeroconf
import threading
from sensor_msgs.msg import JointState
from robot_control_interfaces.msg import ArmCommand
from robot_control_interfaces.srv import ArmPreset
from std_srvs.srv import Trigger

class ArmControllerNode(Node):
    def __init__(self):
        super().__init__('arm_controller')
        
        # Declare parameters
        self.declare_parameters(
            namespace='',
            parameters=[
                ('server_ip', '192.168.160.71'),
                ('server_port', 4000),
                ('server_name', 'laptop.local'),
                ('default_speed', 30),
                ('default_claw_speed', 30),
                ('joint1_min', 0),
                ('joint1_max', 1023),
                ('joint2_min', 0),
                ('joint2_max', 1023),
                ('joint3_min', 0),
                ('joint3_max', 1023),
                ('base_min', 0),
                ('base_max', 500),
                ('gripper_rotate_min', 0),
                ('gripper_rotate_max', 270),
                ('gripper_claw_min', 0),
                ('gripper_claw_max', 180),
            ]
        )
        
        # Get parameters
        self.server_ip = self.get_parameter('server_ip').value
        self.server_port = self.get_parameter('server_port').value
        self.server_name = self.get_parameter('server_name').value
        self.default_speed = self.get_parameter('default_speed').value
        self.default_claw_speed = self.get_parameter('default_claw_speed').value
        
        # Initialize state variables
        self.client_socket = None
        self.zeroconf = None
        self.joint1 = 300
        self.joint2 = 300
        self.joint3 = 500
        self.base_angle = 0
        self.gripper_rotate = 90
        self.gripper_claw = 0
        self.running = True
        
        # Create QoS profile
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=10
        )
        
        # Create publishers
        self.joint_state_pub = self.create_publisher(
            JointState,
            'arm_joint_states',
            qos_profile
        )
        
        # Create subscribers
        self.command_sub = self.create_subscription(
            ArmCommand,
            'arm_commands',
            self.command_callback,
            qos_profile
        )
        
        # Create services
        self.preset_service = self.create_service(
            ArmPreset,
            'set_arm_position',
            self.preset_callback
        )
        
        self.emergency_stop_service = self.create_service(
            Trigger,
            'emergency_stop',
            self.emergency_stop_callback
        )
        
        # Start mDNS service
        self.start_mdns_service()
        
        # Start server thread
        self.server_thread = threading.Thread(target=self.run_server)
        self.server_thread.daemon = True
        self.server_thread.start()
        
        # Start joint state publisher timer
        self.create_timer(0.1, self.publish_joint_states)
        
        self.get_logger().info('Arm controller node started')
    
    def format_angle(self, angle):
        """Convert angle to 4-character string (0-1023)"""
        angle_val = max(0, min(1023, int(angle)))
        return f"{angle_val:04d}"
    
    def send_command(self, cmd):
        """Send command to ESP8266"""
        if self.client_socket:
            try:
                full_cmd = f"{cmd}E"
                self.client_socket.sendall(full_cmd.encode())
                self.get_logger().debug(f"Sent: {cmd}")
            except (ConnectionResetError, BrokenPipeError, OSError) as e:
                self.get_logger().error(f"Connection error: {e}")
                self.client_socket = None
    
    def move_joint(self, joint, angle):
        """Send joint movement command: J<joint_num><angle>"""
        cmd = f"J{joint}{self.format_angle(angle)}"
        self.send_command(cmd)
        
        # Update local position
        if joint == 1:
            self.joint1 = angle
        elif joint == 2:
            self.joint2 = angle
        elif joint == 3:
            self.joint3 = angle
    
    def move_all_joints(self, j1, j2, j3):
        """Move all joints simultaneously: A<j1><j2><j3>"""
        cmd = f"A{self.format_angle(j1)}{self.format_angle(j2)}{self.format_angle(j3)}"
        self.send_command(cmd)
        self.joint1, self.joint2, self.joint3 = j1, j2, j3
    
    def move_base(self, angle):
        """Send base rotation command: B<angle>"""
        angle = max(0, min(500, int(angle)))
        cmd = f"B{angle}"
        self.send_command(cmd)
        self.base_angle = angle
    
    def move_gripper_rotate(self, angle):
        """Send gripper rotation command: GR<angle>"""
        angle = max(0, min(270, int(angle)))
        cmd = f"GR{angle}"
        self.send_command(cmd)
        self.gripper_rotate = angle
    
    def move_gripper_claw(self, angle):
        """Send gripper claw command: GC<angle>"""
        angle = max(0, min(180, int(angle)))
        cmd = f"GC{angle}"
        self.send_command(cmd)
        self.gripper_claw = angle
        time.sleep(0.05)
    
    def start_mdns_service(self):
        """Start mDNS service for network discovery"""
        try:
            service_info = ServiceInfo(
                "_http._tcp.local.",
                f"{self.server_name}._http._tcp.local.",
                addresses=[socket.inet_aton(self.server_ip)],
                port=self.server_port,
                server=f"{self.server_name}.",
            )
            
            self.zeroconf = Zeroconf()
            self.zeroconf.register_service(service_info)
            self.get_logger().info(f"mDNS service registered as {self.server_name} on {self.server_ip}:{self.server_port}")
        except Exception as e:
            self.get_logger().error(f"Failed to start mDNS: {e}")
    
    def handle_client(self, client_socket, addr):
        """Handle incoming client connection"""
        self.get_logger().info(f"Connected to ESP8266 at {addr}")
        self.client_socket = client_socket
        try:
            while self.running:
                time.sleep(0.1)
        except Exception as e:
            self.get_logger().error(f"Client handler error: {e}")
        finally:
            client_socket.close()
            self.client_socket = None
    
    def run_server(self):
        """Main server loop"""
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            server_socket.bind((self.server_ip, self.server_port))
        except OSError as e:
            self.get_logger().error(f"Failed to bind to {self.server_ip}:{self.server_port} - {e}")
            return
        
        server_socket.listen(1)
        server_socket.settimeout(1)
        
        self.get_logger().info(f"Server listening on {self.server_ip}:{self.server_port}...")
        
        try:
            while self.running:
                try:
                    client_socket, addr = server_socket.accept()
                    self.handle_client(client_socket, addr)
                except socket.timeout:
                    continue
                except Exception as e:
                    self.get_logger().error(f"Server error: {e}")
                    break
        finally:
            self.running = False
            server_socket.close()
            if self.zeroconf:
                self.zeroconf.unregister_all_services()
                self.zeroconf.close()
    
    def command_callback(self, msg):
        """Handle incoming arm commands"""
        try:
            if msg.joint_num == 1:
                self.move_joint(1, msg.angle)
            elif msg.joint_num == 2:
                self.move_joint(2, msg.angle)
            elif msg.joint_num == 3:
                self.move_joint(3, msg.angle)
            elif msg.joint_num == 4:
                self.move_base(msg.angle)
            elif msg.joint_num == 5:
                self.move_gripper_rotate(msg.angle)
            elif msg.joint_num == 6:
                self.move_gripper_claw(msg.angle)
        except Exception as e:
            self.get_logger().error(f"Error processing command: {e}")
    
    def preset_callback(self, request, response):
        """Handle preset position requests"""
        try:
            if request.preset_num == 1:  # Home position
                self.move_all_joints(300, 300, 500)
                self.move_base(0)
                self.move_gripper_rotate(90)
                self.move_gripper_claw(0)
                response.success = True
                response.message = "Moved to home position"
            elif request.preset_num == 2:  # Extended position
                self.move_all_joints(500, 500, 800)
                self.move_base(90)
                self.move_gripper_rotate(90)
                self.move_gripper_claw(0)
                response.success = True
                response.message = "Moved to extended position"
            elif request.preset_num == 3:  # Camera vertical position
                self.move_all_joints(300, 300, 500)
                self.move_base(0)
                self.move_gripper_rotate(0)
                self.move_gripper_claw(0)
                response.success = True
                response.message = "Moved to camera vertical position"
            else:
                response.success = False
                response.message = "Invalid preset number"
        except Exception as e:
            response.success = False
            response.message = f"Error moving to preset position: {e}"
        return response
    
    def emergency_stop_callback(self, request, response):
        """Handle emergency stop request"""
        try:
            self.running = False
            if self.client_socket:
                self.client_socket.close()
            response.success = True
            response.message = "Emergency stop activated"
        except Exception as e:
            response.success = False
            response.message = f"Error during emergency stop: {e}"
        return response
    
    def publish_joint_states(self):
        """Publish current joint states"""
        msg = JointState()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.name = ['joint1', 'joint2', 'joint3', 'base', 'gripper_rotate', 'gripper_claw']
        msg.position = [
            float(self.joint1),
            float(self.joint2),
            float(self.joint3),
            float(self.base_angle),
            float(self.gripper_rotate),
            float(self.gripper_claw)
        ]
        self.joint_state_pub.publish(msg)

    def cleanup(self):
        """Cleanup resources before shutdown"""
        self.running = False
        if self.zeroconf:
            self.zeroconf.unregister_all_services()
            self.zeroconf.close()
        if self.client_socket:
            self.client_socket.close()
            self.client_socket = None

def main(args=None):
    rclpy.init(args=args)
    node = ArmControllerNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.cleanup()
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 