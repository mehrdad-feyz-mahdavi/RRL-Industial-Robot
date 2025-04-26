import socket
import time
from zeroconf import ServiceInfo, Zeroconf
import threading
import rclpy
from rclpy.node import Node
from robot_control_interfaces.msg import ArmCommand
from sensor_msgs.msg import JointState
from trajectory_msgs.msg import JointTrajectory
import math
import signal

# Server configuration
PORT = 4000
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."
FIXED_IP = "192.168.81.123"
USE_MDNS = True  # Set to False if mDNS is causing issues

# Joint configuration
JOINT_NAMES = ['arm_base_joint', 'a2', 'a3', 'a4', 'bg', 'g1']

# Joint limits and conversion factors
JOINT_LIMITS = {
    'arm_base_joint': {'min': -math.pi, 'max': 0, 'servo_min': 0, 'servo_max': 500},
    'a2': {'min': -2.30383, 'max': 0, 'servo_min': 0, 'servo_max': 1023},
    'a3': {'min': -1.7453, 'max': 1.7453, 'servo_min': 0, 'servo_max': 1023},
    'a4': {'min': -1.57, 'max': 1.57, 'servo_min': 0, 'servo_max': 1023},
    'bg': {'min': -math.pi, 'max': math.pi, 'servo_min': 0, 'servo_max': 270},
    'g1': {'min': -0.288, 'max': 0.134, 'servo_min': 0, 'servo_max': 180}
}

