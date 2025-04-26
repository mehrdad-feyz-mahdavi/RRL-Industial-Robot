cmake_minimum_required(VERSION 3.8)
project(my_robot_navigation)

# Default to C++17
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

# Compiler warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Find dependencies
find_package(ament_cmake REQUIRED)
find_package(nav2_bringup REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(geometry_msgs REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(geometry_msgs REQUIRED)

# Install configuration files
install(
  DIRECTORY config launch behavior_trees
  DESTINATION share/${PROJECT_NAME}
)

# Install Python launch files if any
install(
  DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
  PATTERN "*.py"
)

# Install param files
install(
  DIRECTORY config
  DESTINATION share/${PROJECT_NAME}
  PATTERN "*.yaml"
  PATTERN "*.xml"
)

# Install behavior tree files
install(
  FILES
    behavior_trees/navigate_w_recovery_advanced.xml
  DESTINATION share/${PROJECT_NAME}/behavior_trees
)

# نصب فایل پایتون به عنوان اسکریپت اجرایی
install(PROGRAMS
  scripts/holonomic_action.py
  DESTINATION lib/${PROJECT_NAME}
)

# Install map files
install(
  DIRECTORY maps/
  DESTINATION share/${PROJECT_NAME}/maps
)

rosidl_generate_interfaces(${PROJECT_NAME}
  "action/MoveHolonomic.action"
  DEPENDENCIES geometry_msgs
)

# Testing
if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # Skip copyright check (uncomment after adding licenses)
  set(ament_cmake_copyright_FOUND TRUE)
  # Skip cpplint (uncomment when in git repo)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()