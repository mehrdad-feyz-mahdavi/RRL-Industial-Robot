// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_control_interfaces:msg/ArmCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__BUILDER_HPP_
#define ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_control_interfaces/msg/detail/arm_command__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_control_interfaces
{

namespace msg
{

namespace builder
{

class Init_ArmCommand_speed
{
public:
  explicit Init_ArmCommand_speed(::robot_control_interfaces::msg::ArmCommand & msg)
  : msg_(msg)
  {}
  ::robot_control_interfaces::msg::ArmCommand speed(::robot_control_interfaces::msg::ArmCommand::_speed_type arg)
  {
    msg_.speed = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_control_interfaces::msg::ArmCommand msg_;
};

class Init_ArmCommand_angle
{
public:
  explicit Init_ArmCommand_angle(::robot_control_interfaces::msg::ArmCommand & msg)
  : msg_(msg)
  {}
  Init_ArmCommand_speed angle(::robot_control_interfaces::msg::ArmCommand::_angle_type arg)
  {
    msg_.angle = std::move(arg);
    return Init_ArmCommand_speed(msg_);
  }

private:
  ::robot_control_interfaces::msg::ArmCommand msg_;
};

class Init_ArmCommand_joint_num
{
public:
  Init_ArmCommand_joint_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArmCommand_angle joint_num(::robot_control_interfaces::msg::ArmCommand::_joint_num_type arg)
  {
    msg_.joint_num = std::move(arg);
    return Init_ArmCommand_angle(msg_);
  }

private:
  ::robot_control_interfaces::msg::ArmCommand msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_control_interfaces::msg::ArmCommand>()
{
  return robot_control_interfaces::msg::builder::Init_ArmCommand_joint_num();
}

}  // namespace robot_control_interfaces

#endif  // ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__BUILDER_HPP_
