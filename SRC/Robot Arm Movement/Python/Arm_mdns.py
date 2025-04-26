import socket
import time
from zeroconf import ServiceInfo, Zeroconf
import keyboard
import threading

# Server configuration
PORT = 4000
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."

class ArmController:
    def __init__(self):
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
        
        # Home positions (zero angle positions)
        self.home_joint1 = 300
        self.home_joint2 = 300
        self.home_joint3 = 500
        
        # Angle ranges
        self.joint1_range = 180  # degrees
        self.joint2_range = 180  # degrees
        self.joint3_range = 180  # degrees

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

    def calculate_angle(self, current_value, home_value, range_degrees):
        """Calculate angle from potentiometer value relative to home position"""
        # Convert potentiometer value to angle relative to home position
        angle = ((current_value - home_value) / 1023.0) * range_degrees
        return round(angle, 1)

    def move_joint(self, joint, angle):
        """Send joint movement command: J<joint_num><angle>"""
        cmd = f"J{joint}{self.format_angle(angle)}"
        self.send_command(cmd)
        
        # Update local position and show angle
        if joint == 1:
            self.joint1 = angle
            current_angle = self.calculate_angle(angle, self.home_joint1, self.joint1_range)
            print(f"Joint 1: {current_angle}°")
        elif joint == 2:
            self.joint2 = angle
            current_angle = self.calculate_angle(angle, self.home_joint2, self.joint2_range)
            print(f"Joint 2: {current_angle}°")
        elif joint == 3:
            self.joint3 = angle
            current_angle = self.calculate_angle(angle, self.home_joint3, self.joint3_range)
            print(f"Joint 3: {current_angle}°")

    def move_all_joints(self, j1, j2, j3):
        """Move all joints simultaneously: A<j1><j2><j3>"""
        cmd = f"A{self.format_angle(j1)}{self.format_angle(j2)}{self.format_angle(j3)}"
        self.send_command(cmd)
        self.joint1, self.joint2, self.joint3 = j1, j2, j3
        # Show angles after movement
        print(f"Joint 1: {self.calculate_angle(j1, self.home_joint1, self.joint1_range)}°")
        print(f"Joint 2: {self.calculate_angle(j2, self.home_joint2, self.joint2_range)}°")
        print(f"Joint 3: {self.calculate_angle(j3, self.home_joint3, self.joint3_range)}°")

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
        hostname = socket.gethostname()
        try:
            local_ip = socket.gethostbyname(hostname)
            service_info = ServiceInfo(
                SERVICE_TYPE,
                f"{SERVER_NAME}.{SERVICE_TYPE}",
                addresses=[socket.inet_aton(local_ip)],
                port=PORT,
                server=f"{SERVER_NAME}.",
            )
            
            self.zeroconf = Zeroconf()
            self.zeroconf.register_service(service_info)
            print(f"mDNS service registered as {SERVER_NAME} on {local_ip}:{PORT}")
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

    def input_handler(self):
        """Handle keyboard input for arm control"""
        print("Controls:")
        print("Joint 1: Q/A")
        print("Joint 2: W/S")
        print("Joint 3: E/D")
        print("Base: R/F")
        print("Gripper Rotate: T/G")
        print("Gripper Claw Controls:")
        print("  Y/H: Continuous open/close")
        print("  Preset Positions:")
        print("    0: 0 degrees (fully closed)")
        print("    4: 45 degrees")
        print("    9: 90 degrees")
        print("    3: 135 degrees")
        print("    8: 180 degrees (fully open)")
        print("Speed: +/-")
        print("Claw Speed: U/J")
        print("Preset 1: 1 (Home)")
        print("Preset 2: 2 (Extended)")
        print("Preset 3: 3 (cam vertical on table)")
        print("Stop: SPACE")
        print("Quit: ESC")
        
        while self.running:
            # Joint 1 controls
            if keyboard.is_pressed('q'):
                self.move_joint(1, self.joint1 + self.speed)
                while keyboard.is_pressed('q'): pass
            
            elif keyboard.is_pressed('a'):
                self.move_joint(1, self.joint1 - self.speed)
                while keyboard.is_pressed('a'): pass
            
            # Joint 2 controls
            elif keyboard.is_pressed('w'):
                self.move_joint(2, self.joint2 + self.speed)
                while keyboard.is_pressed('w'): pass
            
            elif keyboard.is_pressed('s'):
                self.move_joint(2, self.joint2 - self.speed)
                while keyboard.is_pressed('s'): pass
            
            # Joint 3 controls
            elif keyboard.is_pressed('e'):
                self.move_joint(3, self.joint3 + self.speed)
                while keyboard.is_pressed('e'): pass
            
            elif keyboard.is_pressed('d'):
                self.move_joint(3, self.joint3 - self.speed)
                while keyboard.is_pressed('d'): pass

            # Base rotation controls
            elif keyboard.is_pressed('r'):
                self.move_base(self.base_angle + 250)  # Rotate clockwise
                while keyboard.is_pressed('r'): pass
            
            elif keyboard.is_pressed('f'):
                self.move_base(self.base_angle - 250)  # Rotate counter-clockwise
                while keyboard.is_pressed('f'): pass

            # Gripper rotation controls
            elif keyboard.is_pressed('t'):
                self.move_gripper_rotate(self.gripper_rotate + 30)
                while keyboard.is_pressed('t'): pass
            
            elif keyboard.is_pressed('g'):
                self.move_gripper_rotate(self.gripper_rotate - 30)
                while keyboard.is_pressed('g'): pass

            # Gripper claw continuous controls
            elif keyboard.is_pressed('y'):
                self.move_gripper_claw(self.gripper_claw + self.claw_speed)
                while keyboard.is_pressed('y'): pass
            
            elif keyboard.is_pressed('h'):
                self.move_gripper_claw(self.gripper_claw - self.claw_speed)
                while keyboard.is_pressed('h'): pass

            # Claw speed adjustment
            elif keyboard.is_pressed('u'):
                self.claw_speed = min(60, self.claw_speed + 5)
                print(f"Claw Speed: {self.claw_speed}")
                while keyboard.is_pressed('u'): pass
            
            elif keyboard.is_pressed('j'):
                self.claw_speed = max(5, self.claw_speed - 5)
                print(f"Claw Speed: {self.claw_speed}")
                while keyboard.is_pressed('j'): pass

            # Preset positions
            elif keyboard.is_pressed('1'):  # Home position
                self.move_all_joints(self.home_joint1, self.home_joint2, self.home_joint3)
                print("Moving to home position (zero angles)")
                while keyboard.is_pressed('1'): pass
            
            elif keyboard.is_pressed('2'):  # Extended position
                self.move_all_joints(500, 500, 500)
                while keyboard.is_pressed('2'): pass
            
            elif keyboard.is_pressed('3'):  # Camera vertical position
                self.move_all_joints(300, 500, 300)
                while keyboard.is_pressed('3'): pass

            # Emergency stop
            elif keyboard.is_pressed('esc'):
                self.running = False
            
            time.sleep(0.01)  # Small delay to prevent CPU overuse

    def run_server(self):
        """Main server loop"""
        self.start_mdns_service()
        
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind(('0.0.0.0', PORT))
        server_socket.listen(1)
        server_socket.settimeout(1)  # Allow periodic checking of self.running
        
        print(f"Server listening on port {PORT}...")
        
        # Start input handler in separate thread
        input_thread = threading.Thread(target=self.input_handler)
        input_thread.daemon = True
        input_thread.start()
        
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
            input_thread.join()
            print("Server stopped")

if __name__ == "__main__":
    controller = ArmController()
    controller.run_server()
