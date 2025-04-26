#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist, Quaternion, TransformStamped
from sensor_msgs.msg import JointState
from tf2_ros import TransformBroadcaster
import math

class RobotStatePublisher(Node):
    def __init__(self):
        super().__init__('robot_state_publisher')
        
        # Physical parameters (converted to meters)
        self.wheel_radius = 0.075  # 7.5cm radius
        self.track_width = 0.24    # 45cm between left/right wheels
        self.wheel_base = 0.45     # 24cm between front/rear wheels
        
        # Robot state
        self.robot_x = 0.0
        self.robot_y = 0.0
        self.robot_theta = 0.0
        
        # Wheel joint positions
        self.wheel_positions = {
            'left_down_wheel_joint': 0.0,
            'right_down_wheel_joint': 0.0,
            'left_up_wheel_joint': 0.0,
            'right_up_wheel_joint': 0.0
        }
        
        # Wheel velocities (rad/s)
        self.wheel_velocities = {
            'left_down_wheel_joint': 0.0,
            'right_down_wheel_joint': 0.0,
            'left_up_wheel_joint': 0.0,
            'right_up_wheel_joint': 0.0
        }
        
        # TF Broadcaster
        self.tf_broadcaster = TransformBroadcaster(self)
        
        # Publishers/Subscribers
        self.joint_pub = self.create_publisher(JointState, 'joint_states', 10)
        # self.cmd_vel_sub = self.create_subscription(
        #     Twist, '/cmd_vel', self.cmd_vel_callback, 10)
        
        # Main update timer (30Hz)
        self.timer = self.create_timer(1.0/30.0, self.update_state)

    def cmd_vel_callback(self, msg):
        """Convert velocity commands to wheel rotations"""
        linear_x = msg.linear.x
        linear_y = msg.linear.y
        angular_vel = msg.angular.z
        
        # Mecanum wheel kinematics (corrected)
        # For standard mecanum wheels with rollers at 45 degrees
        L = self.track_width / 2
        W = self.wheel_base / 2
        R = self.wheel_radius
        
        # Calculate wheel velocities (rad/s)
        self.wheel_velocities['left_up_wheel_joint'] = (linear_x - linear_y - (L + W) * angular_vel) / R
        self.wheel_velocities['right_up_wheel_joint'] = (linear_x + linear_y + (L + W) * angular_vel) / R
        self.wheel_velocities['left_down_wheel_joint'] = (linear_x + linear_y - (L + W) * angular_vel) / R
        self.wheel_velocities['right_down_wheel_joint'] = (linear_x - linear_y + (L + W) * angular_vel) / R
        
        self.get_logger().info(f'Wheel velocities: {self.wheel_velocities}')

    def update_state(self):
        """Main update function"""
        now = self.get_clock().now()
        dt = 1.0/30.0  # Time since last update
        
        # Update wheel positions based on velocities
        for wheel in self.wheel_positions:
            self.wheel_positions[wheel] += self.wheel_velocities[wheel] * dt
        
        self.publish_joint_states()
        self.publish_transforms(dt)

    def publish_joint_states(self):
        """Publish current wheel positions"""
        joint_state = JointState()
        joint_state.header.stamp = self.get_clock().now().to_msg()
        joint_state.name = [
            'left_down_wheel_joint',
            'right_down_wheel_joint',
            'left_up_wheel_joint',
            'right_up_wheel_joint'
        ]
        joint_state.position = [
            self.wheel_positions['left_down_wheel_joint'],
            self.wheel_positions['right_down_wheel_joint'],
            self.wheel_positions['left_up_wheel_joint'],
            self.wheel_positions['right_up_wheel_joint']
        ]
        joint_state.velocity = [
            self.wheel_velocities['left_down_wheel_joint'],
            self.wheel_velocities['right_down_wheel_joint'],
            self.wheel_velocities['left_up_wheel_joint'],
            self.wheel_velocities['right_up_wheel_joint']
        ]
        self.joint_pub.publish(joint_state)

    def publish_transforms(self, dt):
        """Publish complete TF tree"""
        now = self.get_clock().now().to_msg()
        
        # Calculate odometry from all wheel movements (mecanum-specific)
        # Average the contributions from all wheels
        R = self.wheel_radius
        L = self.track_width / 2
        W = self.wheel_base / 2
        const_v = 8
        # Calculate robot velocity in body frame
        vx = R * (self.wheel_velocities['left_up_wheel_joint'] + 
                    self.wheel_velocities['right_up_wheel_joint'] + 
                    self.wheel_velocities['left_down_wheel_joint'] + 
                    self.wheel_velocities['right_down_wheel_joint']) * const_v
        
        vy = R * (-self.wheel_velocities['left_up_wheel_joint'] + 
                    self.wheel_velocities['right_up_wheel_joint'] + 
                    self.wheel_velocities['left_down_wheel_joint'] - 
                    self.wheel_velocities['right_down_wheel_joint']) * const_v
        
        omega = R/((L + W)) * (-self.wheel_velocities['left_up_wheel_joint'] + 
                                self.wheel_velocities['right_up_wheel_joint'] - 
                                self.wheel_velocities['left_down_wheel_joint'] + 
                                self.wheel_velocities['right_down_wheel_joint']) * const_v
        
        # Update robot pose
        self.robot_theta += omega * dt
        self.robot_x += (vx * math.cos(self.robot_theta) - vy * math.sin(self.robot_theta)) * dt
        self.robot_y += (vx * math.sin(self.robot_theta) + vy * math.cos(self.robot_theta)) * dt
        
        # 1. Odom to base_link transform
        odom_tf = TransformStamped()
        odom_tf.header.stamp = now
        odom_tf.header.frame_id = "odom"
        odom_tf.child_frame_id = "base_link"
        odom_tf.transform.translation.x = self.robot_x
        odom_tf.transform.translation.y = self.robot_y
        odom_tf.transform.translation.z = 0.0
        
        q = Quaternion()
        q.z = math.sin(self.robot_theta/2)
        q.w = math.cos(self.robot_theta/2)
        odom_tf.transform.rotation = q
        self.tf_broadcaster.sendTransform(odom_tf)
        
        # 2. Wheel transforms (4 wheels)sudo apt install ros-humble-nav2-map-server ros-humble-nav2-util
        wheel_poses = {
            'left_down_wheel': (self.track_width/2, self.wheel_base/2, -self.wheel_radius),
            'right_down_wheel': (-self.track_width/2, self.wheel_base/2, -self.wheel_radius),
            'left_up_wheel': (self.track_width/2, -self.wheel_base/2, -self.wheel_radius),
            'right_up_wheel': (-self.track_width/2, -self.wheel_base/2, -self.wheel_radius)
        }
        
        for wheel, (x, y, z) in wheel_poses.items():
            tf = TransformStamped()
            tf.header.stamp = now
            tf.header.frame_id = "base_link"
            tf.child_frame_id = f"{wheel}_link"
            tf.transform.translation.x = x
            tf.transform.translation.y = y
            tf.transform.translation.z = z
            
            # Wheel rotation (90° around X axis plus actual wheel rotation)
            angle = self.wheel_positions[f"{wheel}_joint"]
            q = Quaternion()
            q.x = math.sin(math.pi/4)  # 90° rotation around X
            q.w = math.cos(math.pi/4)
            tf.transform.rotation = q
            
            self.tf_broadcaster.sendTransform(tf)

def main():
    rclpy.init()
    node = RobotStatePublisher()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()