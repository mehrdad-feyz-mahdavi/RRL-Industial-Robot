// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__BUILDER_HPP_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "race_orchestrator/msg/detail/race_parameters__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace race_orchestrator
{

namespace msg
{

namespace builder
{

class Init_RaceParameters_goal_position
{
public:
  explicit Init_RaceParameters_goal_position(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  ::race_orchestrator::msg::RaceParameters goal_position(::race_orchestrator::msg::RaceParameters::_goal_position_type arg)
  {
    msg_.goal_position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_start_position
{
public:
  explicit Init_RaceParameters_start_position(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  Init_RaceParameters_goal_position start_position(::race_orchestrator::msg::RaceParameters::_start_position_type arg)
  {
    msg_.start_position = std::move(arg);
    return Init_RaceParameters_goal_position(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_obstacle_density
{
public:
  explicit Init_RaceParameters_obstacle_density(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  Init_RaceParameters_start_position obstacle_density(::race_orchestrator::msg::RaceParameters::_obstacle_density_type arg)
  {
    msg_.obstacle_density = std::move(arg);
    return Init_RaceParameters_start_position(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_enable_obstacles
{
public:
  explicit Init_RaceParameters_enable_obstacles(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  Init_RaceParameters_obstacle_density enable_obstacles(::race_orchestrator::msg::RaceParameters::_enable_obstacles_type arg)
  {
    msg_.enable_obstacles = std::move(arg);
    return Init_RaceParameters_obstacle_density(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_checkpoints
{
public:
  explicit Init_RaceParameters_checkpoints(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  Init_RaceParameters_enable_obstacles checkpoints(::race_orchestrator::msg::RaceParameters::_checkpoints_type arg)
  {
    msg_.checkpoints = std::move(arg);
    return Init_RaceParameters_enable_obstacles(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_time_limit
{
public:
  explicit Init_RaceParameters_time_limit(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  Init_RaceParameters_checkpoints time_limit(::race_orchestrator::msg::RaceParameters::_time_limit_type arg)
  {
    msg_.time_limit = std::move(arg);
    return Init_RaceParameters_checkpoints(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_object_sequence
{
public:
  explicit Init_RaceParameters_object_sequence(::race_orchestrator::msg::RaceParameters & msg)
  : msg_(msg)
  {}
  Init_RaceParameters_time_limit object_sequence(::race_orchestrator::msg::RaceParameters::_object_sequence_type arg)
  {
    msg_.object_sequence = std::move(arg);
    return Init_RaceParameters_time_limit(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

class Init_RaceParameters_race_id
{
public:
  Init_RaceParameters_race_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RaceParameters_object_sequence race_id(::race_orchestrator::msg::RaceParameters::_race_id_type arg)
  {
    msg_.race_id = std::move(arg);
    return Init_RaceParameters_object_sequence(msg_);
  }

private:
  ::race_orchestrator::msg::RaceParameters msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::race_orchestrator::msg::RaceParameters>()
{
  return race_orchestrator::msg::builder::Init_RaceParameters_race_id();
}

}  // namespace race_orchestrator

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__BUILDER_HPP_
