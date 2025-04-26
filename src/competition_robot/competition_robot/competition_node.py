#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from nav2_msgs.action import NavigateToPose
from geometry_msgs.msg import PoseStamped, Twist
from rclpy.action import ActionClient
from sensor_msgs.msg import Image
from cv_bridge import CvBridge
import cv2
import numpy as np
from tf2_ros import TransformListener, Buffer
from std_msgs.msg import String
from threading import Timer
import time
from enum import Enum, auto
from ultralytics import YOLO
import os
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from control_msgs.action import FollowJointTrajectory
from rclpy.duration import Duration

class RobotState(Enum):
    IDLE = auto()
    NAVIGATING = auto()
    DETECTING = auto()
    PICKING = auto()
    PLACING = auto()
    ERROR = auto()

class ScenarioType(Enum):
    BMT = auto()
    BTT1 = auto()
    BTT2 = auto()
    ATT1 = auto()
    ATT2 = auto()
    FINAL = auto()

class CompetitionNode(Node):
    def __init__(self):
        super().__init__('competition_node')
        
        # Load YOLO model
        self.model = YOLO('best.pt')
        
        # Declare parameters
        self.declare_parameters(
            namespace='',
            parameters=[
                ('table_height', 0.75),
                ('object_heights.cube', 0.05),
                ('object_heights.cylinder', 0.1),
                ('object_heights.sphere', 0.08),
                ('detection_confidence', 0.5),
                ('navigation_timeout', 60.0),
                ('holonomic_speed', 0.1),
                ('holonomic_duration', 3.0),
                ('scenario', 'BMT'),
                # Arm parameters
                ('arm.joint_names', ['joint1', 'joint2', 'joint3', 'joint4', 'joint5', 'joint6']),
                ('arm.home_position', [0.0, 0.0, 0.0, 0.0, 0.0, 0.0]),
                ('arm.gripper.open_position', 0.1),
                ('arm.gripper.close_position', 0.0),
                ('arm.control.position_tolerance', 0.01),
                ('arm.control.velocity_tolerance', 0.1),
                ('arm.control.acceleration_limit', 1.0),
                ('arm.control.velocity_limit', 1.0)
            ]
        )
        
        # Initialize state
        self.state = RobotState.IDLE
        self.current_waypoint = 0
        self.object_detected = None
        self.object_angle = 0.0
        self.object_confidence = 0.0
        self.picked_objects = []
        
        # Setup clients and publishers
        self.setup_communication()
        
        # Load scenario configuration
        self.load_scenario()
        
        # Start the competition
        self.start_competition()

    def setup_communication(self):
        """Setup all ROS2 communication channels"""
        self.nav_to_pose_client = ActionClient(self, NavigateToPose, 'navigate_to_pose')
        self.cmd_vel_pub = self.create_publisher(Twist, '/cmd_vel', 10)
        self.bridge = CvBridge()
        self.image_sub = self.create_subscription(
            Image, '/camera/image_raw', self.image_callback, 10)
        
        # Arm action client
        self.arm_client = ActionClient(
            self,
            FollowJointTrajectory,
            '/arm_controller/follow_joint_trajectory'
        )
        
        # Create a timer for navigation timeout
        self.nav_timeout_timer = None

    def load_scenario(self):
        """Load scenario configuration from parameters"""
        scenario_name = self.get_parameter('scenario').value
        try:
            scenario_type = ScenarioType[scenario_name]
            self.get_logger().info(f"Loading scenario: {scenario_name}")
            
            # Get scenario waypoints from parameters
            scenario_config = self.get_parameter('scenarios.' + scenario_name).value
            self.waypoints = []
            
            for wp in scenario_config['waypoints']:
                pose = self.create_pose(wp['x'], wp['y'], wp['yaw'])
                self.waypoints.append((wp['name'], pose))
                
            self.get_logger().info(f"Loaded {len(self.waypoints)} waypoints for scenario {scenario_name}")
            
        except Exception as e:
            self.get_logger().error(f"Error loading scenario: {str(e)}")
            self.state = RobotState.ERROR
            self.recover_from_error()

    def start_competition(self):
        """Start the competition sequence"""
        self.get_logger().info("Starting competition sequence")
        self.state = RobotState.NAVIGATING
        self.start_navigation()

    def create_pose(self, x, y, yaw):
        """Create a PoseStamped message"""
        pose = PoseStamped()
        pose.header.frame_id = 'map'
        pose.header.stamp = self.get_clock().now().to_msg()
        pose.pose.position.x = x
        pose.pose.position.y = y
        pose.pose.position.z = 0.0
        pose.pose.orientation.z = np.sin(yaw / 2)
        pose.pose.orientation.w = np.cos(yaw / 2)
        return pose

    def start_navigation(self):
        """Start navigation to current waypoint"""
        if self.current_waypoint >= len(self.waypoints):
            self.get_logger().info("All waypoints completed!")
            return

        waypoint_name, waypoint_pose = self.waypoints[self.current_waypoint]
        self.get_logger().info(f"Navigating to waypoint {waypoint_name}")
        
        goal_msg = NavigateToPose.Goal()
        goal_msg.pose = waypoint_pose
        
        # Set navigation timeout
        nav_timeout = self.get_parameter('navigation_timeout').value
        self.nav_timeout_timer = Timer(nav_timeout, self.handle_navigation_timeout)
        self.nav_timeout_timer.start()
        
        self.nav_to_pose_client.wait_for_server()
        self.send_goal_future = self.nav_to_pose_client.send_goal_async(
            goal_msg,
            feedback_callback=self.nav_feedback_callback)
        self.send_goal_future.add_done_callback(self.goal_response_callback)

    def handle_navigation_timeout(self):
        """Handle navigation timeout"""
        if self.state == RobotState.NAVIGATING:
            self.get_logger().error("Navigation timeout reached")
            self.state = RobotState.ERROR
            self.recover_from_error()

    def goal_response_callback(self, future):
        """Handle navigation goal response"""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Goal rejected')
            self.state = RobotState.ERROR
            self.recover_from_error()
            return

        self.get_logger().info('Goal accepted')
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.get_result_callback)

    def get_result_callback(self, future):
        """Handle navigation result"""
        if self.nav_timeout_timer:
            self.nav_timeout_timer.cancel()
            
        result = future.result().result
        self.get_logger().info(f'Navigation result: {result}')
        
        if self.state == RobotState.NAVIGATING:
            waypoint_name, _ = self.waypoints[self.current_waypoint]
            if 'pickup' in waypoint_name:
                self.state = RobotState.DETECTING
                self.start_holonomic_movement()
            elif 'assembly' in waypoint_name:
                self.state = RobotState.PLACING
                self.release_object()
            elif waypoint_name == 'final':
                self.get_logger().info("Final waypoint reached. Competition completed!")
                self.state = RobotState.IDLE
            else:
                self.next_waypoint()

    def nav_feedback_callback(self, feedback_msg):
        """Handle navigation feedback"""
        feedback = feedback_msg.feedback
        self.get_logger().info(f'Distance remaining: {feedback.distance_remaining:.2f} meters')

    def start_holonomic_movement(self):
        """Start holonomic movement for object detection"""
        self.get_logger().info("Starting holonomic movement for detection")
        
        speed = self.get_parameter('holonomic_speed').value
        duration = self.get_parameter('holonomic_duration').value
        
        twist = Twist()
        twist.linear.x = speed
        self.cmd_vel_pub.publish(twist)
        
        Timer(duration, self.stop_and_detect).start()

    def stop_and_detect(self):
        """Stop movement and process detection"""
        twist = Twist()
        self.cmd_vel_pub.publish(twist)
        
        self.get_logger().info("Processing object detection")
        if self.object_detected and self.object_confidence >= self.get_parameter('detection_confidence').value:
            self.state = RobotState.PICKING
            self.process_object()
        else:
            self.get_logger().warning("No object detected with sufficient confidence")
            self.next_waypoint()

    def image_callback(self, msg):
        """Process camera image for object detection"""
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, "bgr8")
            
            # Run YOLO detection
            results = self.model(cv_image, conf=self.get_parameter('detection_confidence').value)
            
            if len(results) > 0 and len(results[0].boxes) > 0:
                # Get the highest confidence detection
                box = results[0].boxes[0]
                self.object_detected = self.model.names[int(box.cls[0])]
                self.object_confidence = float(box.conf[0])
                
                # Calculate object angle
                x1, y1, x2, y2 = map(int, box.xyxy[0])
                rect = cv2.minAreaRect(np.array([[x1, y1], [x2, y1], [x2, y2], [x1, y2]]))
                self.object_angle = rect[2]
                
                self.get_logger().info(
                    f"Detected: {self.object_detected}, "
                    f"Confidence: {self.object_confidence:.2f}, "
                    f"Angle: {self.object_angle:.2f}"
                )
            
        except Exception as e:
            self.get_logger().error(f"Error in image processing: {str(e)}")

    def move_arm_to_pose(self, joint_positions, duration=5.0):
        """Move arm to specified joint positions"""
        if not self.arm_client.wait_for_server(timeout_sec=1.0):
            self.get_logger().error("Arm action server not available")
            return False

        trajectory = JointTrajectory()
        trajectory.joint_names = self.get_parameter('arm.joint_names').value
        
        point = JointTrajectoryPoint()
        point.positions = joint_positions
        point.time_from_start = Duration(seconds=duration).to_msg()
        
        trajectory.points = [point]
        
        goal_msg = FollowJointTrajectory.Goal()
        goal_msg.trajectory = trajectory
        
        self.get_logger().info(f"Moving arm to position: {joint_positions}")
        self.send_goal_future = self.arm_client.send_goal_async(goal_msg)
        self.send_goal_future.add_done_callback(self.arm_goal_response_callback)
        return True

    def arm_goal_response_callback(self, future):
        """Handle arm goal response"""
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error('Arm goal rejected')
            return

        self.get_logger().info('Arm goal accepted')
        self._get_result_future = goal_handle.get_result_async()
        self._get_result_future.add_done_callback(self.arm_result_callback)

    def arm_result_callback(self, future):
        """Handle arm result"""
        result = future.result().result
        if result.error_code != 0:
            self.get_logger().error(f'Arm movement failed with error code: {result.error_code}')
        else:
            self.get_logger().info('Arm movement completed successfully')

    def move_arm_to_home(self):
        """Move arm to home position"""
        home_position = self.get_parameter('arm.home_position').value
        return self.move_arm_to_pose(home_position)

    def move_arm_to_pickup(self):
        """Move arm to pickup position"""
        pickup_position = [0.0, -1.57, 1.57, 0.0, 0.0, 0.0]  # Example pickup pose
        return self.move_arm_to_pose(pickup_position)

    def move_arm_to_place(self):
        """Move arm to place position"""
        place_position = [0.0, -1.57, 1.57, 0.0, 0.0, 0.0]  # Example place pose
        return self.move_arm_to_pose(place_position)

    def control_gripper(self, position):
        """Control gripper position"""
        # Implementation depends on your gripper control method
        # This is a placeholder for the actual gripper control
        self.get_logger().info(f"Setting gripper to position: {position}")

    def process_object(self):
        """Process detected object"""
        if not self.object_detected:
            self.get_logger().warning("No object detected")
            self.next_waypoint()
            return

        self.get_logger().info(f"Processing object: {self.object_detected}")
        
        # Move arm to pickup position
        if self.move_arm_to_pickup():
            # Open gripper
            self.control_gripper(self.get_parameter('arm.gripper.open_position').value)
            
            # Wait for arm to reach position
            time.sleep(2.0)
            
            # Close gripper
            self.control_gripper(self.get_parameter('arm.gripper.close_position').value)
            
            # Move arm to home position
            self.move_arm_to_home()
            
            self.picked_objects.append(self.object_detected)
            self.next_waypoint()
        else:
            self.get_logger().error("Failed to move arm to pickup position")
            self.state = RobotState.ERROR
            self.recover_from_error()

    def next_waypoint(self):
        """Move to next waypoint"""
        self.current_waypoint += 1
        
        if self.current_waypoint < len(self.waypoints):
            self.state = RobotState.NAVIGATING
            self.start_navigation()
        else:
            self.get_logger().info("All waypoints completed!")
            self.state = RobotState.IDLE

    def release_object(self):
        """Release the held object"""
        self.get_logger().info("Releasing object")
        
        # Move arm to place position
        if self.move_arm_to_place():
            # Open gripper
            self.control_gripper(self.get_parameter('arm.gripper.open_position').value)
            
            # Wait for object to be released
            time.sleep(1.0)
            
            # Move arm to home position
            self.move_arm_to_home()
            
            self.next_waypoint()
        else:
            self.get_logger().error("Failed to move arm to place position")
            self.state = RobotState.ERROR
            self.recover_from_error()

    def recover_from_error(self):
        """Attempt to recover from error state"""
        self.get_logger().info("Attempting error recovery...")
        
        # Stop any movement
        twist = Twist()
        self.cmd_vel_pub.publish(twist)
        
        # Cancel any active timers
        if self.nav_timeout_timer:
            self.nav_timeout_timer.cancel()
        
        # Reset state and retry current waypoint
        self.state = RobotState.NAVIGATING
        self.start_navigation()

def main(args=None):
    rclpy.init(args=args)
    node = CompetitionNode()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 