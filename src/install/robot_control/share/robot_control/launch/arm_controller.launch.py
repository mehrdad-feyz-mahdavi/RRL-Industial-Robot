from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    config = os.path.join(
        get_package_share_directory('robot_control'),
        'config',
        'arm_controller_params.yaml'
    )

    return LaunchDescription([
        Node(
            package='robot_control',
            executable='arm_controller_node',
            name='arm_controller',
            parameters=[config],
            output='screen',
            emulate_tty=True,
        )
    ]) 