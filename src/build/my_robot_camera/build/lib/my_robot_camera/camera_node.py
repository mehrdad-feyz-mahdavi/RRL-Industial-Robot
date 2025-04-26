#!/usr/bin/env python3
### ls /dev/video*
import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo
from cv_bridge import CvBridge
import cv2
import os
import threading
import numpy as np
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy, QoSDurabilityPolicy, QoSLivelinessPolicy, Duration
from ultralytics import YOLO
from my_robot_camera_msgs.msg import Detection, DetectionArray

class CameraNode(Node):
    def __init__(self):
        super().__init__('camera_node')
        
        # Parameters
        self.declare_parameter('frame_id', 'camera_link')
        self.declare_parameter('width', 1280)  # Updated for better detection
        self.declare_parameter('height', 720)  # Updated for better detection
        self.declare_parameter('exposure', -1)
        self.declare_parameter('buffer_size', 1)
        self.declare_parameter('queue_size', 30)  # Increased queue size for better buffering
        
        # YOLO parameters
        self.declare_parameter('model_path', 'best.pt')
        self.declare_parameter('confidence_threshold', 0.7)
        
        # Get parameters
        self.camera_id = 2
        self.fps = 90
        self.enable_detection = True
        self.frame_id = self.get_parameter('frame_id').value
        self.width = self.get_parameter('width').value
        self.height = self.get_parameter('height').value
        self.exposure = self.get_parameter('exposure').value
        self.buffer_size = self.get_parameter('buffer_size').value
        self.queue_size = self.get_parameter('queue_size').value
        
        # Get YOLO parameters
        self.confidence_threshold = self.get_parameter('confidence_threshold').value
        model_path = self.get_parameter('model_path').value
        
        # Initialize YOLO model
        try:
            self.model = YOLO(model_path)
            self.get_logger().info(f'Successfully loaded YOLO model from {model_path}')
        except Exception as e:
            self.get_logger().error(f'Failed to load YOLO model: {str(e)}')
            self.enable_detection = False
        
        # Set real-time priority if running as root
        if os.geteuid() == 0:
            try:
                os.sched_setscheduler(0, os.SCHED_FIFO, os.sched_param(99))
                self.get_logger().info('Set real-time scheduler priority')
            except Exception as e:
                self.get_logger().warn(f'Could not set real-time priority: {str(e)}')
        
        # QoS profile for real-time streaming
        qos_profile = QoSProfile(
            reliability=QoSReliabilityPolicy.RELIABLE,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=self.queue_size,
            durability=QoSDurabilityPolicy.VOLATILE,
            liveliness=QoSLivelinessPolicy.AUTOMATIC,
            deadline=Duration(seconds=1/self.fps)
        )
        
        self.get_logger().info(f'Attempting to open camera {self.camera_id}')
        
        # Try to open the camera
        self.cap = None
        self.init_camera()
        
        if not self.cap or not self.cap.isOpened():
            self.get_logger().error('Failed to open camera. Available cameras:')
            self.list_available_cameras()
            return
            
        # Publishers with QoS profile
        self.image_pub = self.create_publisher(Image, 'image_raw', qos_profile)
        self.detection_pub = self.create_publisher(Image, 'image_detections', qos_profile)
        self.info_pub = self.create_publisher(CameraInfo, 'camera_info', qos_profile)
        self.detections_pub = self.create_publisher(DetectionArray, 'detections', qos_profile)
        
        self.bridge = CvBridge()
        self.frame_lock = threading.Lock()
        self.latest_frame = None
        self.running = True
        
        # Create output directory for detection results
        self.output_dir = os.path.join(os.getcwd(), 'detection_results')
        os.makedirs(self.output_dir, exist_ok=True)
        self.frame_counter = 0
        
        # Start capture thread
        self.capture_thread = threading.Thread(target=self._capture_loop)
        self.capture_thread.daemon = True
        self.capture_thread.start()
        
        # Publishing timer at desired FPS
        period = 0.2
        self.timer = self.create_timer(period, self.timer_callback)
        
        self.get_logger().info('Camera node initialized successfully')
    
    def process_frame(self, frame):
        """Process the frame with YOLO object detection"""
        try:
            # Run YOLO inference
            results = self.model(frame, conf=self.confidence_threshold)
            
            # Create a copy for drawing
            processed = frame.copy()
            
            # Create DetectionArray message
            detection_array = DetectionArray()
            detection_array.header.stamp = self.get_clock().now().to_msg()
            detection_array.header.frame_id = self.frame_id
            
            # Save detection results to file and create detection messages
            self.frame_counter += 1
            frame_text_file = os.path.join(self.output_dir, f"frame_{self.frame_counter}.txt")
            
            with open(frame_text_file, 'w') as file:
                for result in results:
                    for box in result.boxes:
                        # Get detection details
                        x1, y1, x2, y2 = map(int, box.xyxy[0])
                        confidence = box.conf[0].item()
                        class_id = int(box.cls[0])
                        
                        # Create Detection message
                        detection = Detection()
                        detection.class_id = class_id
                        detection.x1 = x1
                        detection.y1 = y1
                        detection.x2 = x2
                        detection.y2 = y2
                        detection.confidence = confidence
                        detection_array.detections.append(detection)
                        
                        # Write to file
                        file.write(f"{class_id} {x1} {y1} {x2} {y2} {confidence:.2f}\n")
                        self.get_logger().info(f"class_id: {class_id}")
                        # Draw on image
                        cv2.rectangle(processed, (x1, y1), (x2, y2), (0, 255, 0), 2)
                        cv2.putText(
                            processed,
                            f"{self.model.names[class_id]}: {confidence:.2f}",
                            (x1, y1 - 10),
                            cv2.FONT_HERSHEY_SIMPLEX,
                            0.5,
                            (0, 255, 0),
                            2
                        )
            
            # Publish detections
            # self.get_logger().info(f'publishing on detections topic')
            self.detections_pub.publish(detection_array)
            return processed
            
        except Exception as e:
            self.get_logger().error(f'Error in YOLO processing: {str(e)}')
            return frame
    
    def init_camera(self):
        """Initialize the camera with proper settings"""
        try:
            self.cap = cv2.VideoCapture(self.camera_id)
            if not self.cap.isOpened():
                return False
                
            # Configure camera settings
            self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, self.width)
            self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, self.height)
            self.cap.set(cv2.CAP_PROP_FPS, self.fps)
            self.cap.set(cv2.CAP_PROP_BUFFERSIZE, self.buffer_size)
            
            if self.exposure != -1:
                self.cap.set(cv2.CAP_PROP_AUTO_EXPOSURE, 0)
                self.cap.set(cv2.CAP_PROP_EXPOSURE, self.exposure)
            
            # Verify settings
            actual_width = self.cap.get(cv2.CAP_PROP_FRAME_WIDTH)
            actual_height = self.cap.get(cv2.CAP_PROP_FRAME_HEIGHT)
            actual_fps = self.cap.get(cv2.CAP_PROP_FPS)
            
            self.get_logger().info(f'Camera initialized with: {actual_width}x{actual_height} @ {actual_fps}fps')
            return True
            
        except Exception as e:
            self.get_logger().error(f'Error initializing camera: {str(e)}')
            return False
    
    def list_available_cameras(self):
        """List all available camera devices"""
        for i in range(10):
            cap = cv2.VideoCapture(i)
            if cap.isOpened():
                self.get_logger().info(f'Camera {i} is available')
                cap.release()
            else:
                self.get_logger().info(f'Camera {i} is not available')
    
    def _capture_loop(self):
        """Continuous frame capture loop running in separate thread"""
        while self.running and rclpy.ok():
            if not self.cap or not self.cap.isOpened():
                self.get_logger().warn('Camera disconnected, attempting to reconnect...')
                if self.init_camera():
                    self.get_logger().info('Successfully reconnected to camera')
                else:
                    self.get_logger().error('Failed to reconnect to camera')
                    rclpy.sleep(1.0)
                continue
                
            ret, frame = self.cap.read()
            if ret:
                with self.frame_lock:
                    self.latest_frame = frame
            else:
                self.get_logger().warn('Failed to capture frame')
                self.cap.release()

    def timer_callback(self):
        """Timer callback for publishing frames"""
        with self.frame_lock:
            frame = self.latest_frame
            if frame is None:
                return
        
        try:
            # Get current timestamp
            now = self.get_clock().now()
            
            # Publish raw image
            raw_msg = self.bridge.cv2_to_imgmsg(frame, 'bgr8')
            raw_msg.header.stamp = now.to_msg()
            raw_msg.header.frame_id = self.frame_id
            self.image_pub.publish(raw_msg)
            
            if self.enable_detection:
                # Process frame with YOLO and publish results
                processed = self.process_frame(frame)
                processed_msg = self.bridge.cv2_to_imgmsg(processed, 'bgr8')
                processed_msg.header = raw_msg.header
                self.detection_pub.publish(processed_msg)
            
            # Camera info
            info = CameraInfo()
            info.header = raw_msg.header
            info.height = frame.shape[0]
            info.width = frame.shape[1]
            self.info_pub.publish(info)
            
        except Exception as e:
            self.get_logger().error(f'Error publishing frame: {str(e)}')
    
    def destroy_node(self):
        """Clean up resources"""
        self.running = False
        if self.capture_thread.is_alive():
            self.capture_thread.join()
        if self.cap and self.cap.isOpened():
            self.cap.release()
        super().destroy_node()

def main(args=None):
    rclpy.init(args=args)
    node = CameraNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()