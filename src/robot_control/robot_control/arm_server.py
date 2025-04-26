import socket
import time
from zeroconf import ServiceInfo, Zeroconf
import threading
import rclpy
from rclpy.node import Node
from robot_control_interfaces.msg import ArmCommand
from sensor_msgs.msg import JointState

# Server configuration
PORT = 4000
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."
FIXED_IP = "192.168.81.123"  # Added fixed IP address
# کتابخونه کیبورد نمیشه استفاده کرد
# باید یه تا\یک درست کنیم که آرم کنترلر روش سابسکرایب کنه و توش ست پوینت های بازو رو بخونه
# پابلیش کننده روبات سروره

class ArmController(Node):
    def __init__(self):
        super().__init__('arm_controller')
        self.client_socket = None
        self.zeroconf = None
        self.joint1 = 300
        self.joint2 = 300
        self.joint3 = 500                       
        self.base_angle = 0  # Current base angle (0-180)
        self.gripper_rotate = 90  # Current gripper rotation angle (0-270)
        self.gripper_claw = 0  # Current gripper claw position (0-180)
        self.speed = 30  # Default speed adjustment for joints
        self.claw_speed = 30  # Default speed for claw servo
        self.running = True

        # Create subscriber for arm commands
        self.subscription = self.create_subscription(
            ArmCommand,
            '/cmd_arm',
            self.arm_command_callback,
            1000)
        self.subscription  # prevent unused variable warning

        # Create subscriber for joint states
        self.joint_states_sub = self.create_subscription(
            JointState,
            '/joint_states',
            self.joint_states_callback,
            10)
        self.joint_states_sub  # prevent unused variable warning
        
        # Store latest joint states
        self.latest_joint_states = None
        
        # Create timer for processing joint states every 0.5 seconds
        self.joint_states_timer = self.create_timer(2, self.process_joint_states)

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
                print(f"Sent: {cmd}")
            except (ConnectionResetError, BrokenPipeError, OSError) as e:
                print(f"Connection error: {e}")
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
            print(f"mDNS service registered as {SERVER_NAME} on {FIXED_IP}:{PORT}")
        except Exception as e:
            print(f"Failed to start mDNS: {e}")

    def handle_client(self, client_socket, addr):
        """Handle incoming client connection"""
        print(f"Connected to ESP8266 at {addr}")
        self.client_socket = client_socket
        try:
            while self.running:
                time.sleep(0.1)  # Prevent CPU overuse
        except Exception as e:
            print(f"Client handler error: {e}")
        finally:
            client_socket.close()
            self.client_socket = None

    def arm_command_callback(self, msg):
        """Handle incoming arm commands from ROS topic"""
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
        
        # Update speed if provided
        if msg.speed > 0:
            self.speed = msg.speed

    def joint_states_callback(self, msg):
        """Store latest joint states message"""
        self.latest_joint_states = msg

    def process_joint_states(self):
        """Process joint states at fixed interval"""
        if self.latest_joint_states is None:
            return
            
        try:
            # Find the indices of our joints in the message
            joint1_idx = self.latest_joint_states.name.index('a2')
            joint2_idx = self.latest_joint_states.name.index('a3')
            joint3_idx = self.latest_joint_states.name.index('a4')
            base_idx = self.latest_joint_states.name.index('arm_base_joint')
            gripper_rotate_idx = self.latest_joint_states.name.index('bg')
            gripper_claw_idx = self.latest_joint_states.name.index('g1')

            # Convert joint positions from radians to degrees
            # Note: The angles are in radians, convert to degrees and map to appropriate ranges
            joint1_angle = int((self.latest_joint_states.position[joint1_idx] * 180 / 3.14159))  # Convert rad to deg and offset
            joint2_angle = int((self.latest_joint_states.position[joint2_idx] * 180 / 3.14159))
            joint3_angle = int((self.latest_joint_states.position[joint3_idx] * 180 / 3.14159))
            base_angle = -int((self.latest_joint_states.position[base_idx] * 180 / 3.14159))
            gripper_rotate_angle = 90 - int((self.latest_joint_states.position[gripper_rotate_idx] * 180 / 3.14159))
            gripper_claw_angle = int((self.latest_joint_states.position[gripper_claw_idx] * 180 / 3.14159))

            self.get_logger().info(f"Joint1: {joint1_angle}, Joint2: {joint2_angle}, Joint3: {joint3_angle}, Base: {base_angle}, Gripper Rotate: {gripper_rotate_angle}, Gripper Claw: {gripper_claw_angle}")

            # Convert angles using linear mapping formulas
            # Joint 1: Maps 0 to 300, -54 to 720
            joint1_angle = int(300 + (joint1_angle * (680 - 300) / (-54 - 0)))

            # Joint 2: Maps 0 to 300, -70 to 600 
            joint2_angle = int(300 + (joint2_angle * (700 - 300) / (-70 - 0)))

            # Joint 3: Maps 0 to 500, 42 to 750
            joint3_angle = int(500 + (joint3_angle * (850 - 500) / (42 - 0)))

            # Log joint angles and gripper positions for debugging
            self.get_logger().info(f"Joint1: {joint1_angle}, Joint2: {joint2_angle}, Joint3: {joint3_angle}, Base: {base_angle}, Gripper Rotate: {gripper_rotate_angle}, Gripper Claw: {gripper_claw_angle}")
            
            # Send commands to robot
            self.move_joint(1, joint1_angle)
            self.move_joint(2, joint2_angle)
            self.move_joint(3, joint3_angle)
            self.move_base(base_angle)
            self.move_gripper_rotate(gripper_rotate_angle)
            self.move_gripper_claw(gripper_claw_angle)

        except ValueError as e:
            self.get_logger().warn(f"Could not find all required joints in joint_states message: {e}")
        except Exception as e:
            self.get_logger().error(f"Error processing joint states: {e}")

    def run_server(self):
        """Main server loop"""
        self.start_mdns_service()
        
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        try:
            server_socket.bind((FIXED_IP, PORT))  # Bind to fixed IP
        except OSError as e:
            print(f"Failed to bind to {FIXED_IP}:{PORT} - {e}")
            print("Make sure the IP address is properly configured on your network interface.")
            return
        
        server_socket.listen(1)
        server_socket.settimeout(1)  # Allow periodic checking of self.running
        
        print(f"Server listening on {FIXED_IP}:{PORT}...")
         
        try:
            while self.running:
                try:
                    client_socket, addr = server_socket.accept()
                    self.handle_client(client_socket, addr)
                except socket.timeout:
                    continue
                except Exception as e:
                    print(f"Server error: {e}")
                    break
        except KeyboardInterrupt:
            print("\nShutting down server...")
        finally:
            self.running = False
            server_socket.close()
            if self.zeroconf:
                self.zeroconf.unregister_all_services()
                self.zeroconf.close()
            print("Server stopped")

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