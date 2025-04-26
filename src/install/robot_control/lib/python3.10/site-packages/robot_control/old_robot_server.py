import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Quaternion, TransformStamped
from sensor_msgs.msg import JointState
from my_robot_camera_msgs.msg import DetectionArray
import socket
from zeroconf import ServiceInfo, Zeroconf
import re
from tf2_ros import TransformBroadcaster
import math
import numpy as np
import time
# Server configuration (same as original)
PORT = 3001
SERVER_IP = "192.168.160.71"  # Fixed IP address
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."

class MecanumController(Node):
    def __init__(self):
        super().__init__('mecanum_controller')
        
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
        
        # TF Broadcaster
        self.tf_broadcaster = TransformBroadcaster(self)
        
        # Robot parameters (adjust according to your robot)
        self.wheel_radius = 0.075  # 7.5cm radius (matches your state publisher)
        self.track_width = 0.24     # 24cm between left/right wheels
        self.wheel_base = 0.45      # 45cm between front/rear wheels
        
        # Robot state
        self.robot_x = 0.0
        self.robot_y = 0.0
        self.robot_theta = 0.0
        
        # Image center coordinates (assuming 1280x720 resolution)
        self.image_center_x = 300
        self.image_center_y = 300
        
        # Control parameters for centering
        self.kp = 0.05  # Proportional gain
        self.max_speed = 40  # Maximum motor speed for centering
        
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
        self.rpm_timer = self.create_timer(0.1, self.update_state)  # 20Hz
        
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
                    slip_const = 1.2
                    # Update wheel velocities (matching your RobotStatePublisher naming)
                    self.wheel_velocities['right_up_wheel_joint'] = fr_rpm * rpm_to_rads * slip_const 
                    self.wheel_velocities['right_down_wheel_joint'] = rr_rpm * rpm_to_rads * slip_const
                    self.wheel_velocities['left_down_wheel_joint'] = rl_rpm * rpm_to_rads * slip_const
                    self.wheel_velocities['left_up_wheel_joint'] = fl_rpm * rpm_to_rads * slip_const
                    
                    # Update wheel positions based on velocities
                    dt = 0.1  # Time since last update (20Hz)
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
        self.wheel_vel_pub.publish(joint_state)
        
    def publish_transforms(self):
        """Publish complete TF tree including odometry and wheel transforms"""
        now = self.get_clock().now().to_msg()
        dt = 0.1 # Time since last update (20Hz)
        
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
        return
        """Callback for processing detections and centering the robot on objects"""
        if not msg.detections:
            return
        
        # Get the first detection (you can modify this to track specific objects)
        detection = msg.detections[0]
        
        # Calculate center of the detected object
        obj_center_x = (detection.x1 + detection.x2) / 2
        obj_center_y = (detection.y1 + detection.y2) / 2
        self.get_logger().info(f"object center: {obj_center_x}, {obj_center_y}")
        
        # Calculate errors from image center
        if msg.detections[0].class_id == 5:
            error_x = self.image_center_x - obj_center_x
            error_y = self.image_center_y - obj_center_y
        else:
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
        fl_speed = max(-40, min(40, fl_speed))
        rl_speed = max(-40, min(40, rl_speed))
        rr_speed = max(-40, min(40, rr_speed))
        fr_speed = max(-40, min(40, fr_speed))
        
        # Send motor commands
        self.motor(fl_speed, rl_speed, rr_speed, fr_speed)
        
        # Log the centering action
        self.get_logger().info(f"class_id: {msg.detections[0].class_id}")
        
    def destroy_node(self):
        """Cleanup on node shutdown"""
        self.get_logger().info("Shutting down mecanum controller...")
        self.client_socket.close()
        self.server_socket.close()
        self.zeroconf.unregister_all_services()
        self.zeroconf.close()
        super().destroy_node()

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