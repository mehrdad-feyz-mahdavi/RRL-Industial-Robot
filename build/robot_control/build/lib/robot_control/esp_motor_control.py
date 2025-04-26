import random
import socket
from zeroconf import ServiceInfo, Zeroconf
import keyboard
import time
import json
from datetime import datetime
import threading
import cv2
from ultralytics import YOLO
import numpy as np
import os

# Server configuration for robot control
ROBOT_PORT = 3001
ARM_PORT = 4000
SERVER_IP = "192.168.81.123"
SERVER_NAME = "laptop.local"
SERVICE_TYPE = "_http._tcp.local."

# Motor speed constants
MOTOR_SPEED = 20  # Default motor speed
TURN_SPEED = 20   # Speed for turning

# Arm initial positions
JOINT1_INITIAL = 300
JOINT2_INITIAL = 300
JOINT3_INITIAL = 500
BASE_INITIAL = 0
GRIPPER_ROTATE_INITIAL = 90
GRIPPER_CLAW_INITIAL = 0

class RobotArmController:
    def __init__(self):
        self.client_socket = None
        self.zeroconf = None
        self.joint1 = JOINT1_INITIAL
        self.joint2 = JOINT2_INITIAL
        self.joint3 = JOINT3_INITIAL
        self.base_angle = BASE_INITIAL
        self.gripper_rotate = GRIPPER_ROTATE_INITIAL
        self.gripper_claw = GRIPPER_CLAW_INITIAL
        self.running = True

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
                print(f"Sent arm command: {cmd}")
                return full_cmd
            except (ConnectionResetError, BrokenPipeError, OSError) as e:
                print(f"Arm connection error: {e}")
                self.client_socket = None
        return None

    def move_joint(self, joint, angle):
        """Send joint movement command: J<joint_num><angle>"""
        cmd = f"J{joint}{self.format_angle(angle)}"
        result = self.send_command(cmd)
        
        # Update local position
        if joint == 1:
            self.joint1 = angle
        elif joint == 2:
            self.joint2 = angle
        elif joint == 3:
            self.joint3 = angle
        return result

    def move_all_joints(self, j1, j2, j3):
        """Move all joints simultaneously: A<j1><j2><j3>"""
        cmd = f"A{self.format_angle(j1)}{self.format_angle(j2)}{self.format_angle(j3)}"
        result = self.send_command(cmd)
        self.joint1, self.joint2, self.joint3 = j1, j2, j3
        return result

    def move_base(self, angle):
        """Send base rotation command: B<angle>"""
        angle = max(0, min(500, int(angle)))
        cmd = f"B{angle}"
        result = self.send_command(cmd)
        self.base_angle = angle
        return result

    def move_gripper_rotate(self, angle):
        """Send gripper rotation command: GR<angle>"""
        angle = max(0, min(270, int(angle)))
        cmd = f"GR{angle}"
        result = self.send_command(cmd)
        self.gripper_rotate = angle
        return result

    def move_gripper_claw(self, angle):
        """Send gripper claw command: GC<angle>"""
        angle = max(0, min(180, int(angle)))
        cmd = f"GC{angle}"
        result = self.send_command(cmd)
        self.gripper_claw = angle
        return result

    def start_mdns_service(self):
        """Start mDNS service for arm control"""
        service_info = ServiceInfo(
            SERVICE_TYPE,
            f"{SERVER_NAME}_arm.{SERVICE_TYPE}",
            addresses=[socket.inet_aton(SERVER_IP)],
            port=ARM_PORT,
            server=f"{SERVER_NAME}.",
        )
        
        self.zeroconf = Zeroconf()
        self.zeroconf.register_service(service_info)
        print(f"Arm mDNS service registered as {SERVER_NAME}_arm on {SERVER_IP}:{ARM_PORT}")

    def connect_to_esp(self):
        """Initialize connection to ESP8266 for arm control"""
        self.start_mdns_service()
        
        server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
        server_socket.bind((SERVER_IP, ARM_PORT))
        server_socket.listen(1)
        
        print(f"Arm server listening on {SERVER_IP}:{ARM_PORT}...")
        
        client_socket, addr = server_socket.accept()
        print(f"Connected to arm ESP8266 at {addr}")
        
        client_socket.settimeout(0.1)
        self.client_socket = client_socket
        return client_socket, server_socket, self.zeroconf

