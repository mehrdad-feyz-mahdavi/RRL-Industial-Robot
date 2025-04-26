cmake_minimum_required(VERSION 3.8)
project(my_robot_bringup)

find_package(ament_cmake REQUIRED)

install(DIRECTORY
  launch
  config
  maps
  scripts
  rviz
  DESTINATION share/${PROJECT_NAME}
)

ament_package()

