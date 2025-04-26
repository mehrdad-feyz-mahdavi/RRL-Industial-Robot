import os
from launch import LaunchDescription
from launch.actions import ExecuteProcess, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import FindExecutable
from ament_index_python.packages import get_package_share_directory

def generate_launch_description():

    saving_map = False
    # ${PACKAGE_PATH}/maps/map.pgm
    ld = LaunchDescription()

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

    # 5. Run SLAM Toolbox
    slam_toolbox = ExecuteProcess(
        cmd=[
            'ros2', 'run', 'slam_toolbox', 'async_slam_toolbox_node',
            '--ros-args',
            '--params-file', './src/slam_toolbox/config/slam_config.yaml'
        ],
        output='screen'
    )

    # 6. Run robot server
    robot_server = ExecuteProcess(
        cmd=['ros2', 'run', 'robot_control', 'robot_server'],
        output='screen'
    )

    # 6. Run robot server
    old_robot_server = ExecuteProcess(
        cmd=['ros2', 'run', 'robot_control', 'old_robot_server'],
        output='screen'
    )

    # 7. Run arm server
    arm_server = ExecuteProcess(
        cmd=['ros2', 'run', 'robot_control', 'arm_server'],
        output='screen'
    )

    # 8. Launch Nav2
    nav2_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('my_robot_navigation'),
            '/launch/navigation_launch.py'
        ])
    )


    ####### for amcl:
    map_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('my_robot_navigation'),
            '/launch/map_server.launch.py'
        ])
    )

    lifecycle_map_server_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('my_robot_navigation'),
            '/launch/lifecycle_map_server.launch.py'
        ])
    )

    online_async_slam_toolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('slam_toolbox'),
            '/launch/online_async_launch.py'
        ])
    )

    offline_async_slam_toolbox_launch = IncludeLaunchDescription(
        PythonLaunchDescriptionSource([
            get_package_share_directory('slam_toolbox'),
            '/launch/offline_launch.py'
        ])
    )
    # nav2_launch = IncludeLaunchDescription(
    #     PythonLaunchDescriptionSource([
    #         get_package_share_directory('nav2_bringup'),
    #         '/launch/navigation_launch.py'
    #     ]), 
    #     launch_arguments={
    #         'use_sim_time': 'false',
    #         'planner_server.expected_planner_frequency': '5.0',
    #         'local_costmap.publish_frequency': '10.0',
    #         'global_costmap.publish_frequency': '5.0'
    #     }.items()
    # )

    # 8. Launch RViz2
    rviz2 = ExecuteProcess(
        cmd=['rviz2'],
        output='screen'
    )

    if saving_map:
        ld.add_action(rsp_launch)
        ld.add_action(ldlidar_launch)
        ld.add_action(lidar_filter)
        # ld.add_action(camera_node)
        ld.add_action(slam_toolbox)
        ld.add_action(robot_server)
        ld.add_action(map_server_launch)
        # ld.add_action(lifecycle_map_server_launch)
        # ld.add_action(online_async_slam_toolbox_launch)
        ld.add_action(nav2_launch)
        ld.add_action(rviz2)
    else:
        ld.add_action(rsp_launch)
        ld.add_action(ldlidar_launch)
        ld.add_action(lidar_filter)
        ld.add_action(camera_node)
        # ld.add_action(slam_toolbox)
        # ld.add_action(robot_server)
        ld.add_action(map_server_launch)
        ld.add_action(lifecycle_map_server_launch)
        ld.add_action(online_async_slam_toolbox_launch)
        # ld.add_action(offline_async_slam_toolbox_launch)
        ld.add_action(nav2_launch)
        # ld.add_action(arm_server)
        # ld.add_action(rviz2)
    return ld