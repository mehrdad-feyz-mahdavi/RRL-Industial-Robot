// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_robot_camera_msgs:msg/DetectionArray.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION_ARRAY__BUILDER_HPP_
#define MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_robot_camera_msgs/msg/detail/detection_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_robot_camera_msgs
{

namespace msg
{

namespace builder
{

class Init_DetectionArray_detections
{
public:
  explicit Init_DetectionArray_detections(::my_robot_camera_msgs::msg::DetectionArray & msg)
  : msg_(msg)
  {}
  ::my_robot_camera_msgs::msg::DetectionArray detections(::my_robot_camera_msgs::msg::DetectionArray::_detections_type arg)
  {
    msg_.detections = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::DetectionArray msg_;
};

class Init_DetectionArray_header
{
public:
  Init_DetectionArray_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_DetectionArray_detections header(::my_robot_camera_msgs::msg::DetectionArray::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_DetectionArray_detections(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::DetectionArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_camera_msgs::msg::DetectionArray>()
{
  return my_robot_camera_msgs::msg::builder::Init_DetectionArray_header();
}

}  // namespace my_robot_camera_msgs

#endif  // MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION_ARRAY__BUILDER_HPP_
