import socket
import time
from zeroconf import ServiceInfo, Zeroconf
import threading
import rclpy
from rclpy.node import Node
from robot_control_interfaces.msg import ArmCommand
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory

# Server configuration
PORT = 4000
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."
FIXED_IP = "192.168.81.123"  # Added fixed IP address

class ArmController(Node):
    def __init__(self):
        super().__init__('arm_controller')
        self.client_socket = None
        self.zeroconf = None
        self.connection_lock = threading.Lock()
        self.connected = False
        
        # Joint state variables
        self.joint1 = 300
        self.joint2 = 300
        self.joint3 = 500                       
        self.base_angle = 0  # Current base angle (0-180)
        self.gripper_rotate = 90  # Current gripper rotation angle (0-270)
        self.gripper_claw = 0  # Current gripper claw position (0-180)
        self.speed = 30  # Default speed adjustment for joints
        self.claw_speed = 30  # Default speed for claw servo
        self.running = True

        # Create subscribers for controller commands
        self.arm_controller_sub = self.create_subscription(
            JointTrajectory,
            '/arm_controller/joint_trajectory',
            self.arm_controller_callback,
            10)
            
        self.gripper_controller_sub = self.create_subscription(
            JointTrajectory,
            '/gripper_controller/joint_trajectory',
            self.gripper_controller_callback,
            10)

        # Create joint state publisher
        self.joint_state_pub = self.create_publisher(
            JointState,
            '/joint_states',
            10)
        
        # Create timer for periodic joint state publishing
        self.timer = self.create_timer(0.1, self.publish_joint_states)  # 10Hz

    def format_angle(self, angle):
        """Convert angle to 4-character string (0-1023)"""
        angle_val = max(0, min(1023, int(angle)))
        return f"{angle_val:04d}"

    def send_command(self, cmd):
        """Send command to ESP8266"""
        with self.connection_lock:
            if self.connected and self.client_socket:
                try:
                    full_cmd = f"{cmd}E"
                    self.client_socket.sendall(full_cmd.encode())
                    self.get_logger().debug(f'Sent command: {cmd}')
                except (ConnectionResetError, BrokenPipeError, OSError) as e:
                    self.get_logger().error(f'Connection error: {e}')
                    self.connected = False
                    if self.client_socket:
                        self.client_socket.close()
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
        angle = max(0, min(500, int(angle)))  # Constrain to 0-180 degrees
        cmd = f"B{angle}"
        self.send_command(cmd)
        self.base_angle = angle

    def move_gripper_rotate(self, angle):
        """Send gripper rotation command: GR<angle>"""
        angle = max(0, min(270, int(angle)))  # Constrain to 0-270 degrees
        cmd = f"GR{angle}"
        self.send_command(cmd)
        self.gripper_rotate = angle

    def move_gripper_claw(self, angle):
        """Send gripper claw command: GC<angle>"""
        angle = max(0, min(180, int(angle)))  # Constrain to 0-180 degrees
        cmd = f"GC{angle}"
        self.send_command(cmd)
        self.gripper_claw = angle
        time.sleep(0.05)  # Small delay to ensure command is processed

    def arm_controller_callback(self, msg):
        """Handle incoming arm controller commands"""
        if not self.connected:
            self.get_logger().warn('Cannot process command: Not connected to arm server')
            return
            
        # Get the last point in the trajectory
        if not msg.points:
            return
            
        last_point = msg.points[-1]
        
        # Map joint names to their positions and convert from radians to servo angles
        for i, joint_name in enumerate(msg.joint_names):
            if joint_name == 'arm_base_joint':
                # Convert from radians (-π to 0) to servo angle (0 to 500)
                angle = (last_point.positions[i] + 3.14159) * (500 / 3.14159)
                self.move_base(angle)
            elif joint_name == 'a2':
                # Convert from radians (-2.3 to 0) to servo angle (0 to 1023)
                angle = (last_point.positions[i] + 2.3038) * (1023 / 2.3038)
                self.move_joint(2, angle)
            elif joint_name == 'a3':
                # Convert from radians (-1.74 to 0) to servo angle (0 to 1023)
                angle = (last_point.positions[i] + 1.7453) * (1023 / 1.7453)
                self.move_joint(3, angle)
            elif joint_name == 'a4':
                # Convert from radians (-0.64 to 1.57) to servo angle (0 to 1023)
                angle = (last_point.positions[i] + 0.6458) * (1023 / 2.2166)
                self.move_joint(1, angle)

    def gripper_controller_callback(self, msg):
        """Handle incoming gripper controller commands"""
        if not self.connected:
            self.get_logger().warn('Cannot process command: Not connected to arm server')
            return
            
        # Get the last point in the trajectory
        if not msg.points:
            return
            
        last_point = msg.points[-1]
        
        # Map joint names to their positions and convert from radians to servo angles
        for i, joint_name in enumerate(msg.joint_names):
            if joint_name == 'bg':
                # Convert from radians (-π to 0) to servo angle (0 to 270)
                angle = (last_point.positions[i] + 3.1415) * (270 / 3.1415)
                self.move_gripper_rotate(angle)
            elif joint_name == 'g1':
                # Convert from radians (-0.288 to 0.134) to servo angle (0 to 180)
                angle = (last_point.positions[i] + 0.288) * (180 / 0.422)
                self.move_gripper_claw(angle)

    def publish_joint_states(self):
        """Publish current joint states"""
        joint_state = JointState()
        joint_state.header.stamp = self.get_clock().now().to_msg()
        joint_state.name = ['arm_base_joint', 'a2', 'a3', 'a4', 'bg', 'g1']
        
        # Convert servo angles to radians for MoveIt
        joint_state.position = [
            self.base_angle * (3.14159 / 500) - 3.14159,  # arm_base_joint (-π to 0)
            self.joint2 * (2.3038 / 1023) - 2.3038,  # a2 (-2.3 to 0)
            self.joint3 * (1.7453 / 1023) - 1.7453,  # a3 (-1.74 to 0)
            self.joint1 * (2.2166 / 1023) - 0.6458,  # a4 (-0.64 to 1.57)
            self.gripper_rotate * (3.1415 / 270) - 3.1415,  # bg (-π to 0)
            self.gripper_claw * (0.422 / 180) - 0.288  # g1 (-0.288 to 0.134)
        ]
        
        self.joint_state_pub.publish(joint_state)

    def start_mdns_service(self):
        """Start mDNS service for network discovery"""
        try:
            service_info = ServiceInfo(
                SERVICE_TYPE,
                f"{SERVER_NAME}.{SERVICE_TYPE}",
                addresses=[socket.inet_aton(FIXED_IP)],
                port=PORT,
                server=f"{SERVER_NAME}.",
            )
            
            self.zeroconf = Zeroconf()
            self.zeroconf.register_service(service_info)
            self.get_logger().info(f"mDNS service registered as {SERVER_NAME} on {FIXED_IP}:{PORT}")
        except Exception as e:
            self.get_logger().error(f"Failed to start mDNS: {e}")

    def handle_client(self, client_socket, addr):
        """Handle incoming client connection"""
        self.get_logger().info(f"Connected to ESP8266 at {addr}")
        with self.connection_lock:
            self.client_socket = client_socket
            self.connected = True
        try:
            while self.running:
                time.sleep(0.1)  # Prevent CPU overuse
        except Exception as e:
            self.get_logger().error(f"Client handler error: {e}")
        finally:
            with self.connection_lock:
                client_socket.close()
                self.client_socket = None
                self.connected = False

    def run_server(self):
        """Main server loop"""
        self.start_mdns_service()
        
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            server_socket.bind((FIXED_IP, PORT))  # Bind to fixed IP
        except OSError as e:
            self.get_logger().error(f"Failed to bind to {FIXED_IP}:{PORT} - {e}")
            self.get_logger().error("Make sure the IP address is properly configured on your network interface.")
            return
        
        server_socket.listen(1)
        server_socket.settimeout(1)  # Allow periodic checking of self.running
        
        self.get_logger().info(f"Server listening on {FIXED_IP}:{PORT}...")
         
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
        except KeyboardInterrupt:
            self.get_logger().info("\nShutting down server...")
        finally:
            self.running = False
            server_socket.close()
            if self.zeroconf:
                self.zeroconf.unregister_all_services()
                self.zeroconf.close()
            self.get_logger().info("Server stopped")

def main(args=None):
    rclpy.init(args=args)
    controller = ArmController()
    
    # Run ROS node in a separate thread
    ros_thread = threading.Thread(target=rclpy.spin, args=(controller,))
    ros_thread.daemon = True
    ros_thread.start()
    
    # Run the server in the main thread
    controller.run_server()
    
    # Cleanup
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == "__main__":
    main()