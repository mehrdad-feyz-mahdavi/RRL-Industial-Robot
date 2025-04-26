// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from robot_control_interfaces:srv/ArmPreset.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__BUILDER_HPP_
#define ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "robot_control_interfaces/srv/detail/arm_preset__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace robot_control_interfaces
{

namespace srv
{

namespace builder
{

class Init_ArmPreset_Request_preset_num
{
public:
  Init_ArmPreset_Request_preset_num()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::robot_control_interfaces::srv::ArmPreset_Request preset_num(::robot_control_interfaces::srv::ArmPreset_Request::_preset_num_type arg)
  {
    msg_.preset_num = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_control_interfaces::srv::ArmPreset_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_control_interfaces::srv::ArmPreset_Request>()
{
  return robot_control_interfaces::srv::builder::Init_ArmPreset_Request_preset_num();
}

}  // namespace robot_control_interfaces


namespace robot_control_interfaces
{

namespace srv
{

namespace builder
{

class Init_ArmPreset_Response_message
{
public:
  explicit Init_ArmPreset_Response_message(::robot_control_interfaces::srv::ArmPreset_Response & msg)
  : msg_(msg)
  {}
  ::robot_control_interfaces::srv::ArmPreset_Response message(::robot_control_interfaces::srv::ArmPreset_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::robot_control_interfaces::srv::ArmPreset_Response msg_;
};

class Init_ArmPreset_Response_success
{
public:
  Init_ArmPreset_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ArmPreset_Response_message success(::robot_control_interfaces::srv::ArmPreset_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ArmPreset_Response_message(msg_);
  }

private:
  ::robot_control_interfaces::srv::ArmPreset_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::robot_control_interfaces::srv::ArmPreset_Response>()
{
  return robot_control_interfaces::srv::builder::Init_ArmPreset_Response_success();
}

}  // namespace robot_control_interfaces

#endif  // ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__BUILDER_HPP_
