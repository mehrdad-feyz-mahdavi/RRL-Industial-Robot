#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import Image, CameraInfo
from rclpy.qos import QoSProfile, QoSReliabilityPolicy, QoSHistoryPolicy, QoSDurabilityPolicy

class QoSBridgeNode(Node):
    def __init__(self):
        super().__init__('qos_bridge_node')
        
        # QoS profile for subscribing to camera (BEST_EFFORT)
        sub_qos = QoSProfile(
            reliability=QoSReliabilityPolicy.BEST_EFFORT,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=1
        )
        
        # QoS profile for publishing to RViz (RELIABLE)
        pub_qos = QoSProfile(
            reliability=QoSReliabilityPolicy.RELIABLE,
            history=QoSHistoryPolicy.KEEP_LAST,
            depth=1,
            durability=QoSDurabilityPolicy.VOLATILE
        )
        
        # Create subscribers with BEST_EFFORT QoS
        self.raw_sub = self.create_subscription(
            Image,
            'image_raw',
            self.raw_callback,
            sub_qos
        )
        
        self.detection_sub = self.create_subscription(
            Image,
            'image_detections',
            self.detection_callback,
            sub_qos
        )
        
        self.info_sub = self.create_subscription(
            CameraInfo,
            'camera_info',
            self.info_callback,
            sub_qos
        )
        
        # Create publishers with RELIABLE QoS
        self.raw_pub = self.create_publisher(
            Image,
            'image_raw_reliable',
            pub_qos
        )
        
        self.detection_pub = self.create_publisher(
            Image,
            'image_detections_reliable',
            pub_qos
        )
        
        self.info_pub = self.create_publisher(
            CameraInfo,
            'camera_info_reliable',
            pub_qos
        )
        
        self.get_logger().info('QoS Bridge Node initialized')
    
    def raw_callback(self, msg):
        self.raw_pub.publish(msg)
    
    def detection_callback(self, msg):
        self.detection_pub.publish(msg)
    
    def info_callback(self, msg):
        self.info_pub.publish(msg)

def main(args=None):
    rclpy.init(args=args)
    node = QoSBridgeNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 