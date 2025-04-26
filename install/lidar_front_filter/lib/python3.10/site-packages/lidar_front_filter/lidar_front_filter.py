#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
import math

class LidarFrontFilter(Node):
    def __init__(self):
        super().__init__('lidar_front_filter')
        
        # Declare parameters
        self.declare_parameter('min_crop_angle', 30.0)  # Minimum angle in degrees (left of center)
        self.declare_parameter('max_crop_angle', 150.0)   # Maximum angle in degrees (right of center)
        self.declare_parameter('input_topic', '/scan_ktz')
        self.declare_parameter('output_topic', '/scan')
        
        # Get parameters
        self.min_crop_angle = math.radians(self.get_parameter('min_crop_angle').value)
        self.max_crop_angle = math.radians(self.get_parameter('max_crop_angle').value)
        input_topic = self.get_parameter('input_topic').value
        output_topic = self.get_parameter('output_topic').value
        
        # Create subscriber and publisher
        self.subscription = self.create_subscription(
            LaserScan,
            input_topic,
            self.scan_callback,
            10)
        
        self.publisher = self.create_publisher(
            LaserScan,
            output_topic,
            10)
        
        self.get_logger().info(f'LiDAR filter initialized. Crop angles: {math.degrees(self.min_crop_angle):.1f} to {math.degrees(self.max_crop_angle):.1f} degrees')

    def scan_callback(self, msg):
        # Calculate start and end indices based on angles
        angle_min = msg.angle_min
        angle_increment = msg.angle_increment
        
        # Calculate relative indices from angle_min
        start_index = int((self.min_crop_angle - angle_min) / angle_increment)
        end_index = int((self.max_crop_angle - angle_min) / angle_increment) + 1
        
        # Ensure indices are within valid range
        start_index = max(0, start_index)
        end_index = min(len(msg.ranges), end_index)
        
        # Create filtered message
        filtered_msg = LaserScan()
        filtered_msg.header = msg.header
        filtered_msg.angle_min = angle_min + (start_index * angle_increment)
        filtered_msg.angle_max = angle_min + ((end_index - 1) * angle_increment)
        filtered_msg.angle_increment = msg.angle_increment
        filtered_msg.time_increment = msg.time_increment
        filtered_msg.scan_time = msg.scan_time
        filtered_msg.range_min = msg.range_min
        filtered_msg.range_max = msg.range_max
        
        # Filter the data
        filtered_msg.ranges = msg.ranges[start_index:end_index]
        filtered_msg.intensities = msg.intensities[start_index:end_index] if msg.intensities else []
        
        # Publish the filtered message
        self.publisher.publish(filtered_msg)

def main(args=None):
    rclpy.init(args=args)
    lidar_filter = LidarFrontFilter()
    rclpy.spin(lidar_filter)
    lidar_filter.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()