class CameraController:
    def __init__(self):
        self.camera_id = 0
        self.width = 1280
        self.height = 720
        self.fps = 90
        self.enable_detection = True
        self.cap = None
        self.model = None
        self.frame_lock = threading.Lock()
        self.latest_frame = None
        self.latest_detections = []
        self.running = True
        self.confidence_threshold = 0.7
        self.display_frame = True  # New flag to control frame display
        
        # Initialize camera and YOLO
        self.init_camera()
        self.init_yolo()
        
        # Start capture thread
        self.capture_thread = threading.Thread(target=self._capture_loop)
        self.capture_thread.daemon = True
        self.capture_thread.start()
        
        # Start detection thread
        self.detection_thread = threading.Thread(target=self._detection_loop)
        self.detection_thread.daemon = True
        self.detection_thread.start()

    def init_camera(self):
        """Initialize the camera with proper settings"""
        try:
            self.cap = cv2.VideoCapture(self.camera_id)
            if not self.cap.isOpened():
                print(f"Failed to open camera {self.camera_id}")
                return False
                
            # Configure camera settings
            self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, self.width)
            self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, self.height)
            self.cap.set(cv2.CAP_PROP_FPS, self.fps)
            self.cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)
            
            actual_width = self.cap.get(cv2.CAP_PROP_FRAME_WIDTH)
            actual_height = self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
            actual_fps = self.cap.get(cv2.CAP_PROP_FPS)
            
            print(f'Camera initialized with: {actual_width}x{actual_height} @ {actual_fps}fps')
            return True
            
        except Exception as e:
            print(f'Error initializing camera: {str(e)}')
            return False

    def init_yolo(self):
        """Initialize YOLO model"""
        try:
            model_path = 'best.pt'  # Make sure this file exists in your working directory
            self.model = YOLO(model_path)
            print(f'Successfully loaded YOLO model from {model_path}')
        except Exception as e:
            print(f'Failed to load YOLO model: {str(e)}')
            self.enable_detection = False

    def _capture_loop(self):
        """Continuous frame capture loop"""
        while self.running:
            if not self.cap or not self.cap.isOpened():
                print('Camera disconnected, attempting to reconnect...')
                if self.init_camera():
                    print('Successfully reconnected to camera')
                else:
                    print('Failed to reconnect to camera')
                    time.sleep(1.0)
                continue
                
            ret, frame = self.cap.read()
            if ret:
                with self.frame_lock:
                    self.latest_frame = frame
            else:
                print('Failed to capture frame')
                self.cap.release()
            time.sleep(0.01)  # Small delay to prevent CPU overuse

    def _detection_loop(self):
        """Continuous object detection loop"""
        while self.running and self.enable_detection:
            with self.frame_lock:
                frame = self.latest_frame
                if frame is None:
                    time.sleep(0.01)
                    continue
            
            try:
                # Run YOLO inference
                results = self.model(frame, conf=self.confidence_threshold)
                
                detections = []
                # Create a copy of frame for visualization
                display_frame = frame.copy()
                
                for result in results:
                    for box in result.boxes:
                        # Get detection details
                        x1, y1, x2, y2 = map(int, box.xyxy[0])
                        confidence = box.conf[0].item()
                        class_id = int(box.cls[0])
                        class_name = self.model.names[class_id]
                        
                        # Calculate center point
                        center_x = (x1 + x2) // 2
                        center_y = (y1 + y2) // 2
                        
                        detections.append({
                            'class_id': class_id,
                            'class_name': class_name,
                            'confidence': confidence,
                            'center_x': center_x,
                            'center_y': center_y,
                            'x1': x1,
                            'y1': y1,
                            'x2': x2,
                            'y2': y2
                        })
                        
                        # Draw bounding box
                        cv2.rectangle(display_frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        
                        # Add label with class name and confidence
                        label = f"{class_name}: {confidence:.2f}"
                        cv2.putText(display_frame, label, (x1, y1 - 10),
                                  cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
                        
                        # Draw center point
                        cv2.circle(display_frame, (center_x, center_y), 4, (0, 0, 255), -1)
                
                self.latest_detections = detections
                
                # Display the frame
                if self.display_frame:
                    cv2.imshow('Robot Camera Feed', display_frame)
                    cv2.waitKey(1)
                
            except Exception as e:
                print(f'Error in YOLO processing: {str(e)}')
            
            time.sleep(0.1)  # Process at 10 FPS to not overload the system

    def get_latest_detections(self):
        """Get the latest detections"""
        return self.latest_detections

    def cleanup(self):
        """Clean up resources"""
        print("Stopping camera threads...")
        self.running = False
        
        # Wait for threads to finish with timeout
        if self.capture_thread.is_alive():
            self.capture_thread.join(timeout=2.0)
        if self.detection_thread.is_alive():
            self.detection_thread.join(timeout=2.0)
            
        # Release camera
        if self.cap and self.cap.isOpened():
            print("Releasing camera...")
            self.cap.release()
            
        # Close any open windows
        cv2.destroyAllWindows()
        print("Camera cleanup completed")

def format_speed(speed):
    """Format speed value for ESP command"""
    return f"{'+' if speed >= 0 else '-'}{abs(speed):03d}"

def motor(client_socket, L1, L2, R2, R1, max_retries=3):
    """
    Send motor commands to ESP8266 with retry logic
    Args:
        client_socket: Connected socket to ESP8266
        L1: Front left motor speed (-255 to 255)
        L2: Rear left motor speed (-255 to 255)
        R2: Rear right motor speed (-255 to 255)
        R1: Front right motor speed (-255 to 255)
        max_retries: Maximum number of retry attempts
    """
    if not client_socket:
        print("No connection to robot")
        return None
        
    cmd = f"M{format_speed(L1)}{format_speed(L2)}{format_speed(R2)}{format_speed(R1)}E"
    
    for attempt in range(max_retries):
        try:
            client_socket.sendall(cmd.encode())
            time.sleep(0.05)  # Add small delay between commands
            return cmd  # Return the command for recording
        except (ConnectionResetError, BrokenPipeError, TimeoutError) as e:
            if attempt == max_retries - 1:  # Last attempt
                print(f"Connection error in motor command after {max_retries} attempts: {e}")
                return None
            time.sleep(0.1)  # Wait before retry
        except Exception as e:
            print(f"Unexpected error in motor command: {e}")
            return None
    return None

def connect_to_esp():
    """Initialize connection to ESP8266"""
    # Start mDNS service
    service_info = ServiceInfo(
        SERVICE_TYPE,
        f"{SERVER_NAME}_robot.{SERVICE_TYPE}",
        addresses=[socket.inet_aton(SERVER_IP)],
        port=ROBOT_PORT,
        server=f"{SERVER_NAME}.",
    )
    
    zeroconf = Zeroconf()
    zeroconf.register_service(service_info)
    print(f"Robot mDNS service registered as {SERVER_NAME}_robot on {SERVER_IP}:{ROBOT_PORT}")
    
    # Create and configure server socket
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    server_socket.bind((SERVER_IP, ROBOT_PORT))
    server_socket.listen(1)
    
    print(f"Server listening on {SERVER_IP}:{ROBOT_PORT}...")
    
    # Wait for ESP8266 connection
    client_socket, addr = server_socket.accept()
    print(f"Connected to robot ESP8266 at {addr}")
    
    # Set timeout for reading data
    client_socket.settimeout(0.1)  # 100ms timeout
    
    return client_socket, server_socket, zeroconf

def cleanup(client_socket, server_socket, zeroconf):
    """Cleanup function to close connections"""
    client_socket.close()
    server_socket.close()
    zeroconf.unregister_all_services()
    zeroconf.close()

def save_recording(recording_data, filename):
    """Save recorded commands to a file"""
    with open(filename, 'w') as f:
        json.dump(recording_data, f, indent=2)
    print(f"Recording saved to {filename}")

def load_recording(filename):
    """Load recorded commands from a file"""
    with open(filename, 'r') as f:
        return json.load(f)

def playback_recording(robot_socket, arm_controller, recording_data):
    """Playback recorded commands"""
    print("Playing back recorded commands...")
    start_time = time.time()
    
    for entry in recording_data:
        # Wait until the correct timestamp
        while (time.time() - start_time) < entry['timestamp']:
            time.sleep(0.01)
        
        # Execute the command
        if entry['command']:
            if entry['command'].startswith('M'):  # Robot movement command
                print(f"Executing robot command: {entry['command']}")
                robot_socket.sendall(entry['command'].encode())
            elif entry['command'].startswith(('J', 'A', 'B', 'G')):  # Arm command
                print(f"Executing arm command: {entry['command']}")
                arm_controller.client_socket.sendall(entry['command'].encode())
    
    print("Playback completed")
    # Stop both robot and arm
    robot_socket.sendall("M+000+000+000+000E".encode())

def track_object(robot_socket, camera_controller, target_x=350, target_y=320, tolerance=15, target_class_id=3):
    """
    Move robot to center the object with specified class_id
    Returns True if object is centered, False if object not found or error
    """
    try:
        detections = camera_controller.get_latest_detections()
        target_obj = None
        
        # Find object with specified class_id
        for det in detections:
            if det['class_id'] == target_class_id:
                target_obj = det
                break
        
        if not target_obj:
            # If object not found, perform search pattern
            search_speed = 15
            search_cycles = 20
            
            # Use static variable to track search state
            if not hasattr(track_object, 'search_count'):
                track_object.search_count = 0
                track_object.search_right = random.choice([True, False])
            
            # Move right for 20 cycles then left for 20 cycles
            if track_object.search_right:
                motor(robot_socket, search_speed, -search_speed, -search_speed, search_speed)
            else:
                motor(robot_socket, -search_speed, search_speed, search_speed, -search_speed)
                
            track_object.search_count += 1
            if track_object.search_count >= search_cycles:
                track_object.search_count = 0
                track_object.search_right = not track_object.search_right
                
            time.sleep(0.1)  # Wait between movements
            return False
            
        # Get current position
        current_x = target_obj['center_x']
        current_y = target_obj['center_y']
        
        # Calculate errors
        error_x = target_x - current_x
        error_y = target_y - current_y
        
        # Check if object is centered within tolerance
        if abs(error_x) <= tolerance and abs(error_y) <= tolerance:
            motor(robot_socket, 0, 0, 0, 0)
            time.sleep(0.1)  # Wait after stop command
            return True
            
        # Adjust speed based on error magnitude (proportional control)
        base_speed = 18
        
        # Add proportional control
        x_scale = min(1.0, abs(error_x) / 180)  # Scale based on error magnitude
        y_scale = min(1.0, abs(error_y) / 180)
        
        # Move left/right to center horizontally
        if abs(error_x) > tolerance:
            speed = int(base_speed * x_scale)
            if error_x > 0:  # Need to move right
                if not motor(robot_socket, speed, -speed, -speed, speed):
                    time.sleep(0.1)
                    return False
            else:  # Need to move left
                if not motor(robot_socket, -speed, speed, speed, -speed):
                    time.sleep(0.1)
                    return False
        # Move forward/backward to center vertically
        elif abs(error_y) > tolerance:
            speed = int(base_speed * y_scale)
            if error_y > 0:  # Need to move backward
                if not motor(robot_socket, speed, speed, -speed, -speed):
                    time.sleep(0.1)
                    return False
            else:  # Need to move forward
                if not motor(robot_socket, -speed, -speed, speed, speed):
                    time.sleep(0.1)
                    return False
                
        time.sleep(0.05)  # Small delay between movements
        return False
        
    except Exception as e:
        print(f"Error in tracking: {e}")
        try:
            motor(robot_socket, 0, 0, 0, 0)
            time.sleep(0.1)
        except:
            pass
        return False

def perform_arm_movement_with_delay(arm_controller, movement_name, joint_positions, delay=5.0):
    """
    Perform a set of arm movements with a delay
    Args:
        arm_controller: The arm controller instance
        movement_name: Name of the movement sequence (for logging)
        joint_positions: Dictionary of joint numbers and their target positions
        delay: Delay in seconds after movements
    """
    print(f"\nExecuting {movement_name}...")
    try:
        for joint_num, position in joint_positions.items():
            if joint_num == 5:
                arm_controller.move_gripper_claw(position)
            elif joint_num == 4:
                arm_controller.move_base(position)
            else:
                arm_controller.move_joint(joint_num, position)
            time.sleep(0.2)  # Small delay between joint movements
        print(f"Waiting {delay} seconds...")
        time.sleep(delay)
        print(f"Completed {movement_name}")
        return True
    except Exception as e:
        print(f"Error during {movement_name}: {e}")
        return False

def save_tracking_sequence(filename):
    """Save the tracking sequence to a file"""
    tracking_sequence = {
        "type": "tracking_sequence",
        "grabbing_sequence": [
            ("Initial approach", {
                1: 990,   # Joint 1
                2: 850,   # Joint 2
                3: 500,   # Joint 3
                5: 0      # Gripper open
            }),
            ("Lower arm", {
                1: 890,
                2: 850,
                3: 450,
                5: 90     # Close gripper
            }),
            ("Close gripper", {
                1: 600,
                2: 850,
                3: 450,
                5: 90     # Close gripper
            }),
            ("Lift object", {
                1: 400,
                2: 500,
                3: 300
            }),
            ("Lift object", {
                1: 400,
                2: 500,
                3: 300,
            }),
            ("Lift object", {
                4: 180,
            }),
            ("Lift object", {
                1: 600,
                2: 500,
                3: 300,
            }),
            ("Close gripper", {
                5: 0     # Close gripper
            }),
            ("Lift object", {
                1: 400,
                2: 500,
                3: 300,
            }),
            ("Close gripper", {
                4: 0
            })
        ]
    }
    with open(filename, 'w') as f:
        json.dump(tracking_sequence, f, indent=2)
    print(f"Tracking sequence saved to {filename}")

def execute_tracking_sequence(robot_socket, arm_controller, camera_controller):
    """Execute the tracking and grabbing sequence"""
    print("Starting tracking sequence...")
    try:
        # Initialize arm position
        arm_controller.move_joint(1, 700)
        time.sleep(0.2)
        arm_controller.move_joint(2, 850)
        time.sleep(0.2)
        arm_controller.move_joint(3, 100)
        time.sleep(0.2)
        arm_controller.move_gripper_claw(0)
        time.sleep(0.2)
        arm_controller.move_gripper_rotate(0)
        time.sleep(0.2)

        # Track object until centered
        while True:
            is_centered = track_object(robot_socket, camera_controller)
            if is_centered:
                print("Object centered!")
                break
            time.sleep(0.05)

        # Stop the robot
        motor(robot_socket, 0, 0, 0, 0)
        time.sleep(0.5)

        # Load and execute grabbing sequence
        with open('tracking_sequence.json', 'r') as f:
            sequence_data = json.load(f)
            
        if sequence_data["type"] == "tracking_sequence":
            for movement_name, joint_positions in sequence_data["grabbing_sequence"]:
                if not perform_arm_movement_with_delay(arm_controller, movement_name, joint_positions):
                    break
        
        print("Tracking sequence completed")
        return True
    except Exception as e:
        print(f"Error during tracking sequence: {e}")
        try:
            motor(robot_socket, 0, 0, 0, 0)
        except:
            pass
        return False

def save_recording_txt(recording_data, filename):
    """Save recorded commands to a text file in an editable format"""
    with open(filename, 'w') as f:
        f.write("# Robot and Arm Recording File\n")
        f.write("# Format: duration command [class_id]\n")
        f.write("# For tracking sequences: duration TRACK_AND_GRAB class_id\n")
        f.write("# For motor commands: duration Mspeed1speed2speed3speed4E\n")
        f.write("# For arm commands: duration [J|A|B|GR|GC]values\n\n")
        
        for entry in recording_data:
            if entry['command'] == 'TRACK_AND_GRAB':
                f.write(f"{entry['duration']:.2f} TRACK_AND_GRAB {entry.get('class_id', 3)}\n")
            else:
                f.write(f"{entry['duration']:.2f} {entry['command']}\n")

def load_recording_txt(filename):
    """Load recorded commands from a text file"""
    recording_data = []
    try:
        with open(filename, 'r') as f:
            lines = f.readlines()
            
        for line in lines:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
                
            parts = line.split()
            if len(parts) < 2:
                continue
                
            duration = float(parts[0])
            command = parts[1]
            
            if command == 'TRACK_AND_GRAB':
                class_id = int(parts[2]) if len(parts) > 2 else 3
                recording_data.append({
                    'duration': duration,
                    'command': 'TRACK_AND_GRAB',
                    'class_id': class_id,
                    'grabbing_sequence': [
                        ("Initial approach", {
                            1: 990,   # Joint 1
                            2: 850,   # Joint 2
                            3: 500,   # Joint 3
                            5: 0      # Gripper open
                        }),
                        ("Lower arm", {
                            1: 890,
                            2: 850,
                            3: 450,
                            5: 90     # Close gripper
                        }),
                        ("Close gripper", {
                            1: 600,
                            2: 850,
                            3: 450,
                            5: 90     # Close gripper
                        }),
                        ("Lift object", {
                            1: 400,
                            2: 500,
                            3: 300
                        }),
                        ("Lift object", {
                            1: 400,
                            2: 500,
                            3: 300,
                            4: 180,
                        }),
                        ("Lift object", {
                            1: 600,
                            2: 500,
                            3: 300,
                        }),
                        ("Close gripper", {
                            5: 0     # Close gripper
                        }),
                        ("Lift object", {
                            1: 400,
                            2: 500,
                            3: 300,
                        }),
                        ("Close gripper", {
                            4: 0
                        })
                    ]
                })
            else:
                recording_data.append({
                    'duration': duration,
                    'command': command
                })
                
        return recording_data
    except Exception as e:
        print(f"Error loading recording file: {e}")
        return []

def control_robot_and_arm(robot_socket, arm_controller, camera_controller):
    """Handle keyboard input for robot and arm control"""
    print("Robot Control:")
    print("Movement Controls:")
    print("W - Forward")
    print("S - Backward")
    print("A - Left")
    print("D - Right")
    print("Q - Turn Left")
    print("E - Turn Right")
    print("\nArm Controls:")
    print("T/G - Joint 1 up/down")
    print("Y/H - Joint 2 up/down")
    print("U/J - Joint 3 up/down")
    print("I/K - Base rotation left/right")
    print("O/L - Gripper rotation")
    print("N/M - Gripper claw open/close")
    print("\nSpecial Controls:")
    print("Z - Track object (class_id 3)")
    print("X + number key - Record tracking sequence for specific class ID")
    print("\nRecording Controls:")
    print("R - Start/Stop Recording")
    print("P - Playback recording")
    print("B - Load recording from text file")
    print("Press Ctrl+C to exit")
    
    recording = False
    recording_data = []
    last_command_time = None
    tracking_mode = False
    waiting_for_class_id = False
    
    try:
        while True:
            robot_command = None
            arm_command = None
            current_time = time.time()
            
            if keyboard.is_pressed('r'):  # Toggle recording
                time.sleep(0.2)  # Debounce
                if not recording:
                    recording = True
                    recording_data = []
                    last_command_time = time.time()
                    print("Recording started...")
                else:
                    recording = False
                    if recording_data:
                        filename = f"robot_arm_recording_{datetime.now().strftime('%Y%m%d_%H%M%S')}.txt"
                        save_recording_txt(recording_data, filename)
                    print("Recording stopped")
                continue

            if keyboard.is_pressed('b'):  # Load recording
                time.sleep(0.2)  # Debounce
                try:
                    # List all text files in current directory
                    txt_files = [f for f in os.listdir() if f.endswith('.txt')]
                    if not txt_files:
                        print("No recording files found!")
                        continue
                        
                    print("\nAvailable recording files:")
                    for i, file in enumerate(txt_files):
                        print(f"{i}: {file}")
                    
                    print("\nPress the number key (0-9) to select the file to load...")
                    # Wait for number key press
                    file_selected = False
                    while not file_selected:
                        for i in range(min(10, len(txt_files))):
                            if keyboard.is_pressed(str(i)):
                                try:
                                    loaded_data = load_recording_txt(txt_files[i])
                                    if loaded_data:
                                        recording_data = loaded_data
                                        print(f"\nLoaded recording from {txt_files[i]}")
                                    file_selected = True
                                    time.sleep(0.2)  # Debounce
                                    break
                                except Exception as e:
                                    print(f"Error loading file: {e}")
                                    break
                        if keyboard.is_pressed('esc'):
                            print("File loading cancelled")
                            file_selected = True
                        time.sleep(0.1)
                            
                except Exception as e:
                    print(f"Error listing recording files: {e}")
                continue

            if waiting_for_class_id:
                # Check for number keys 0-9
                for i in range(10):
                    if keyboard.is_pressed(str(i)):
                        time.sleep(0.2)  # Debounce
                        target_class_id = i
                        print(f"Recording tracking sequence for class ID {target_class_id}...")
                        current_time = time.time()
                        if last_command_time is not None:
                            duration = current_time - last_command_time
                        else:
                            duration = 0
                        
                        # Add tracking sequence command to recording with class ID
                        recording_data.append({
                            'duration': duration,
                            'command': 'TRACK_AND_GRAB',
                            'class_id': target_class_id,
                            'grabbing_sequence': [
                                ("Initial approach", {
                                    1: 990,   # Joint 1
                                    2: 850,   # Joint 2
                                    3: 500,   # Joint 3
                                    5: 0      # Gripper open
                                }),
                                ("Lower arm", {
                                    1: 890,
                                    2: 850,
                                    3: 450,
                                    5: 90     # Close gripper
                                }),
                                ("Close gripper", {
                                    1: 600,
                                    2: 850,
                                    3: 450,
                                    5: 90     # Close gripper
                                }),
                                ("Lift object", {
                                    1: 400,
                                    2: 500,
                                    3: 300
                                }),
                                ("Lift object", {
                                    1: 400,
                                    2: 500,
                                    3: 300,
                                    4: 180,
                                }),
                                ("Lift object", {
                                    1: 600,
                                    2: 500,
                                    3: 300,
                                }),
                                ("Close gripper", {
                                    5: 0     # Close gripper
                                }),
                                ("Lift object", {
                                    1: 400,
                                    2: 500,
                                    3: 300,
                                }),
                                ("Close gripper", {
                                    4: 0
                                })
                            ]
                        })
                        last_command_time = time.time()
                        print(f"Tracking sequence recorded for class ID {target_class_id}")
                        waiting_for_class_id = False
                        break
                continue

            if keyboard.is_pressed('x') and recording:
                time.sleep(0.2)  # Debounce
                print("Press a number (0-9) to select class ID...")
                waiting_for_class_id = True
                continue

            # Regular movement controls
            if keyboard.is_pressed('w'):
                robot_command = motor(robot_socket, MOTOR_SPEED, MOTOR_SPEED, -MOTOR_SPEED, -MOTOR_SPEED)
            elif keyboard.is_pressed('s'):
                robot_command = motor(robot_socket, -MOTOR_SPEED, -MOTOR_SPEED, MOTOR_SPEED, MOTOR_SPEED)
            elif keyboard.is_pressed('a'):
                robot_command = motor(robot_socket, MOTOR_SPEED, -MOTOR_SPEED, -MOTOR_SPEED, MOTOR_SPEED)
            elif keyboard.is_pressed('d'):
                robot_command = motor(robot_socket, -MOTOR_SPEED, MOTOR_SPEED, MOTOR_SPEED, -MOTOR_SPEED)
            elif keyboard.is_pressed('q'):
                robot_command = motor(robot_socket, TURN_SPEED, TURN_SPEED, TURN_SPEED, TURN_SPEED)
            elif keyboard.is_pressed('e'):
                robot_command = motor(robot_socket, -TURN_SPEED, -TURN_SPEED, -TURN_SPEED, -TURN_SPEED)
            elif keyboard.is_pressed(' '):
                robot_command = motor(robot_socket, 0, 0, 0, 0)

            # Arm controls
            if keyboard.is_pressed('t'):
                arm_command = arm_controller.move_joint(1, arm_controller.joint1 + 10)
            elif keyboard.is_pressed('g'):
                arm_command = arm_controller.move_joint(1, arm_controller.joint1 - 10)
            elif keyboard.is_pressed('y'):
                arm_command = arm_controller.move_joint(2, arm_controller.joint2 + 10)
            elif keyboard.is_pressed('h'):
                arm_command = arm_controller.move_joint(2, arm_controller.joint2 - 10)
            elif keyboard.is_pressed('u'):
                arm_command = arm_controller.move_joint(3, arm_controller.joint3 + 10)
            elif keyboard.is_pressed('j'):
                arm_command = arm_controller.move_joint(3, arm_controller.joint3 - 10)
            elif keyboard.is_pressed('i'):
                arm_command = arm_controller.move_base(arm_controller.base_angle + 10)
            elif keyboard.is_pressed('k'):
                arm_command = arm_controller.move_base(arm_controller.base_angle - 10)
            elif keyboard.is_pressed('o'):
                arm_command = arm_controller.move_gripper_rotate(arm_controller.gripper_rotate + 10)
            elif keyboard.is_pressed('l'):
                arm_command = arm_controller.move_gripper_rotate(arm_controller.gripper_rotate - 10)
            elif keyboard.is_pressed('n'):
                arm_command = arm_controller.move_gripper_claw(arm_controller.gripper_claw + 10)
            elif keyboard.is_pressed('m'):
                arm_command = arm_controller.move_gripper_claw(arm_controller.gripper_claw - 10)

            # Record commands if recording is active
            if recording and (robot_command):
                current_time = time.time()
                if last_command_time is not None:
                    duration = current_time - last_command_time
                else:
                    duration = 0
                
                recording_data.append({
                    'duration': duration,
                    'command': robot_command if robot_command else arm_command
                })
                last_command_time = current_time

            if keyboard.is_pressed('p'):  # Playback
                time.sleep(0.2)  # Debounce
                if not recording and recording_data:
                    print("Playing back recorded commands...")
                    
                    for entry in recording_data:
                        # Wait for the recorded duration before executing this command
                        if entry['duration'] > 0:
                            print(f"Waiting for {entry['duration']:.1f} seconds...")
                            time.sleep(entry['duration'])
                        
                        # Execute the command
                        if entry['command'] == 'TRACK_AND_GRAB':
                            print(f"Executing tracking sequence for class ID {entry.get('class_id', 3)}...")
                            try:
                                # Initialize arm position
                                arm_controller.move_joint(1, 700)
                                time.sleep(0.2)
                                arm_controller.move_joint(2, 850)
                                time.sleep(0.2)
                                arm_controller.move_joint(3, 100)
                                time.sleep(0.2)
                                arm_controller.move_gripper_claw(0)
                                time.sleep(0.2)
                                arm_controller.move_gripper_rotate(0)
                                time.sleep(0.2)

                                # Track object until centered
                                tracking_start_time = time.time()
                                while True:
                                    is_centered = track_object(robot_socket, camera_controller, 
                                                            target_class_id=entry.get('class_id', 3))
                                    if is_centered:
                                        print("Object centered!")
                                        break
                                    if time.time() - tracking_start_time > 30:  # 30 second timeout
                                        print("Tracking timeout - moving to next command")
                                        break
                                    time.sleep(0.05)

                                # Stop the robot
                                motor(robot_socket, 0, 0, 0, 0)
                                time.sleep(0.5)

                                # Execute grabbing sequence
                                for movement_name, joint_positions in entry['grabbing_sequence']:
                                    if not perform_arm_movement_with_delay(arm_controller, movement_name, joint_positions):
                                        print("Error in grabbing sequence - continuing with next command")
                                        break

                            except Exception as e:
                                print(f"Error during tracking sequence: {e}")
                                try:
                                    motor(robot_socket, 0, 0, 0, 0)
                                except:
                                    pass
                            print("Tracking sequence completed, continuing with next command...")
                            
                        elif entry['command']:
                            if entry['command'].startswith('M'):  # Robot movement command
                                print(f"Executing robot command: {entry['command']}")
                                robot_socket.sendall(entry['command'].encode())
                            elif entry['command'].startswith(('J', 'A', 'B', 'G')):  # Arm command
                                print(f"Executing arm command: {entry['command']}")
                                arm_controller.client_socket.sendall(entry['command'].encode())
                    
                    print("Playback completed")
                    # Stop both robot and arm
                    motor(robot_socket, 0, 0, 0, 0)
                continue

    except KeyboardInterrupt:
        # Stop both robot and arm
        motor(robot_socket, 0, 0, 0, 0)
        arm_controller.move_all_joints(JOINT1_INITIAL, JOINT2_INITIAL, JOINT3_INITIAL)

def main():
    camera_controller = None
    arm_controller = None
    robot_client = None
    robot_server = None
    robot_zeroconf = None
    
    try:
        # Initialize camera controller
        camera_controller = CameraController()
        
        # Initialize arm controller
        arm_controller = RobotArmController()
        
        # Connect to robot ESP
        print("Connecting to robot ESP...")
        robot_client, robot_server, robot_zeroconf = connect_to_esp()
        
        # Connect to arm ESP
        print("Connecting to arm ESP...")
        arm_client, arm_server, arm_zeroconf = arm_controller.connect_to_esp()
        
        # Start control loop
        control_robot_and_arm(robot_client, arm_controller, camera_controller)
        
    except KeyboardInterrupt:
        print("\nShutting down gracefully...")
    except Exception as e:
        print(f"\nError occurred: {e}")
    finally:
        print("Cleaning up resources...")
        
        # Cleanup camera
        if camera_controller:
            print("Stopping camera...")
            camera_controller.running = False
            camera_controller.cleanup()
            
        # Stop any ongoing robot movement
        if robot_client:
            try:
                print("Stopping robot...")
                motor(robot_client, 0, 0, 0, 0)
            except:
                pass
            
        # Reset arm to safe position if possible
        if arm_controller and arm_controller.client_socket:
            try:
                print("Resetting arm position...")
                arm_controller.move_all_joints(JOINT1_INITIAL, JOINT2_INITIAL, JOINT3_INITIAL)
                time.sleep(0.5)
            except:
                pass
            
        # Cleanup robot connections
        if robot_client:
            print("Closing robot connection...")
            robot_client.close()
        if robot_server:
            robot_server.close()
        if robot_zeroconf:
            robot_zeroconf.unregister_all_services()
            robot_zeroconf.close()
            
        # Cleanup arm connections
        if arm_controller:
            print("Closing arm connection...")
            if arm_controller.client_socket:
                arm_controller.client_socket.close()
            if arm_controller.zeroconf:
                arm_controller.zeroconf.unregister_all_services()
                arm_controller.zeroconf.close()
                
        print("Cleanup completed")

if __name__ == '__main__':
    main() 