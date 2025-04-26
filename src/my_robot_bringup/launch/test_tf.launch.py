from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        # Static Transform Publisher for testing
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='test_tf_publisher',
            arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'test_frame'],
            output='screen'
        )
    ]) 