// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__TRAITS_HPP_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "race_orchestrator/msg/detail/race_parameters__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace race_orchestrator
{

namespace msg
{

inline void to_flow_style_yaml(
  const RaceParameters & msg,
  std::ostream & out)
{
  out << "{";
  // member: race_id
  {
    out << "race_id: ";
    rosidl_generator_traits::value_to_yaml(msg.race_id, out);
    out << ", ";
  }

  // member: object_sequence
  {
    if (msg.object_sequence.size() == 0) {
      out << "object_sequence: []";
    } else {
      out << "object_sequence: [";
      size_t pending_items = msg.object_sequence.size();
      for (auto item : msg.object_sequence) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: time_limit
  {
    out << "time_limit: ";
    rosidl_generator_traits::value_to_yaml(msg.time_limit, out);
    out << ", ";
  }

  // member: checkpoints
  {
    if (msg.checkpoints.size() == 0) {
      out << "checkpoints: []";
    } else {
      out << "checkpoints: [";
      size_t pending_items = msg.checkpoints.size();
      for (auto item : msg.checkpoints) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: enable_obstacles
  {
    out << "enable_obstacles: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_obstacles, out);
    out << ", ";
  }

  // member: obstacle_density
  {
    out << "obstacle_density: ";
    rosidl_generator_traits::value_to_yaml(msg.obstacle_density, out);
    out << ", ";
  }

  // member: start_position
  {
    if (msg.start_position.size() == 0) {
      out << "start_position: []";
    } else {
      out << "start_position: [";
      size_t pending_items = msg.start_position.size();
      for (auto item : msg.start_position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
    out << ", ";
  }

  // member: goal_position
  {
    if (msg.goal_position.size() == 0) {
      out << "goal_position: []";
    } else {
      out << "goal_position: [";
      size_t pending_items = msg.goal_position.size();
      for (auto item : msg.goal_position) {
        rosidl_generator_traits::value_to_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const RaceParameters & msg,
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

  // member: object_sequence
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.object_sequence.size() == 0) {
      out << "object_sequence: []\n";
    } else {
      out << "object_sequence:\n";
      for (auto item : msg.object_sequence) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: time_limit
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "time_limit: ";
    rosidl_generator_traits::value_to_yaml(msg.time_limit, out);
    out << "\n";
  }

  // member: checkpoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.checkpoints.size() == 0) {
      out << "checkpoints: []\n";
    } else {
      out << "checkpoints:\n";
      for (auto item : msg.checkpoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: enable_obstacles
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "enable_obstacles: ";
    rosidl_generator_traits::value_to_yaml(msg.enable_obstacles, out);
    out << "\n";
  }

  // member: obstacle_density
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "obstacle_density: ";
    rosidl_generator_traits::value_to_yaml(msg.obstacle_density, out);
    out << "\n";
  }

  // member: start_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.start_position.size() == 0) {
      out << "start_position: []\n";
    } else {
      out << "start_position:\n";
      for (auto item : msg.start_position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: goal_position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.goal_position.size() == 0) {
      out << "goal_position: []\n";
    } else {
      out << "goal_position:\n";
      for (auto item : msg.goal_position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        rosidl_generator_traits::value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const RaceParameters & msg, bool use_flow_style = false)
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
  const race_orchestrator::msg::RaceParameters & msg,
  std::ostream & out, size_t indentation = 0)
{
  race_orchestrator::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use race_orchestrator::msg::to_yaml() instead")]]
inline std::string to_yaml(const race_orchestrator::msg::RaceParameters & msg)
{
  return race_orchestrator::msg::to_yaml(msg);
}

template<>
inline const char * data_type<race_orchestrator::msg::RaceParameters>()
{
  return "race_orchestrator::msg::RaceParameters";
}

template<>
inline const char * name<race_orchestrator::msg::RaceParameters>()
{
  return "race_orchestrator/msg/RaceParameters";
}

template<>
struct has_fixed_size<race_orchestrator::msg::RaceParameters>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<race_orchestrator::msg::RaceParameters>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<race_orchestrator::msg::RaceParameters>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__TRAITS_HPP_
