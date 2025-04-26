// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from robot_control_interfaces:msg/ArmCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__TRAITS_HPP_
#define ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "robot_control_interfaces/msg/detail/arm_command__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace robot_control_interfaces
{

namespace msg
{

inline void to_flow_style_yaml(
  const ArmCommand & msg,
  std::ostream & out)
{
  out << "{";
  // member: joint_num
  {
    out << "joint_num: ";
    rosidl_generator_traits::value_to_yaml(msg.joint_num, out);
    out << ", ";
  }

  // member: angle
  {
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << ", ";
  }

  // member: speed
  {
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const ArmCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: joint_num
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "joint_num: ";
    rosidl_generator_traits::value_to_yaml(msg.joint_num, out);
    out << "\n";
  }

  // member: angle
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "angle: ";
    rosidl_generator_traits::value_to_yaml(msg.angle, out);
    out << "\n";
  }

  // member: speed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "speed: ";
    rosidl_generator_traits::value_to_yaml(msg.speed, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const ArmCommand & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace robot_control_interfaces

namespace rosidl_generator_traits
{

[[deprecated("use robot_control_interfaces::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const robot_control_interfaces::msg::ArmCommand & msg,
  std::ostream & out, size_t indentation = 0)
{
  robot_control_interfaces::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use robot_control_interfaces::msg::to_yaml() instead")]]
inline std::string to_yaml(const robot_control_interfaces::msg::ArmCommand & msg)
{
  return robot_control_interfaces::msg::to_yaml(msg);
}

template<>
inline const char * data_type<robot_control_interfaces::msg::ArmCommand>()
{
  return "robot_control_interfaces::msg::ArmCommand";
}

template<>
inline const char * name<robot_control_interfaces::msg::ArmCommand>()
{
  return "robot_control_interfaces/msg/ArmCommand";
}

template<>
struct has_fixed_size<robot_control_interfaces::msg::ArmCommand>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<robot_control_interfaces::msg::ArmCommand>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<robot_control_interfaces::msg::ArmCommand>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__TRAITS_HPP_
