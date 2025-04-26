#!/usr/bin/env python3
import rclpy
from rclpy.action import ActionServer
from rclpy.node import Node
from geometry_msgs.msg import Twist
from my_robot_navigation.action import MoveHolonomic
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.executors import MultiThreadedExecutor
import math
import time

class HolonomicActionServer(Node):
    def __init__(self):
        super().__init__('holonomic_action_server')
        
        # Create callback group
        self.callback_group = ReentrantCallbackGroup()
        
        self._action_server = ActionServer(
            self,
            MoveHolonomic,          
            'move_holonomic_to_second_object',
            self.execute_callback,
            callback_group=self.callback_group
        )
        self.publisher = self.create_publisher(Twist, '/cmd_vel', 10)
        self.get_logger().info('Holonomic Action Server has been started')

    async def execute_callback(self, goal_handle):
        self.get_logger().info('Executing goal...')
        
        feedback_msg = MoveHolonomic.Feedback()
        result = MoveHolonomic.Result()

        # Get goal parameters
        target_x = goal_handle.request.target_x
        target_y = goal_handle.request.target_y
        target_theta = goal_handle.request.target_theta
        
        # Create Twist message for movement
        cmd_vel = Twist()
        
        try:
            # Set initial velocities based on target position
            cmd_vel.linear.x = self._calculate_velocity(target_x, 0.5)
            cmd_vel.linear.y = self._calculate_velocity(target_y, 0.5)
            cmd_vel.angular.z = self._calculate_angular_velocity(target_theta, 0.5)
            
            # Movement control loop
            start_time = time.time()
            rate = self.create_rate(10)  # 10Hz control loop
            
            while rclpy.ok():
                # Check if there is a cancel request
                if goal_handle.is_cancel_requested:
                    goal_handle.canceled()
                    self.stop_robot()
                    self.get_logger().info('Goal canceled')
                    return MoveHolonomic.Result()

                # Publish velocity command
                self.publisher.publish(cmd_vel)
                
                # Update feedback
                feedback_msg.current_x = target_x  # In a real robot, this would come from odometry
                feedback_msg.current_y = target_y
                feedback_msg.current_theta = target_theta
                goal_handle.publish_feedback(feedback_msg)
                
                # Check if we've reached the goal (simplified)
                if self._is_goal_reached(target_x, target_y, target_theta):
                    break
                    
                # Timeout after 30 seconds
                if time.time() - start_time > 30.0:
                    self.stop_robot()
                    goal_handle.abort()
                    self.get_logger().warn('Goal timed out')
                    return MoveHolonomic.Result()
                
                rate.sleep()
            
            # Goal reached successfully
            self.stop_robot()
            goal_handle.succeed()
            result.success = True
            self.get_logger().info('Goal succeeded')
            return result
            
        except Exception as e:
            self.get_logger().error(f'Exception during execution: {str(e)}')
            self.stop_robot()
            goal_handle.abort()
            result.success = False
            return result

    def _calculate_velocity(self, target, max_speed):
        """Calculate linear velocity based on target distance"""
        # Simplified linear velocity calculation
        return max_speed if abs(target) > 0.1 else 0.0

    def _calculate_angular_velocity(self, target_theta, max_angular_speed):
        """Calculate angular velocity based on target angle"""
        # Simplified angular velocity calculation
        return max_angular_speed if abs(target_theta) > 0.1 else 0.0

    def _is_goal_reached(self, target_x, target_y, target_theta):
        """Check if the robot has reached the target position"""
        # In a real implementation, you would compare current position from odometry
        # with target position using appropriate thresholds
        # This is a simplified version
        return False

    def stop_robot(self):
        """Stop the robot by publishing zero velocities"""
        stop_cmd = Twist()
        self.publisher.publish(stop_cmd)

def main(args=None):
    rclpy.init(args=args)
    
    server = HolonomicActionServer()
    
    # Use MultiThreadedExecutor for better performance
    executor = MultiThreadedExecutor()
    executor.add_node(server)
    
    try:
        executor.spin()
    except KeyboardInterrupt:
        pass
    finally:
        executor.shutdown()
        server.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()