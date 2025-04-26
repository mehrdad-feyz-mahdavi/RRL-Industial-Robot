// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__BUILDER_HPP_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "race_orchestrator/msg/detail/race_status__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace race_orchestrator
{

namespace msg
{

namespace builder
{

class Init_RaceStatus_failure_reason
{
public:
  explicit Init_RaceStatus_failure_reason(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  ::race_orchestrator::msg::RaceStatus failure_reason(::race_orchestrator::msg::RaceStatus::_failure_reason_type arg)
  {
    msg_.failure_reason = std::move(arg);
    return std::move(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_race_failed
{
public:
  explicit Init_RaceStatus_race_failed(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_failure_reason race_failed(::race_orchestrator::msg::RaceStatus::_race_failed_type arg)
  {
    msg_.race_failed = std::move(arg);
    return Init_RaceStatus_failure_reason(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_race_completed
{
public:
  explicit Init_RaceStatus_race_completed(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_race_failed race_completed(::race_orchestrator::msg::RaceStatus::_race_completed_type arg)
  {
    msg_.race_completed = std::move(arg);
    return Init_RaceStatus_race_failed(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_next_checkpoint
{
public:
  explicit Init_RaceStatus_next_checkpoint(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_race_completed next_checkpoint(::race_orchestrator::msg::RaceStatus::_next_checkpoint_type arg)
  {
    msg_.next_checkpoint = std::move(arg);
    return Init_RaceStatus_race_completed(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_current_position
{
public:
  explicit Init_RaceStatus_current_position(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_next_checkpoint current_position(::race_orchestrator::msg::RaceStatus::_current_position_type arg)
  {
    msg_.current_position = std::move(arg);
    return Init_RaceStatus_next_checkpoint(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_total_objects
{
public:
  explicit Init_RaceStatus_total_objects(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_current_position total_objects(::race_orchestrator::msg::RaceStatus::_total_objects_type arg)
  {
    msg_.total_objects = std::move(arg);
    return Init_RaceStatus_current_position(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_objects_collected
{
public:
  explicit Init_RaceStatus_objects_collected(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_total_objects objects_collected(::race_orchestrator::msg::RaceStatus::_objects_collected_type arg)
  {
    msg_.objects_collected = std::move(arg);
    return Init_RaceStatus_total_objects(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_current_object
{
public:
  explicit Init_RaceStatus_current_object(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_objects_collected current_object(::race_orchestrator::msg::RaceStatus::_current_object_type arg)
  {
    msg_.current_object = std::move(arg);
    return Init_RaceStatus_objects_collected(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_remaining_time
{
public:
  explicit Init_RaceStatus_remaining_time(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_current_object remaining_time(::race_orchestrator::msg::RaceStatus::_remaining_time_type arg)
  {
    msg_.remaining_time = std::move(arg);
    return Init_RaceStatus_current_object(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_current_time
{
public:
  explicit Init_RaceStatus_current_time(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_remaining_time current_time(::race_orchestrator::msg::RaceStatus::_current_time_type arg)
  {
    msg_.current_time = std::move(arg);
    return Init_RaceStatus_remaining_time(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_robot_id
{
public:
  explicit Init_RaceStatus_robot_id(::race_orchestrator::msg::RaceStatus & msg)
  : msg_(msg)
  {}
  Init_RaceStatus_current_time robot_id(::race_orchestrator::msg::RaceStatus::_robot_id_type arg)
  {
    msg_.robot_id = std::move(arg);
    return Init_RaceStatus_current_time(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

class Init_RaceStatus_race_id
{
public:
  Init_RaceStatus_race_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_RaceStatus_robot_id race_id(::race_orchestrator::msg::RaceStatus::_race_id_type arg)
  {
    msg_.race_id = std::move(arg);
    return Init_RaceStatus_robot_id(msg_);
  }

private:
  ::race_orchestrator::msg::RaceStatus msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::race_orchestrator::msg::RaceStatus>()
{
  return race_orchestrator::msg::builder::Init_RaceStatus_race_id();
}

}  // namespace race_orchestrator

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__BUILDER_HPP_