class ArmController(Node):
    def __init__(self):
        super().__init__('arm_controller')
        self.client_socket = None
        self.zeroconf = None
        self.connection_lock = threading.Lock()
        self.connected = False
        self.running = True  # Initialize running flag
        self.server_socket = None  # Initialize server socket
        
        # Initialize joint positions to zero
        self.joint_positions = {
            'arm_base_joint': 0.0,
            'a2': 0.0,
            'a3': 0.0,
            'a4': 0.0,
            'bg': 0.0,
            'g1': 0.0
        }
        
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

        # Create joint state publisher with explicit QoS settings
        self.joint_state_pub = self.create_publisher(
            JointState,
            '/joint_states',
            rclpy.qos.QoSProfile(
                depth=10,
                durability=rclpy.qos.QoSDurabilityPolicy.VOLATILE,
                reliability=rclpy.qos.QoSReliabilityPolicy.BEST_EFFORT
            ))
        
        # Create timer for periodic joint state publishing
        self.timer = self.create_timer(0.1, self.publish_joint_states)  # 10Hz
        
        # Start the server in a separate thread
        self.server_thread = threading.Thread(target=self.run_server)
        self.server_thread.daemon = True
        self.server_thread.start()
        
        # Wait for connection
        self.get_logger().info("Waiting for ESP8266 connection...")
        while not self.connected and self.running:
            time.sleep(0.1)
        
        if self.connected:
            self.get_logger().info("Connected to ESP8266")
        else:
            self.get_logger().error("Failed to connect to ESP8266")

    def convert_to_servo(self, joint_name, radian_value):
        """Convert from radians to servo angle"""
        limits = JOINT_LIMITS[joint_name]
        # Normalize to [0,1]
        normalized = (radian_value - limits['min']) / (limits['max'] - limits['min'])
        # Convert to servo range
        servo_value = limits['servo_min'] + normalized * (limits['servo_max'] - limits['servo_min'])
        # Round and clamp
        return int(max(limits['servo_min'], min(limits['servo_max'], round(servo_value))))

    def convert_to_radians(self, joint_name, servo_value):
        """Convert from servo angle to radians"""
        limits = JOINT_LIMITS[joint_name]
        # Normalize to [0,1]
        normalized = (servo_value - limits['servo_min']) / (limits['servo_max'] - limits['servo_min'])
        # Convert to radians
        return limits['min'] + normalized * (limits['max'] - limits['min'])

    def format_angle(self, angle):
        """Convert angle to 4-character string (0-1023)"""
        return f"{int(angle):04d}"

    def send_command(self, cmd):
        """Send command to ESP8266"""
        with self.connection_lock:
            if self.connected and self.client_socket:
                try:
                    full_cmd = f"{cmd}E"
                    self.client_socket.sendall(full_cmd.encode())
                    self.get_logger().info(f'Sent command: {full_cmd}')
                except (ConnectionResetError, BrokenPipeError, OSError) as e:
                    self.get_logger().error(f'Connection error: {e}')
                    self.connected = False
                    if self.client_socket:
                        self.client_socket.close()
                        self.client_socket = None
            else:
                self.get_logger().warn(f'Cannot send command: Not connected to ESP8266')

    def move_joint(self, joint_name, angle_rad):
        """Send joint movement command: J<joint_num><angle>"""
        # Clamp angle to joint limits
        limits = JOINT_LIMITS[joint_name]
        angle_rad = max(limits['min'], min(limits['max'], angle_rad))
        
        # Log the movement
        self.get_logger().info(f"Moving {joint_name} to {angle_rad} radians (clamped to limits [{limits['min']}, {limits['max']}])")
        
        servo_angle = self.convert_to_servo(joint_name, angle_rad)
        joint_num = {'a2': 2, 'a3': 3, 'a4': 1}.get(joint_name)
        if joint_num:
            cmd = f"J{joint_num}{self.format_angle(servo_angle)}"
            self.get_logger().info(f"Sending command: {cmd}")
            self.send_command(cmd)
            self.joint_positions[joint_name] = angle_rad
            self.get_logger().info(f"Updated {joint_name} position to {angle_rad}")

    def move_base(self, angle_rad):
        """Send base rotation command: B<angle>"""
        # Clamp angle to joint limits
        limits = JOINT_LIMITS['arm_base_joint']
        angle_rad = max(limits['min'], min(limits['max'], angle_rad))
        
        servo_angle = self.convert_to_servo('arm_base_joint', angle_rad)
        cmd = f"B{servo_angle}"
        self.send_command(cmd)
        self.joint_positions['arm_base_joint'] = angle_rad

    def move_gripper_rotate(self, angle_rad):
        """Send gripper rotation command: GR<angle>"""
        # Clamp angle to joint limits
        limits = JOINT_LIMITS['bg']
        angle_rad = max(limits['min'], min(limits['max'], angle_rad))
        
        servo_angle = self.convert_to_servo('bg', angle_rad)
        cmd = f"GR{servo_angle}"
        self.send_command(cmd)
        self.joint_positions['bg'] = angle_rad

    def move_gripper_claw(self, angle_rad):
        """Send gripper claw command: GC<angle>"""
        # Clamp angle to joint limits
        limits = JOINT_LIMITS['g1']
        angle_rad = max(limits['min'], min(limits['max'], angle_rad))
        
        servo_angle = self.convert_to_servo('g1', angle_rad)
        cmd = f"GC{servo_angle}"
        self.send_command(cmd)
        self.joint_positions['g1'] = angle_rad

    def arm_controller_callback(self, msg):
        """Handle incoming arm controller commands from MoveIt"""
        if not self.connected:
            self.get_logger().warn('Cannot process command: Not connected to arm server')
            return
            
        # Get the last point in the trajectory
        if not msg.points:
            self.get_logger().warn('Received empty trajectory')
            return
            
        last_point = msg.points[-1]
        
        # Log the received trajectory
        self.get_logger().info(f"Received trajectory with {len(msg.points)} points")
        self.get_logger().info(f"Joint names: {msg.joint_names}")
        self.get_logger().info(f"Last point positions: {last_point.positions}")
        
        # Process each joint in the correct order
        for joint_name in ['arm_base_joint', 'a2', 'a3', 'a4']:
            if joint_name in msg.joint_names:
                idx = msg.joint_names.index(joint_name)
                position = last_point.positions[idx]
                
                # Clamp position to joint limits
                limits = JOINT_LIMITS[joint_name]
                position = max(limits['min'], min(limits['max'], position))
                
                # Debug logging
                self.get_logger().info(f"Moving {joint_name} to {position} radians")
                
                if joint_name == 'arm_base_joint':
                    self.move_base(position)
                else:
                    self.move_joint(joint_name, position)
                
                # Update joint position
                self.joint_positions[joint_name] = position
                
                # Small delay between joint movements
                time.sleep(0.1)

    def gripper_controller_callback(self, msg):
        """Handle incoming gripper controller commands"""
        if not self.connected:
            self.get_logger().warn('Cannot process command: Not connected to arm server')
            return
            
        # Get the last point in the trajectory
        if not msg.points:
            return
            
        last_point = msg.points[-1]
        
        # Map joint names to their positions
        for i, joint_name in enumerate(msg.joint_names):
            if joint_name == 'bg':
                # Debug logging
                self.get_logger().debug(f"Received command for {joint_name}: {last_point.positions[i]}")
                self.move_gripper_rotate(last_point.positions[i])
            elif joint_name == 'g1':
                # Debug logging
                self.get_logger().debug(f"Received command for {joint_name}: {last_point.positions[i]}")
                self.move_gripper_claw(last_point.positions[i])

    def publish_joint_states(self):
        """Publish current joint states"""
        joint_state = JointState()
        joint_state.header.stamp = self.get_clock().now().to_msg()
        joint_state.header.frame_id = "base_link"  # Must match URDF
        joint_state.name = JOINT_NAMES
        joint_state.position = [self.joint_positions[name] for name in JOINT_NAMES]
        joint_state.velocity = [0.0] * len(JOINT_NAMES)  # Velocity not supported
        joint_state.effort = [float('nan')] * len(JOINT_NAMES)  # Effort not supported
        
        # Debug logging before publishing
        self.get_logger().info("=== Publishing Joint States ===")
        self.get_logger().info(f"Header: stamp={joint_state.header.stamp}, frame_id={joint_state.header.frame_id}")
        self.get_logger().info(f"Joint names: {joint_state.name}")
        self.get_logger().info(f"Positions: {joint_state.position}")
        self.get_logger().info(f"Velocities: {joint_state.velocity}")
        self.get_logger().info(f"Efforts: {joint_state.effort}")
        
        # Verify joint limits
        for name, position in zip(joint_state.name, joint_state.position):
            limits = JOINT_LIMITS[name]
            if position < limits['min'] or position > limits['max']:
                self.get_logger().warn(f"Joint {name} position {position} is outside limits [{limits['min']}, {limits['max']}]")
                # Clamp the value
                self.joint_positions[name] = max(limits['min'], min(limits['max'], position))
                self.get_logger().warn(f"Clamped {name} to {self.joint_positions[name]}")
        
        # Publish the joint state
        self.joint_state_pub.publish(joint_state)
        self.get_logger().info("=== Joint States Published ===")

    def start_mdns_service(self):
        """Start mDNS service for network discovery"""
        if not USE_MDNS:
            self.get_logger().info("mDNS service disabled")
            return
            
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
            self.get_logger().warn(f"Failed to start mDNS: {e}. Continuing without mDNS...")

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
        
        try:
            self.server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self.server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
            self.server_socket.bind((FIXED_IP, PORT))
            self.server_socket.listen(1)
            self.server_socket.settimeout(1)  # Allow periodic checking of self.running
            
            self.get_logger().info(f"Server listening on {FIXED_IP}:{PORT}...")
            
            while self.running:
                try:
                    client_socket, addr = self.server_socket.accept()
                    self.get_logger().info(f"Accepted connection from {addr}")
                    self.handle_client(client_socket, addr)
                except socket.timeout:
                    continue
                except Exception as e:
                    if self.running:  # Only log if we're not shutting down
                        self.get_logger().error(f"Server error: {e}")
                    break
        except OSError as e:
            self.get_logger().error(f"Failed to start server: {e}")
            if e.errno == 98:  # Address already in use
                self.get_logger().error("Port 4000 is already in use. Try killing existing processes or wait a moment and try again.")
            elif e.errno == 99:  # Cannot assign requested address
                self.get_logger().error("Failed to bind to the network interface. Check your network configuration.")
            else:
                self.get_logger().error("Unexpected error occurred while starting the server.")
        except Exception as e:
            self.get_logger().error(f"Unexpected error: {e}")
        finally:
            self.cleanup()

    def cleanup(self):
        """Cleanup resources"""
        self.running = False
        
        if self.client_socket:
            try:
                self.client_socket.close()
            except:
                pass
                
        if self.server_socket:
            try:
                self.server_socket.close()
            except:
                pass
                
        if self.zeroconf:
            try:
                self.zeroconf.unregister_all_services()
                self.zeroconf.close()
            except:
                pass
                
        self.get_logger().info("Server stopped")

def main(args=None):
    rclpy.init(args=args)
    controller = None
    
    try:
        controller = ArmController()
        
        # Set up signal handler for graceful shutdown
        def signal_handler(sig, frame):
            if controller:
                controller.get_logger().info("Received shutdown signal")
                controller.running = False
        
        signal.signal(signal.SIGINT, signal_handler)
        signal.signal(signal.SIGTERM, signal_handler)
        
        # Run ROS node in a separate thread
        ros_thread = threading.Thread(target=rclpy.spin, args=(controller,))
        ros_thread.daemon = True
        ros_thread.start()
        
        # Run the server in the main thread
        controller.run_server()
        
    except Exception as e:
        if controller:
            controller.get_logger().error(f"Fatal error: {e}")
    finally:
        if controller:
            controller.destroy_node()
        rclpy.shutdown()

if __name__ == "__main__":
    main()