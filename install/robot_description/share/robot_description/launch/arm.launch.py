import os
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Get the package directory
    pkg_robot_description = get_package_share_directory('robot_description')
    
    # Path to the arm xacro file
    arm_xacro = os.path.join(pkg_robot_description, 'description', 'arm.urdf.xacro')
    
    # Declare launch arguments
    use_sim_time = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='Use simulation (Gazebo) clock if true'
    )
    
    # Create the robot state publisher node for the arm
    arm_state_publisher = Node(
        package='robot_state_publisher',
        executable='robot_state_publisher',
        name='arm_state_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': LaunchConfiguration('use_sim_time'),
            'robot_description': f'$(xacro {arm_xacro})'
        }]
    )
    
    # Create the launch description
    ld = LaunchDescription()
    
    # Add the launch arguments
    ld.add_action(use_sim_time)
    
    # Add the nodes
    ld.add_action(arm_state_publisher)
    
    return ld 