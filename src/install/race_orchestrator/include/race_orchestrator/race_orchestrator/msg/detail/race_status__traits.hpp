// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__TRAITS_HPP_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "race_orchestrator/msg/detail/race_status__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace race_orchestrator
{

namespace msg
{

inline void to_flow_style_yaml(
  const RaceStatus & msg,
  std::ostream & out)
{
  out << "{";
  // member: race_id
  {
    out << "race_id: ";
    rosidl_generator_traits::value_to_yaml(msg.race_id, out);
    out << ", ";
  }

  // member: robot_id
  {
    out << "robot_id: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_id, out);
    out << ", ";
  }

  // member: current_time
  {
    out << "current_time: ";
    rosidl_generator_traits::value_to_yaml(msg.current_time, out);
    out << ", ";
  }

  // member: remaining_time
  {
    out << "remaining_time: ";
    rosidl_generator_traits::value_to_yaml(msg.remaining_time, out);
    out << ", ";
  }

  // member: current_object
  {
    out << "current_object: ";
    rosidl_generator_traits::value_to_yaml(msg.current_object, out);
    out << ", ";
  }

  // member: objects_collected
  {
    out << "objects_collected: ";
    rosidl_generator_traits::value_to_yaml(msg.objects_collected, out);
    out << ", ";
  }

  // member: total_objects
  {
    out << "total_objects: ";
    rosidl_generator_traits::value_to_yaml(msg.total_objects, out);
    out << ", ";
  }

  // member: current_position
  {
    if (msg.current_position.size() == 0) {
      out << "current_position: []";
    } else {
      out << "current_position: [";
      size_t pending_items = msg.current_position.size();
      for (auto item : msg.current_position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: next_checkpoint
  {
    if (msg.next_checkpoint.size() == 0) {
      out << "next_checkpoint: []";
    } else {
      out << "next_checkpoint: [";
      size_t pending_items = msg.next_checkpoint.size();
      for (auto item : msg.next_checkpoint) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: race_completed
  {
    out << "race_completed: ";
    rosidl_generator_traits::value_to_yaml(msg.race_completed, out);
    out << ", ";
  }

  // member: race_failed
  {
    out << "race_failed: ";
    rosidl_generator_traits::value_to_yaml(msg.race_failed, out);
    out << ", ";
  }

  // member: failure_reason
  {
    out << "failure_reason: ";
    rosidl_generator_traits::value_to_yaml(msg.failure_reason, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RaceStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: race_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "race_id: ";
    rosidl_generator_traits::value_to_yaml(msg.race_id, out);
    out << "\n";
  }

  // member: robot_id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "robot_id: ";
    rosidl_generator_traits::value_to_yaml(msg.robot_id, out);
    out << "\n";
  }

  // member: current_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_time: ";
    rosidl_generator_traits::value_to_yaml(msg.current_time, out);
    out << "\n";
  }

  // member: remaining_time
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "remaining_time: ";
    rosidl_generator_traits::value_to_yaml(msg.remaining_time, out);
    out << "\n";
  }

  // member: current_object
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "current_object: ";
    rosidl_generator_traits::value_to_yaml(msg.current_object, out);
    out << "\n";
  }

  // member: objects_collected
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "objects_collected: ";
    rosidl_generator_traits::value_to_yaml(msg.objects_collected, out);
    out << "\n";
  }

  // member: total_objects
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "total_objects: ";
    rosidl_generator_traits::value_to_yaml(msg.total_objects, out);
    out << "\n";
  }

  // member: current_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.current_position.size() == 0) {
      out << "current_position: []\n";
    } else {
      out << "current_position:\n";
      for (auto item : msg.current_position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: next_checkpoint
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.next_checkpoint.size() == 0) {
      out << "next_checkpoint: []\n";
    } else {
      out << "next_checkpoint:\n";
      for (auto item : msg.next_checkpoint) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: race_completed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "race_completed: ";
    rosidl_generator_traits::value_to_yaml(msg.race_completed, out);
    out << "\n";
  }

  // member: race_failed
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "race_failed: ";
    rosidl_generator_traits::value_to_yaml(msg.race_failed, out);
    out << "\n";
  }

  // member: failure_reason
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "failure_reason: ";
    rosidl_generator_traits::value_to_yaml(msg.failure_reason, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RaceStatus & msg, bool use_flow_style = false)
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

}  // namespace race_orchestrator

namespace rosidl_generator_traits
{

[[deprecated("use race_orchestrator::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const race_orchestrator::msg::RaceStatus & msg,
  std::ostream & out, size_t indentation = 0)
{
  race_orchestrator::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use race_orchestrator::msg::to_yaml() instead")]]
inline std::string to_yaml(const race_orchestrator::msg::RaceStatus & msg)
{
  return race_orchestrator::msg::to_yaml(msg);
}

template<>
inline const char * data_type<race_orchestrator::msg::RaceStatus>()
{
  return "race_orchestrator::msg::RaceStatus";
}

template<>
inline const char * name<race_orchestrator::msg::RaceStatus>()
{
  return "race_orchestrator/msg/RaceStatus";
}

template<>
struct has_fixed_size<race_orchestrator::msg::RaceStatus>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<race_orchestrator::msg::RaceStatus>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<race_orchestrator::msg::RaceStatus>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__TRAITS_HPP_
