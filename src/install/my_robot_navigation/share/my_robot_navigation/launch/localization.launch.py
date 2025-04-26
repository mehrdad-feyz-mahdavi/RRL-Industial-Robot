import os
from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node

def generate_launch_description():
    # Get the package directory
    pkg_dir = get_package_share_directory('my_robot_navigation')
    
    # Define parameter file path (using whichever exists - amcl_params.yaml or nav2_params.yaml)
    param_file = os.path.join(pkg_dir, 'config', 'amcl_params.yaml')
    if not os.path.exists(param_file):
        param_file = os.path.join(pkg_dir, 'config', 'nav2_params.yaml')
    
    # Define map file path - using the explicit path you requested
    map_yaml_path = os.path.join(
        get_package_share_directory('my_robot_navigation'),
        'config',
        'map.yaml'  # Now looks in install space's config directory
    )
    
    # Print paths for debugging
    print(f"\nParameter file path: {param_file}")
    print(f"Map file path: {map_yaml_path}\n")
    
    # Launch configuration variables
    use_sim_time = LaunchConfiguration('use_sim_time', default='false')
    
    # Declare the launch arguments
    declare_use_sim_time = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='Use simulation clock if true'
    )
    
    # Nodes to launch
    map_server_node = Node(
        package='nav2_map_server',
        executable='map_server',
        name='map_server',
        output='screen',
        parameters=[{'use_sim_time': use_sim_time},
                   {'yaml_filename': map_yaml_path}]  # Using the corrected path here
    )
    
    amcl_node = Node(
        package='nav2_amcl',
        executable='amcl',
        name='amcl',
        output='screen',
        parameters=[param_file,
                   {'use_sim_time': use_sim_time}]
    )
    
    lifecycle_manager = Node(
        package='nav2_lifecycle_manager',
        executable='lifecycle_manager',
        name='lifecycle_manager_localization',
        output='screen',
        parameters=[{'use_sim_time': use_sim_time},
                   {'autostart': True},
                   {'node_names': ['map_server', 'amcl']}]
    )
    
    return LaunchDescription([
        declare_use_sim_time,
        map_server_node,
        amcl_node,
        lifecycle_manager
    ])