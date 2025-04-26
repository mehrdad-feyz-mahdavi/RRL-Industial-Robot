// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from my_robot_camera_msgs:msg/Detection.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__TRAITS_HPP_
#define MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "my_robot_camera_msgs/msg/detail/detection__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace my_robot_camera_msgs
{

namespace msg
{

inline void to_flow_style_yaml(
  const Detection & msg,
  std::ostream & out)
{
  out << "{";
  // member: class_id
  {
    out << "class_id: ";
    rosidl_generator_traits::value_to_yaml(msg.class_id, out);
    out << ", ";
  }

  // member: x1
  {
    out << "x1: ";
    rosidl_generator_traits::value_to_yaml(msg.x1, out);
    out << ", ";
  }

  // member: y1
  {
    out << "y1: ";
    rosidl_generator_traits::value_to_yaml(msg.y1, out);
    out << ", ";
  }

  // member: x2
  {
    out << "x2: ";
    rosidl_generator_traits::value_to_yaml(msg.x2, out);
    out << ", ";
  }

  // member: y2
  {
    out << "y2: ";
    rosidl_generator_traits::value_to_yaml(msg.y2, out);
    out << ", ";
  }

  // member: confidence
  {
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Detection & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: class_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "class_id: ";
    rosidl_generator_traits::value_to_yaml(msg.class_id, out);
    out << "\n";
  }

  // member: x1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x1: ";
    rosidl_generator_traits::value_to_yaml(msg.x1, out);
    out << "\n";
  }

  // member: y1
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y1: ";
    rosidl_generator_traits::value_to_yaml(msg.y1, out);
    out << "\n";
  }

  // member: x2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x2: ";
    rosidl_generator_traits::value_to_yaml(msg.x2, out);
    out << "\n";
  }

  // member: y2
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y2: ";
    rosidl_generator_traits::value_to_yaml(msg.y2, out);
    out << "\n";
  }

  // member: confidence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "confidence: ";
    rosidl_generator_traits::value_to_yaml(msg.confidence, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Detection & msg, bool use_flow_style = false)
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

}  // namespace my_robot_camera_msgs

namespace rosidl_generator_traits
{

[[deprecated("use my_robot_camera_msgs::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const my_robot_camera_msgs::msg::Detection & msg,
  std::ostream & out, size_t indentation = 0)
{
  my_robot_camera_msgs::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use my_robot_camera_msgs::msg::to_yaml() instead")]]
inline std::string to_yaml(const my_robot_camera_msgs::msg::Detection & msg)
{
  return my_robot_camera_msgs::msg::to_yaml(msg);
}

template<>
inline const char * data_type<my_robot_camera_msgs::msg::Detection>()
{
  return "my_robot_camera_msgs::msg::Detection";
}

template<>
inline const char * name<my_robot_camera_msgs::msg::Detection>()
{
  return "my_robot_camera_msgs/msg/Detection";
}

template<>
struct has_fixed_size<my_robot_camera_msgs::msg::Detection>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<my_robot_camera_msgs::msg::Detection>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<my_robot_camera_msgs::msg::Detection>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MY_ROBOT_CAMERA_MSGS__MSG__DETAIL__DETECTION__TRAITS_HPP_
