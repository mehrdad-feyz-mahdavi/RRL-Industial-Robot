#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from builtin_interfaces.msg import Duration
import time

class ArmTest(Node):
    def __init__(self):
        super().__init__('arm_test')
        
        # Create publisher for arm trajectory
        self.arm_publisher = self.create_publisher(
            JointTrajectory,
            '/arm_controller/joint_trajectory',
            10
        )
        
        # Wait for publisher to be ready
        time.sleep(2)
        
        # Test arm motion
        self.test_arm_motion()
    
    def test_arm_motion(self):
        # Create arm trajectory message
        arm_trajectory = JointTrajectory()
        arm_trajectory.joint_names = ['arm_base_joint', 'a2', 'a3', 'a4']
        
        # Create trajectory point
        point = JointTrajectoryPoint()
        point.positions = [0.5, 0.3, -0.2, 0.1]  # New test positions
        point.velocities = [0.0, 0.0, 0.0, 0.0]
        point.time_from_start = Duration(sec=5)  # 5 seconds to reach the goal
        
        arm_trajectory.points.append(point)
        
        # Publish trajectory
        self.arm_publisher.publish(arm_trajectory)
        self.get_logger().info('Published arm trajectory')

def main():
    rclpy.init()
    node = ArmTest()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 