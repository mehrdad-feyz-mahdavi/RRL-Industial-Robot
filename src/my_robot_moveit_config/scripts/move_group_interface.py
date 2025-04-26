#!/usr/bin/env python3

import sys
import rclpy
from rclpy.node import Node
from moveit.planning_interface import MoveGroupInterface
from geometry_msgs.msg import Pose
from moveit_msgs.msg import CollisionObject, RobotTrajectory
from shape_msgs.msg import SolidPrimitive
from std_msgs.msg import Header
from moveit_msgs.msg import PlanningScene, PlanningSceneWorld
from moveit_msgs.srv import GetPlanningScene
from trajectory_msgs.msg import JointTrajectory, JointTrajectoryPoint
import time

class MoveGroupInterfaceExample(Node):
    def __init__(self):
        super().__init__('move_group_interface_example')
        
        # Initialize MoveGroupInterface for the arm
        self.arm = MoveGroupInterface("arm", "robot_description")
        
        # Initialize MoveGroupInterface for the gripper
        self.gripper = MoveGroupInterface("gripper", "robot_description")
        
        # Set planning time
        self.arm.set_planning_time(10.0)
        
        # Set velocity scaling factor
        self.arm.set_max_velocity_scaling_factor(0.5)
        
        # Set acceleration scaling factor
        self.arm.set_max_acceleration_scaling_factor(0.5)
        
        # Set goal tolerance
        self.arm.set_goal_position_tolerance(0.01)
        self.arm.set_goal_orientation_tolerance(0.1)
        
        # Create a planning scene publisher
        self.planning_scene_publisher = self.create_publisher(
            PlanningScene, 'planning_scene', 10
        )
        
        # Create a service client for getting the planning scene
        self.get_planning_scene_client = self.create_client(
            GetPlanningScene, 'get_planning_scene'
        )
        
        # Set controller service call timeout (in seconds)
        self.arm.set_controller_service_call_timeout(5.0)
        
        # Set the default controller
        self.arm.set_default_controller("arm_controller")
        self.gripper.set_default_controller("gripper_controller")
        
        # Allow replanning
        self.arm.allow_replanning(True)
        
        self.get_logger().info("MoveGroupInterface initialized")

    def add_collision_object(self, name, pose, dimensions, shape_type=1):
        """Add a collision object to the planning scene"""
        collision_object = CollisionObject()
        collision_object.header.frame_id = "world"
        collision_object.id = name
        
        # Create a solid primitive
        primitive = SolidPrimitive()
        primitive.type = shape_type  # 1 for box
        primitive.dimensions = dimensions
        
        # Add the primitive to the collision object
        collision_object.primitives.append(primitive)
        collision_object.primitive_poses.append(pose)
        collision_object.operation = CollisionObject.ADD
        
        # Create a planning scene message
        planning_scene = PlanningScene()
        planning_scene.world.collision_objects.append(collision_object)
        planning_scene.is_diff = True
        
        # Publish the planning scene
        self.planning_scene_publisher.publish(planning_scene)
        self.get_logger().info(f"Added collision object: {name}")

    def move_to_named_target(self, target_name):
        """Move to a named target position"""
        self.get_logger().info(f"Moving to target: {target_name}")
        
        # Set the target
        success = self.arm.set_named_target(target_name)
        if not success:
            self.get_logger().error(f"Failed to set target: {target_name}")
            return False
            
        # Plan the trajectory
        plan = self.arm.plan()
        if not plan:
            self.get_logger().error(f"Failed to plan to target: {target_name}")
            return False
            
        # Execute the trajectory
        success = self.arm.execute(plan, wait=True)
        if not success:
            self.get_logger().error(f"Failed to reach target: {target_name}")
            return False
            
        self.get_logger().info(f"Successfully reached target: {target_name}")
        return True

    def move_to_pose(self, pose):
        """Move to a specific pose"""
        self.get_logger().info("Moving to pose")
        
        # Set the target pose
        success = self.arm.set_pose_target(pose)
        if not success:
            self.get_logger().error("Failed to set pose target")
            return False
            
        # Plan the trajectory
        plan = self.arm.plan()
        if not plan:
            self.get_logger().error("Failed to plan to pose")
            return False
            
        # Execute the trajectory
        success = self.arm.execute(plan, wait=True)
        if not success:
            self.get_logger().error("Failed to reach pose")
            return False
            
        self.get_logger().info("Successfully reached pose")
        return True

    def move_gripper(self, position):
        """Move the gripper to a specific position"""
        self.get_logger().info(f"Moving gripper to position: {position}")
        
        # Create a trajectory for the gripper
        trajectory = JointTrajectory()
        trajectory.joint_names = ["bg", "g1"]  # Replace with your gripper joint names
        
        point = JointTrajectoryPoint()
        point.positions = [position, position]  # Same position for both joints
        point.time_from_start = rclpy.duration.Duration(seconds=1.0).to_msg()
        trajectory.points.append(point)
        
        # Execute the trajectory
        success = self.gripper.execute(trajectory, wait=True)
        if not success:
            self.get_logger().error("Failed to move gripper")
            return False
            
        self.get_logger().info("Successfully moved gripper")
        return True

    def execute_cartesian_path(self, waypoints):
        """Execute a cartesian path through waypoints"""
        self.get_logger().info("Executing cartesian path")
        
        # Compute the cartesian path
        (plan, fraction) = self.arm.compute_cartesian_path(
            waypoints,  # waypoints to follow
            0.01,      # eef_step
            0.0,       # jump_threshold
            True       # avoid_collisions
        )
        
        if fraction < 1.0:
            self.get_logger().error(f"Could not compute full path. Fraction: {fraction}")
            return False
            
        # Execute the trajectory
        success = self.arm.execute(plan, wait=True)
        if not success:
            self.get_logger().error("Failed to execute path")
            return False
            
        self.get_logger().info("Successfully executed cartesian path")
        return True

def main():
    rclpy.init()
    
    # Create the node
    node = MoveGroupInterfaceExample()
    
    try:
        # Example usage
        # 1. Move to a named target
        node.move_to_named_target("ready")
        
        # 2. Move gripper to open position
        node.move_gripper(-1.57)  # Open position
        
        # 3. Create a pose for the end effector
        target_pose = Pose()
        target_pose.position.x = 0.5
        target_pose.position.y = 0.0
        target_pose.position.z = 0.5
        target_pose.orientation.w = 1.0
        
        # 4. Move to the target pose
        node.move_to_pose(target_pose)
        
        # 5. Close the gripper
        node.move_gripper(0.0)  # Close position
        
        # 6. Move back to ready position
        node.move_to_named_target("ready")
        
    except KeyboardInterrupt:
        pass
    finally:
        # Clean up
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main() 