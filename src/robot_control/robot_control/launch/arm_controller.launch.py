from launch import LaunchDescription
from launch_ros.actions import Node
import os
from ament_index_python.packages import get_package_share_directory
from launch.substitutions import Command

def generate_launch_description():
    # Get the package directory
    pkg_dir = get_package_share_directory('robot_control')
    
    # Path to configuration files
    arm_config = os.path.join(pkg_dir, 'config', 'arm_controller_params.yaml')
    controllers_config = os.path.join(pkg_dir, 'config', 'controllers.yaml')
    robot_description = os.path.join(pkg_dir, 'config', 'robot.urdf')

    return LaunchDescription([
        # Robot state publisher
        Node(
            package='robot_state_publisher',
            executable='robot_state_publisher',
            name='robot_state_publisher',
            parameters=[{'robot_description': Command(['cat ', robot_description])}],
            output='screen',
        ),
        
        # Controller manager
        Node(
            package='controller_manager',
            executable='ros2_control_node',
            parameters=[controllers_config, {'robot_description': Command(['cat ', robot_description])}],
            output='screen',
        ),
        
        # Arm controller node
        Node(
            package='robot_control',
            executable='arm_controller_node',
            name='arm_controller',
            parameters=[arm_config],
            output='screen',
            emulate_tty=True,
        ),
        
        # Joint state broadcaster
        Node(
            package='controller_manager',
            executable='spawner',
            name='spawner_joint_state_broadcaster',
            arguments=['joint_state_broadcaster', '--controller-manager', '/controller_manager'],
            output='screen',
        ),
        
        # Arm controller spawner
        Node(
            package='controller_manager',
            executable='spawner',
            name='spawner_arm_controller',
            arguments=['arm_controller', '--controller-manager', '/controller_manager'],
            output='screen',
        )
    ]) 