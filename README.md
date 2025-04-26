![header](https://capsule-render.vercel.app/api?type=wave&color=auto&height=300&section=header&text=RRL%20render&fontSize=90)


This robotic project is developed by the robotic team at Imam Khomeini International University.

# Main Robot Workspace

This ROS2 workspace contains the packages for the main robot project.

## Project Structure

```
MAIN_ROBOT_WS/
├── src/
│   ├── robot_description/     # URDF, meshes, configs
│   ├── robot_controller/      # Motor controllers
│   ├── slam_toolbox/         # SLAM configs and launch
│   │   └── config/
│   │   └── slam_config.yaml
│   ├── ldlidar_stl_ros2/     # Lidar driver
│   ├── inverse_kinematics/   # IK calculations
│   ├── my_robot_bringup/     # Launch files
│   │   └── launch/
│   ├── my_node/             # Custom node
│   ├── odometry/            # Odometry calculations
│   ├── serial_motor_demo/   # Serial motor control
│   └── serial_motor_demo_msgs/ # Motor control messages
├── scripts/                 # Python/shell scripts
├── .vscode/                # IDE configs
└── README.md              # This file
```

## Prerequisites

- Ubuntu 22.04 or later
- ROS2 Humble
- Python 3.10
- Git

## Installation

1. Clone the repository:
```bash
cd ~/main_robot_ws
git clone <repository-url> src/
```

2. Install dependencies:
```bash
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```

## Building the Workspace

1. Build all packages:
```bash
cd ~/main_robot_ws
colcon build --symlink-install
```

2. Source the workspace:
```bash
source install/setup.bash
```

## Launching the Robot

1. Launch the complete robot system:
```bash
ros2 launch my_robot_bringup robot.launch.py
```

2. Launch with custom SLAM configuration:
```bash
ros2 launch my_robot_bringup robot.launch.py slam_config_path:=/path/to/your/config.yaml
```

## Debugging Steps

### 1. Verify ROS2 Topics

List all active topics:
```bash
ros2 topic list
```

Monitor specific topics:
```bash
# Monitor laser scan data
ros2 topic echo /scan

# Monitor odometry data
ros2 topic echo /odom

# Monitor TF transforms
ros2 topic echo /tf
```

### 2. Visualize with RViz2

1. Launch RViz2:
```bash
rviz2
```

2. Load the default configuration:
```bash
rviz2 -d src/my_robot_bringup/rviz/robot.rviz
```

3. In RViz2, verify:
   - TF Frames (Add -> TF)
   - Laser Scan (Add -> LaserScan)
   - Map (Add -> Map)
   - Robot Model (Add -> RobotModel)

### 3. TF Frame Verification and Error Checking

#### Basic TF Tree Visualization
```bash
# Generate and view the TF tree
ros2 run tf2_tools view_frames.py

# This will create a PDF file showing the TF tree structure
# Open the generated PDF to verify the frame hierarchy
```

#### TF Tree Validation Steps

1. **Check Frame Existence**
```bash
# List all available frames
ros2 run tf2_tools view_frames.py --debug

# Check if specific frames exist
ros2 run tf2_ros tf2_echo base_link laser --timeout 1.0
```

2. **Verify Transform Chain**
```bash
# Check transform from map to base_link
ros2 run tf2_ros tf2_echo map base_link

# Check transform from base_link to laser
ros2 run tf2_ros tf2_echo base_link laser
```

3. **Monitor TF Updates**
```bash
# Monitor TF updates in real-time
ros2 run tf2_ros tf2_monitor base_link laser

# Check TF frequency
ros2 run tf2_ros tf2_echo base_link laser --frequency 1.0
```

#### Common TF Issues and Solutions

1. **Missing Transforms**
   - Check if static transform publishers are running:
   ```bash
   ros2 node list | grep static_transform_publisher
   ```
   - Verify launch file parameters for static transforms
   - Check for typos in frame names

2. **Incorrect Transform Values**
   - Verify static transform parameters in launch files
   - Check for conflicting transforms from multiple nodes
   - Use `tf2_echo` to compare expected vs actual values

3. **TF Tree Structure Issues**
   - Ensure proper parent-child relationships
   - Check for circular dependencies
   - Verify frame naming conventions

4. **Performance Issues**
   - Monitor TF update frequency
   - Check for transform lookup timeouts
   - Verify buffer sizes in launch configurations

#### TF Debugging Tools

1. **TF Tree Visualization**
```bash
# Generate detailed TF tree report
ros2 run tf2_tools view_frames.py --debug > tf_tree_debug.txt
```

2. **Transform Statistics**
```bash
# Monitor transform statistics
ros2 run tf2_ros tf2_monitor --stats base_link laser
```

3. **TF Buffer Inspection**
```bash
# Check TF buffer contents
ros2 run tf2_ros tf2_echo --buffer 1.0 base_link laser
```

### 4. Node Status

List running nodes:
```bash
ros2 node list
```

Get node info:
```bash
ros2 node info /node_name
```

## Frame Standardization

The following frame names are standardized:
- `/base_link_to_laser` - Transform from base_link to laser frame
- `/base_link` - Base link frame
- `/map` - Map frame
- `/odom` - Odometry frame

## Dependencies

### ROS2 Packages
- rclcpp
- geometry_msgs
- sensor_msgs
- tf2
- tf2_ros
- slam_toolbox
- rviz2
- robot_state_publisher
- joint_state_publisher

### Python Dependencies
- Python 3.10
- numpy
- scipy
- matplotlib

## Troubleshooting

1. **Build Errors**
   - Clean build: `rm -rf build/ install/ log/`
   - Rebuild: `colcon build --symlink-install`

2. **Launch File Issues**
   - Check file permissions: `chmod +x src/my_robot_bringup/launch/*.py`
   - Verify package dependencies in package.xml

3. **TF Issues**
   - Check frame names match in launch files and code
   - Verify static transforms are published
   - Use `ros2 run tf2_tools view_frames` to debug TF tree

4. **Sensor Issues**
   - Check device permissions
   - Verify topic names match in launch files
   - Monitor sensor topics with `ros2 topic echo`

## Contributing

1. Create a new branch for your feature
2. Make your changes
3. Test thoroughly
4. Submit a pull request

## License

[Add your license information here] 
=======
# RRL-Industial-Robot
>>>>>>> origin/main
