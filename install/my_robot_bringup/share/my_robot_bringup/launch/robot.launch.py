import os
from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import FindExecutable
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():
    # Set to True for SLAM (mapping), False for AMCL (localization)
    saving_map = False
    ld = LaunchDescription()

    # ===== Common Components (needed for both SLAM and AMCL) =====
    # 1. Launch LDLidar
    ldlidar_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('ldlidar_stl_ros2'),
            '/launch/ld19.launch.py'
        ])
    )

    # 2. Run lidar front filter
    lidar_filter = ExecuteProcess(
        cmd=['ros2', 'run', 'lidar_front_filter', 'lidar_front_filter'],
        output='screen'
    )

    # 3. Launch robot state publisher
    rsp_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('robot_description'),
            '/launch/rsp.launch.py'
        ])
    )

    # 4. Run camera node
    camera_node = ExecuteProcess(
        cmd=['ros2', 'launch', 'my_robot_camera', 'camera.launch.py'],
        output='screen'
    )

    # 5. Run robot server
    robot_server = ExecuteProcess(
        cmd=['ros2', 'run', 'robot_control', 'robot_server'],
        output='screen'
    )

    # 6. Run old robot server
    old_robot_server = ExecuteProcess(
        cmd=['ros2', 'run', 'robot_control', 'old_robot_server'],
        output='screen'
    )

    # 7. Run arm server
    arm_server = ExecuteProcess(
        cmd=['ros2', 'run', 'robot_control', 'arm_server'],
        output='screen'
    )

    # ===== SLAM Components (only for mapping) =====
    # 8. Run SLAM Toolbox
    slam_toolbox = ExecuteProcess(
        cmd=[
            'ros2', 'run', 'slam_toolbox', 'async_slam_toolbox_node',
            '--ros-args',
            '--params-file', './src/slam_toolbox/config/slam_config.yaml'
        ],
        output='screen'
    )

    # ===== AMCL Components (only for localization) =====
    # 9. Map server launch
    map_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('my_robot_navigation'),
            '/launch/map_server.launch.py'
        ])
    )

    # 10. Lifecycle map server launch
    lifecycle_map_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('my_robot_navigation'),
            '/launch/lifecycle_map_server.launch.py'
        ])
    )

    # 11. Online async SLAM toolbox launch
    online_async_slam_toolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('slam_toolbox'),
            '/launch/online_async_launch.py'
        ])
    )

    # 12. Offline async SLAM toolbox launch
    offline_async_slam_toolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('slam_toolbox'),
            '/launch/offline_launch.py'
        ])
    )

    # 13. Launch Nav2
    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('my_robot_navigation'),
            '/launch/navigation_launch.py'
        ])
    )

    # 14. Launch RViz2
    rviz2 = ExecuteProcess(
        cmd=['rviz2'],
        output='screen'
    )

    # 15. Odometry reset command
    reset_odom = ExecuteProcess(
        cmd=['ros2', 'topic', 'pub', '-1', '/initialpose', 'geometry_msgs/msg/PoseWithCovarianceStamped', 
             '{header: {stamp: {sec: 0, nanosec: 0}, frame_id: "map"}, pose: {pose: {position: {x: 0.0, y: 0.0, z: 0.0}, orientation: {x: 0.0, y: 0.0, z: 0.0, w: 1.0}}, covariance: [0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0]}}'],
        output='screen'
    )

    if saving_map:
        # SLAM configuration (mapping)
        ld.add_action(reset_odom)  # Reset odometry before starting SLAM
        ld.add_action(rsp_launch)
        ld.add_action(ldlidar_launch)
        ld.add_action(lidar_filter)
        ld.add_action(camera_node)
        ld.add_action(slam_toolbox)
        ld.add_action(robot_server)
        ld.add_action(rviz2)
    else:
        # AMCL configuration (localization)
        ld.add_action(reset_odom)  # Reset odometry before starting AMCL
        ld.add_action(rsp_launch)
        ld.add_action(ldlidar_launch)
        ld.add_action(lidar_filter)
        ld.add_action(camera_node)
        ld.add_action(map_server_launch)
        ld.add_action(lifecycle_map_server_launch)
        # ld.add_action(online_async_slam_toolbox_launch)
        ld.add_action(nav2_launch)
        # ld.add_action(arm_server)
        ld.add_action(old_robot_server)
        ld.add_action(rviz2)

    return ld


# my_robot_navigation/maps/map.pgm
# ros2 run nav2_map_server map_saver_cli -f ~/main_robot_ws/src/my_robot_navigation/maps/map --ros-args