import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Quaternion, TransformStamped, PoseStamped
from sensor_msgs.msg import JointState
from my_robot_camera_msgs.msg import DetectionArray
from nav2_msgs.action import NavigateToPose
from rclpy.action import ActionClient
from rclpy.callback_groups import ReentrantCallbackGroup
from robot_control_interfaces.msg import ArmCommand
from robot_control.task_manager import TaskManager, TaskType
import socket
from zeroconf import ServiceInfo, Zeroconf
import re
from tf2_ros import TransformBroadcaster
import math
import numpy as np
import time
import asyncio
from lifecycle_msgs.msg import State
from action_msgs.msg import GoalStatus
# Server configuration (same as original)
PORT = 3001
SERVER_IP = "192.168.81.123"  # Updated to match system IP
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."

class MecanumController(Node):
    def __init__(self):
        super().__init__('mecanum_controller')
        
        # Initialize task manager
        self.task_manager = TaskManager()
        
        # Initialize workspace locations
        self.initialize_workspaces()
        
        # Initialize object locations
        self.initialize_objects()
        
        # Initialize task sequence
        self.initialize_tasks()
        
        # Create callback group for action client
        self.callback_group = ReentrantCallbackGroup()
        
        # Initialize connection to ESP8266
        self.zeroconf = self.start_mdns_service(PORT)
        self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        self.server_socket.bind((SERVER_IP, PORT))
        self.server_socket.listen(1)
        
        self.get_logger().info(f"Server listening on {SERVER_IP}:{PORT}...")
        
        # Wait for ESP8266 connection
        self.client_socket, addr = self.server_socket.accept()
        self.get_logger().info(f"Connected to ESP8266 at {addr}")
        
        # Set timeout for reading RPM data
        self.client_socket.settimeout(0.1)  # 100ms timeout
        
        # Create Nav2 action client
        self.nav_client = ActionClient(
            self,
            NavigateToPose,
            'navigate_to_pose',
            callback_group=self.callback_group
        )
        
        # Create subscriber for cmd_vel
        self.subscription = self.create_subscription(
            Twist,
            '/cmd_vel',
            self.cmd_vel_callback,
            10)
            
        # Create subscriber for detections
        self.detection_sub = self.create_subscription(
            DetectionArray,
            '/detections',
            self.detection_callback,
            10)
        
        # Create publisher for wheel velocities
        self.wheel_vel_pub = self.create_publisher(JointState, 'wheel_velocities', 10)
        
        # Create publisher for arm joint commands
        self.arm_joint_pub = self.create_publisher(ArmCommand, '/cmd_arm', 10)
        
        # TF Broadcaster
        self.tf_broadcaster = TransformBroadcaster(self)
        
        # Robot parameters (adjust according to your robot)
        self.wheel_radius = 0.075  # 7.5cm radius (matches your state publisher)
        self.track_width = 0.4     # 24cm between left/right wheels
        self.wheel_base = 0.35      # 45cm between front/rear wheels
        
        # Robot state
        self.robot_x = 0.0
        self.robot_y = 0.0
        self.robot_theta = 0.0
        
        # Image center coordinates (assuming 1280x720 resolution)
        self.image_center_x = 370
        self.image_center_y = 300
        
        # Control parameters for centering
        self.kp = 0.2  # Proportional gain
        self.max_speed = 50  # Maximum motor speed for centering
        
        # Wheel positions (radians)
        self.wheel_positions = {
            'left_down_wheel_joint': 0.0,
            'right_down_wheel_joint': 0.0,
            'left_up_wheel_joint': 0.0,
            'right_up_wheel_joint': 0.0
        }
        
        # Wheel velocity storage (rad/s)
        self.wheel_velocities = {
            'left_up_wheel_joint': 0.0,    # Front left
            'left_down_wheel_joint': 0.0,  # Rear left
            'right_down_wheel_joint': 0.0, # Rear right
            'right_up_wheel_joint': 0.0    # Front right
        }

        self.lx = self.wheel_base / 2      # half of wheelbase
        self.ly = self.track_width / 2     # half of track width

        # Timer for reading RPM data and updating transforms
        self.rpm_timer = self.create_timer(0.05, self.update_state)  # 20Hz
        self.object_ready_for_grab = False
        self.done_grabbing = True
        self.arm_in_view_position = False
        self.center_cnt = 0
        self.search_cnt = 0
        # Initialize navigation state
        self.nav_ready = False
        self.goal_reached = True
        self.current_goal = None
        self.current_task = None
         
        # Create publisher for goal pose
        self.goal_pub = self.create_publisher(
            PoseStamped,
            '/goal_pose',
            10)
            
        # Timer for task execution
        # self.task_timer = self.create_timer(1.0, self.execute_next_task)

    def initialize_workspaces(self):
        """Initialize workspace locations"""
        # Set workspace locations (example values - replace with your actual values)
        self.task_manager.set_workspace_location('ws1', 6.48, 2.88, 0)
        #self.task_manager.set_workspace_location('ws2', 6.52, 0.81, 0)
        #self.task_manager.set_workspace_location('ws3', 6.49, 1.05, 0)
        # Add more workspaces as needed...

    def initialize_objects(self):
        """Initialize object locations"""
        # Set object locations (example values - replace with your actual values)
        self.task_manager.set_object_location('bolt', 0.9, 0.7, 1.07, 0.1, 0.1)
        self.task_manager.set_object_location('profile_1', 1.5, 0.5, 0.0, 0.1, 0.1)
        # Add more objects as needed...

    def initialize_tasks(self):
        """Initialize the task sequence"""
        # Add tasks to the queue (example sequence - replace with your actual tasks)
        self.task_manager.add_task('nav', 'ws1')  # Navigate to workspace 1
        # Add more tasks as needed...

    def start_mdns_service(self, port):
        """Same as original"""
        service_info = ServiceInfo(
            SERVICE_TYPE,
            f"{SERVER_NAME}.{SERVICE_TYPE}",
            addresses=[socket.inet_aton(SERVER_IP)],
            port=port,
            server=f"{SERVER_NAME}.",
        )
        
        zeroconf = Zeroconf()
        zeroconf.register_service(service_info)
        self.get_logger().info(f"mDNS service registered as {SERVER_NAME} on {SERVER_IP}:{port}")
        return zeroconf
        
    def format_speed(self, speed):
        """Same as original"""
        return f"{'+' if speed >=0 else '-'}{abs(speed):03d}"
        
    def motor(self, L1, L2, R2, R1):
        """Same format as original but without client parameter"""
        cmd = f"M{self.format_speed(L1)}{self.format_speed(L2)}{self.format_speed(R2)}{self.format_speed(R1)}E"
        try:
            self.client_socket.sendall(cmd.encode())
            self.get_logger().debug(f"Sent: {cmd}")
        except (ConnectionResetError, BrokenPipeError) as e:
            self.get_logger().error(f"Connection error: {e}")
            self.reconnect_esp8266()
            
    def reconnect_esp8266(self):
        """Attempt to reconnect to ESP8266"""
        self.client_socket.close()
        self.get_logger().info("Attempting to reconnect to ESP8266...")
        self.client_socket, addr = self.server_socket.accept()
        self.get_logger().info(f"Reconnected to ESP8266 at {addr}")
        self.client_socket.settimeout(0.1)  # Reset timeout after reconnection
        
    def update_state(self):
        """Main update function that reads RPM data and updates transforms"""
        self.read_rpm_data()
        self.publish_transforms()
        
    def read_rpm_data(self):
        """Read RPM data from the robot and update wheel velocities"""
        try:
            # Request RPM data
            self.client_socket.sendall(b'VE')

            # Read response (format: '+3+20-30-39E')
            data = self.client_socket.recv(100).decode().strip()
            # Parse RPM values
            if data.startswith('+') or data.startswith('-'):
                # Extract all signed numbers
                rpm_values = re.findall(r'[+-]\d*\.?\d+', data)
                
                if len(rpm_values) == 4:
                    # Convert to integers
                    fr_rpm = float(rpm_values[0])  # Front right
                    rr_rpm = float(rpm_values[1])  # Rear right
                    rl_rpm = -float(rpm_values[2])  # Rear left
                    fl_rpm = -float(rpm_values[3])  # Front left
                    # self.get_logger().info(f"recieved rpm data: {rpm_values}")
                    
                    # Convert RPM to rad/s (1 RPM = 2π/60 rad/s)
                    rpm_to_rads = 2 * math.pi / 60
                    # سر خوردن
                    slip_const = 1.18
                    # Update wheel velocities (matching your RobotStatePublisher naming)
                    self.wheel_velocities['right_up_wheel_joint'] = fr_rpm * rpm_to_rads * slip_const 
                    self.wheel_velocities['right_down_wheel_joint'] = rr_rpm * rpm_to_rads * slip_const
                    self.wheel_velocities['left_down_wheel_joint'] = rl_rpm * rpm_to_rads * slip_const
                    self.wheel_velocities['left_up_wheel_joint'] = fl_rpm * rpm_to_rads * slip_const
                    
                    # Update wheel positions based on velocities
                    dt = 0.05  # Time since last update (20Hz)
                    for wheel in self.wheel_positions:
                        self.wheel_positions[wheel] += self.wheel_velocities[wheel] * dt
                    
                    # Publish wheel velocities
                    self.publish_wheel_velocities()
                    
        except socket.timeout:
            # Normal case - no data available
            pass
        except (ConnectionResetError, BrokenPipeError) as e:
            self.get_logger().error(f"Connection error in RPM read: {e}")
            self.reconnect_esp8266()
        except Exception as e:
            self.get_logger().error(f"Error processing RPM data: {e}")
            
    def publish_wheel_velocities(self):
        """Publish wheel velocities as JointState message"""
        joint_state = JointState()
        joint_state.header.stamp = self.get_clock().now().to_msg()
        joint_state.name = [
            'left_down_wheel_joint',
            'right_down_wheel_joint',
            'left_up_wheel_joint',
            'right_up_wheel_joint'
        ]
        joint_state.position = [
            self.wheel_positions['left_down_wheel_joint'],
            self.wheel_positions['right_down_wheel_joint'],
            self.wheel_positions['left_up_wheel_joint'],
            self.wheel_positions['right_up_wheel_joint']
        ]
        joint_state.velocity = [
            self.wheel_velocities['left_down_wheel_joint'],
            self.wheel_velocities['right_down_wheel_joint'],
            self.wheel_velocities['left_up_wheel_joint'],
            self.wheel_velocities['right_up_wheel_joint']
        ]
        # self.wheel_vel_pub.publish(joint_state)
        
    def publish_transforms(self):
        """Publish complete TF tree including odometry and wheel transforms"""
        now = self.get_clock().now().to_msg()
        dt = 0.05 # Time since last update (20Hz)
        
        # Calculate odometry from wheel velocities
        L = self.track_width / 2
        W = self.wheel_base / 2
        R = self.wheel_radius
        
        # Calculate robot velocity in body frame (matches your state publisher)
        vx = R * (self.wheel_velocities['left_up_wheel_joint'] + 
                 self.wheel_velocities['right_up_wheel_joint'] + 
                 self.wheel_velocities['left_down_wheel_joint'] + 
                 self.wheel_velocities['right_down_wheel_joint']) / 4
        
        vy = R * (-self.wheel_velocities['left_up_wheel_joint'] + 
                 self.wheel_velocities['right_up_wheel_joint'] + 
                 self.wheel_velocities['left_down_wheel_joint'] - 
                 self.wheel_velocities['right_down_wheel_joint']) / 4
        
        omega = R/(4*(L + W)) * (-self.wheel_velocities['left_up_wheel_joint'] + 
                                self.wheel_velocities['right_up_wheel_joint'] - 
                                self.wheel_velocities['left_down_wheel_joint'] + 
                                self.wheel_velocities['right_down_wheel_joint'])
        
        # Update robot pose
        self.robot_theta += omega * dt
        self.robot_x += (vx * math.cos(self.robot_theta) - vy * math.sin(self.robot_theta)) * dt
        self.robot_y += (vx * math.sin(self.robot_theta) + vy * math.cos(self.robot_theta)) * dt
        
        # 1. Odom to base_link transform
        odom_tf = TransformStamped()
        odom_tf.header.stamp = now
        odom_tf.header.frame_id = "odom"
        odom_tf.child_frame_id = "base_link"
        odom_tf.transform.translation.x = self.robot_x
        odom_tf.transform.translation.y = self.robot_y
        odom_tf.transform.translation.z = 0.0
        
        q = Quaternion()
        q.z = math.sin(self.robot_theta/2)
        q.w = math.cos(self.robot_theta/2)
        odom_tf.transform.rotation = q
        self.tf_broadcaster.sendTransform(odom_tf)
        
        # 2. Wheel transforms (4 wheels)
        wheel_poses = {
            'left_down_wheel': (self.track_width/2, self.wheel_base/2, -self.wheel_radius),
            'right_down_wheel': (-self.track_width/2, self.wheel_base/2, -self.wheel_radius),
            'left_up_wheel': (self.track_width/2, -self.wheel_base/2, -self.wheel_radius),
            'right_up_wheel': (-self.track_width/2, -self.wheel_base/2, -self.wheel_radius)
        }
        
        for wheel, (x, y, z) in wheel_poses.items():
            tf = TransformStamped()
            tf.header.stamp = now
            tf.header.frame_id = "base_link"
            tf.child_frame_id = f"{wheel}_link"
            tf.transform.translation.x = x
            tf.transform.translation.y = y
            tf.transform.translation.z = z
            
            # Wheel rotation (90° around X axis plus actual wheel rotation)
            angle = self.wheel_positions[f"{wheel.replace('_', '_')}_joint"]
            q = Quaternion()
            q.x = math.sin(math.pi/4)  # 90° rotation around X
            q.w = math.cos(math.pi/4)
            tf.transform.rotation = q
            
            self.tf_broadcaster.sendTransform(tf)
        
    def cmd_vel_callback(self, msg):
        """
        Convert Twist message to mecanum wheel velocities using inverse kinematics
        and send to motors.
        """
        # Extract linear and angular velocities
        # سرعت روبات
        vx = msg.linear.x * 0.015  # m/s
        vy = msg.linear.y * 0.015 # m/s
        wz = msg.angular.z * 0.015 # rad/s
        
        # Inverse kinematics for mecanum wheels
        # Wheel velocities in m/s
        wheel_fl = ( vx + vy + (self.lx + self.ly) * wz) / self.wheel_radius
        wheel_rl = ( vx - vy + (self.lx + self.ly) * wz) / self.wheel_radius
        wheel_rr = (-vx - vy + (self.lx + self.ly) * wz) / self.wheel_radius
        wheel_fr = (-vx + vy + (self.lx + self.ly) * wz) / self.wheel_radius
        
        # Convert m/s to motor speed (-255 to 255)
        max_speed = 0.5  # m/s (adjust based on your robot's max speed)
        fl_speed = int((wheel_fl / max_speed) * 255)
        fr_speed = int((wheel_fr / max_speed) * 255)
        rr_speed = int((wheel_rr / max_speed) * 255)
        rl_speed = int((wheel_rl / max_speed) * 255)
        
        # Constrain speeds to [-255, 255]
        fl_speed = max(-255, min(255, fl_speed))
        fr_speed = max(-255, min(255, fr_speed))
        rr_speed = max(-255, min(255, rr_speed))
        rl_speed = max(-255, min(255, rl_speed))
        
        # Send motor commands (note the order: L1, L2, R2, R1)
        # Assuming L1=front left, L2=rear left, R2=rear right, R1=front right
        self.get_logger().info(f"sending motor  {fl_speed} {rl_speed} {rr_speed} {fr_speed}")

        self.motor(fl_speed, rl_speed, rr_speed, fr_speed)
        
    def detection_callback(self, msg):
        # don't use this callback for now
        # return
        """Callback for processing detections and centering the robot on objects"""
        if self.done_grabbing:
            return
        if not msg.detections:
            if not self.arm_in_view_position:
                for i in range(20):
                    self.publish_arm_joints({1: 700, 2: 700, 3: 190, 4: 0, 5: 0, 6: 0})
                    time.sleep(0.5)
                self.arm_in_view_position = True
                return
            self.search_cnt += 1
            if self.search_cnt < 30:
                self.motor(-10, 10, 10, -10)
            elif self.search_cnt < 60:
                self.motor(10, -10, -10, 10)
            else:
                self.search_cnt = 0
                self.motor(0, 0, 0, 0)
        elif self.object_ready_for_grab:
            self.motor(0, 0, 0, 0)
            self.get_logger().info("object is ready for grab")
            for i in range(20):
                self.publish_arm_joints({1: 950, 2: 850, 3: 450, 4: 0, 5: 0,  6: 0})
                time.sleep(0.5)
            for i in range(10):
                self.publish_arm_joints({1: 950, 2: 850, 3: 450, 4: 0, 5: 0, 6: 80 })
                time.sleep(0.5)
            for i in range(20):
                self.publish_arm_joints({1: 500, 2: 850, 3: 450, 4: 0, 5: 0, 6: 80 })
                time.sleep(0.5)
            for i in range(20):
                self.publish_arm_joints({1: 400, 2: 400, 3: 450, 4: 0, 5: 0, 6: 80 })
                time.sleep(0.5)
            self.object_ready_for_grab = False
            self.arm_in_view_position = False
            # self.done_grabbing = True
        else:
            if not self.arm_in_view_position:
                for i in range(20):
                    self.publish_arm_joints({1: 700, 2: 700, 3: 190, 4: 0, 5: 0, 6: 0})
                    time.sleep(0.5)
                self.arm_in_view_position = True
                return
            # Get the first detection (you can modify this to track specific objects)
            detection = msg.detections[0]
            
            # Calculate center of the detected object
            obj_center_x = (detection.x1 + detection.x2) / 2
            obj_center_y = (detection.y1 + detection.y2) / 2
            # self.get_logger().info(f"object center: {obj_center_x}, {obj_center_y}")
            
            # Calculate errors from image center
            if True: #msg.detections[0].class_id == self.current_task.task_data:
                error_x = self.image_center_x - obj_center_x
                error_y = self.image_center_y - obj_center_y
                if abs(error_x) < 30 and abs(error_y) < 30:
                    self.center_cnt += 1
                    error_x = 0
                    error_y = 0
                    if self.center_cnt > 2:
                        self.object_ready_for_grab = True
                        self.get_logger().info("object is in the center")
            else:
                self.search_cnt += 1
                if self.search_cnt < 30:
                    error_x = -100
                elif self.search_cnt < 60:
                    error_x = 100
                else:
                    self.search_cnt = 0
                    error_x = 0
                error_y = 0
            # Calculate motor speeds based on errors
            # Positive error means object is to the left/up, so we need to move left/up
            speed_x = int(self.kp * error_x)
            speed_y = int(self.kp * error_y)
            
            # Constrain speeds
            speed_x = max(-self.max_speed, min(self.max_speed, speed_x))
            speed_y = max(-self.max_speed, min(self.max_speed, speed_y))
            
            # Convert to mecanum wheel speeds
            # For mecanum wheels, moving left/right requires opposite wheel speeds
            # Moving up/down requires same wheel speeds
            fl_speed = + speed_y + speed_x
            rl_speed = + speed_y - speed_x
            rr_speed = - speed_y - speed_x
            fr_speed = - speed_y + speed_x
            
            # Constrain final speeds
            fl_speed = max(-10, min(10, fl_speed))
            rl_speed = max(-10, min(10, rl_speed))
            rr_speed = max(-10, min(10, rr_speed))
            fr_speed = max(-10, min(10, fr_speed))
            
            # Send motor commands
            self.motor(fl_speed, rl_speed, rr_speed, fr_speed)
            time.sleep(0.1)
            self.motor(0, 0, 0, 0)
            
            # Log the centering action
            # self.get_logger().info(f"class_id: {msg.detections[0].class_id}")
    
    def publish_arm_joints(self, joint_positions):
        """
        Publish arm joint positions to /cmd_arm topic using ArmCommand message type.
        
        Args:
            joint_positions (dict): Dictionary containing joint numbers and their target angles
        """
        for joint_num, angle in joint_positions.items():
            msg = ArmCommand()
            msg.joint_num = joint_num
            msg.angle = angle
            msg.speed = 30  # Default speed, can be adjusted if needed
            self.arm_joint_pub.publish(msg)
            self.get_logger().info(f"Published arm command - Joint: {joint_num}, Angle: {angle}")

    def destroy_node(self):
        """Cleanup on node shutdown"""
        self.get_logger().info("Shutting down mecanum controller...")
        self.client_socket.close()
        self.server_socket.close()
        self.zeroconf.unregister_all_services()
        self.zeroconf.close()
        super().destroy_node()

    def send_goal_pose(self, x, y, theta):
        """
        Send a goal pose to the navigation stack and track its completion.
        
        Args:
            x (float): X coordinate in meters
            y (float): Y coordinate in meters
            theta (float): Yaw angle in radians
            
        Returns:
            bool: True if goal was successfully published
        """
        # Create the pose message
        pose_msg = PoseStamped()
        pose_msg.header.frame_id = 'map'
        pose_msg.header.stamp = self.get_clock().now().to_msg()
        
        # Set position
        pose_msg.pose.position.x = x
        pose_msg.pose.position.y = y
        pose_msg.pose.position.z = 0.0
        
        # Set orientation (quaternion from yaw)
        pose_msg.pose.orientation.x = 0.0
        pose_msg.pose.orientation.y = 0.0
        pose_msg.pose.orientation.z = math.sin(theta / 2.0)
        pose_msg.pose.orientation.w = math.cos(theta / 2.0)
        
        # Store current goal for tracking
        self.current_goal = (x, y, theta)
        self.goal_reached = False
        
        # Create and send the goal using the action client
        nav_goal = NavigateToPose.Goal()
        nav_goal.pose = pose_msg  # Assign the pose message to the goal
        
        # Send the goal and wait for result
        future = self.nav_client.send_goal_async(nav_goal)
        future.add_done_callback(self.goal_response_callback)
        
        self.get_logger().info(f'Published goal pose: x={x}, y={y}, theta={theta}')
        return True
        
    def goal_response_callback(self, future):
        """
        Callback for when the goal is accepted or rejected
        """
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().info('Goal rejected :(')
            return

        self.get_logger().info('Goal accepted :)')
        
        # Get the result
        result_future = goal_handle.get_result_async()
        result_future.add_done_callback(self.get_result_callback)
        
    def execute_next_task(self):
        """Execute the next task in the queue"""
        if self.current_task is None and self.goal_reached:
            self.current_task = self.task_manager.get_next_task()
            if self.current_task is None:
                self.get_logger().info("No more tasks to execute")
                return
                
            if self.current_task.task_type == TaskType.NAV:
                x, y, theta = self.task_manager.get_task_pose(self.current_task)
                self.send_goal_pose(x, y, theta)
            elif self.current_task.task_type == TaskType.PICK:
                # Implement pick logic here
                self.get_logger().info(f"Picking object: {self.current_task.task_data}")
                self.done_grabbing = False
            elif self.current_task.task_type == TaskType.PLACE:
                # Implement place logic here
                self.get_logger().info(f"Placing object in storage: {self.current_task.task_data}")
                self.done_grabbing = True
        else:
            self.get_logger().info("Nothing is happening")
    def get_result_callback(self, future):
        """
        Callback for when the goal is completed
        """
        result = future.result().result
        self.goal_reached = True
        self.get_logger().info('Goal reached successfully!')
        
        if self.current_task is not None:
            if self.current_task.task_type == TaskType.NAV:
                self.current_task = None
            elif self.current_task.task_type == TaskType.PICK:
                # Wait for picking to complete
                if self.done_grabbing:
                    self.current_task = None
            elif self.current_task.task_type == TaskType.PLACE:
                # Wait for placing to complete
                if self.done_grabbing:
                    self.current_task = None

def main(args=None):
    rclpy.init(args=args)
    
    mecanum_controller = MecanumController()
    
    try:
        rclpy.spin(mecanum_controller)
    except KeyboardInterrupt:
        pass
    finally:
        mecanum_controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
