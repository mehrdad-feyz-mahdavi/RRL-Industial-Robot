#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from moveit_msgs.msg import DisplayTrajectory
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
from builtin_interfaces.msg import Duration
import time

class MotionTest(Node):
    def __init__(self):
        super().__init__('motion_test')
        
        # Create publisher for arm trajectory
        self.arm_publisher = self.create_publisher(
            JointTrajectory,
            '/arm_controller/joint_trajectory',
            10
        )
        
        # Create publisher for gripper trajectory
        self.gripper_publisher = self.create_publisher(
            JointTrajectory,
            '/gripper_controller/joint_trajectory',
            10
        )
        
        # Wait for publishers to be ready
        time.sleep(2)
        
        # Test arm motion
        self.test_arm_motion()
        
        # Wait a bit
        time.sleep(3)
        
        # Test gripper motion
        self.test_gripper_motion()
    
    def test_arm_motion(self):
        # Create arm trajectory message
        arm_trajectory = JointTrajectory()
        arm_trajectory.joint_names = ['arm_base_joint', 'a2', 'a3', 'a4']
        
        # Create trajectory point
        point = JointTrajectoryPoint()
        point.positions = [0.0, 0.5, -0.3, 0.2]  # Example positions
        point.velocities = [0.0, 0.0, 0.0, 0.0]
        point.time_from_start = Duration(sec=5)  # 5 seconds to reach the goal
        
        arm_trajectory.points.append(point)
        
        # Publish trajectory
        self.arm_publisher.publish(arm_trajectory)
        self.get_logger().info('Published arm trajectory')
    
    def test_gripper_motion(self):
        # Create gripper trajectory message
        gripper_trajectory = JointTrajectory()
        gripper_trajectory.joint_names = ['bg', 'g1']
        
        # Create trajectory point
        point = JointTrajectoryPoint()
        point.positions = [-1.57, -0.288]  # Open position
        point.velocities = [0.0, 0.0]
        point.time_from_start = Duration(sec=2)  # 2 seconds to reach the goal
        
        gripper_trajectory.points.append(point)
        
        # Publish trajectory
        self.gripper_publisher.publish(gripper_trajectory)
        self.get_logger().info('Published gripper trajectory')

def main():
    rclpy.init()
    node = MotionTest()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main() 