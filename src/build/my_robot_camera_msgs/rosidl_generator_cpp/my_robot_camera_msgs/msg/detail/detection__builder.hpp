// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_robot_camera_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_
#define MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_robot_camera_msgs/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_robot_camera_msgs
{

namespace msg
{

namespace builder
{

class Init_Detection_confidence
{
public:
  explicit Init_Detection_confidence(::my_robot_camera_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  ::my_robot_camera_msgs::msg::Detection confidence(::my_robot_camera_msgs::msg::Detection::_confidence_type arg)
  {
    msg_.confidence = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::Detection msg_;
};

class Init_Detection_y2
{
public:
  explicit Init_Detection_y2(::my_robot_camera_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_confidence y2(::my_robot_camera_msgs::msg::Detection::_y2_type arg)
  {
    msg_.y2 = std::move(arg);
    return Init_Detection_confidence(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::Detection msg_;
};

class Init_Detection_x2
{
public:
  explicit Init_Detection_x2(::my_robot_camera_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_y2 x2(::my_robot_camera_msgs::msg::Detection::_x2_type arg)
  {
    msg_.x2 = std::move(arg);
    return Init_Detection_y2(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::Detection msg_;
};

class Init_Detection_y1
{
public:
  explicit Init_Detection_y1(::my_robot_camera_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_x2 y1(::my_robot_camera_msgs::msg::Detection::_y1_type arg)
  {
    msg_.y1 = std::move(arg);
    return Init_Detection_x2(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::Detection msg_;
};

class Init_Detection_x1
{
public:
  explicit Init_Detection_x1(::my_robot_camera_msgs::msg::Detection & msg)
  : msg_(msg)
  {}
  Init_Detection_y1 x1(::my_robot_camera_msgs::msg::Detection::_x1_type arg)
  {
    msg_.x1 = std::move(arg);
    return Init_Detection_y1(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::Detection msg_;
};

class Init_Detection_class_id
{
public:
  Init_Detection_class_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Detection_x1 class_id(::my_robot_camera_msgs::msg::Detection::_class_id_type arg)
  {
    msg_.class_id = std::move(arg);
    return Init_Detection_x1(msg_);
  }

private:
  ::my_robot_camera_msgs::msg::Detection msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_camera_msgs::msg::Detection>()
{
  return my_robot_camera_msgs::msg::builder::Init_Detection_class_id();
}

}  // namespace my_robot_camera_msgs

#endif  // MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__BUILDER_HPP_
