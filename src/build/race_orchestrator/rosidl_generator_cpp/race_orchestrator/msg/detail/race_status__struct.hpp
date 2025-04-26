// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__STRUCT_HPP_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__race_orchestrator__msg__RaceStatus __attribute__((deprecated))
#else
# define DEPRECATED__race_orchestrator__msg__RaceStatus __declspec(deprecated)
#endif

namespace race_orchestrator
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RaceStatus_
{
  using Type = RaceStatus_<ContainerAllocator>;

  explicit RaceStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->race_id = "";
      this->robot_id = "";
      this->current_time = 0.0f;
      this->remaining_time = 0.0f;
      this->current_object = "";
      this->objects_collected = 0l;
      this->total_objects = 0l;
      this->race_completed = false;
      this->race_failed = false;
      this->failure_reason = "";
    }
  }

  explicit RaceStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : race_id(_alloc),
    robot_id(_alloc),
    current_object(_alloc),
    failure_reason(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->race_id = "";
      this->robot_id = "";
      this->current_time = 0.0f;
      this->remaining_time = 0.0f;
      this->current_object = "";
      this->objects_collected = 0l;
      this->total_objects = 0l;
      this->race_completed = false;
      this->race_failed = false;
      this->failure_reason = "";
    }
  }

  // field types and members
  using _race_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _race_id_type race_id;
  using _robot_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _robot_id_type robot_id;
  using _current_time_type =
    float;
  _current_time_type current_time;
  using _remaining_time_type =
    float;
  _remaining_time_type remaining_time;
  using _current_object_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _current_object_type current_object;
  using _objects_collected_type =
    int32_t;
  _objects_collected_type objects_collected;
  using _total_objects_type =
    int32_t;
  _total_objects_type total_objects;
  using _current_position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _current_position_type current_position;
  using _next_checkpoint_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _next_checkpoint_type next_checkpoint;
  using _race_completed_type =
    bool;
  _race_completed_type race_completed;
  using _race_failed_type =
    bool;
  _race_failed_type race_failed;
  using _failure_reason_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _failure_reason_type failure_reason;

  // setters for named parameter idiom
  Type & set__race_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->race_id = _arg;
    return *this;
  }
  Type & set__robot_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->robot_id = _arg;
    return *this;
  }
  Type & set__current_time(
    const float & _arg)
  {
    this->current_time = _arg;
    return *this;
  }
  Type & set__remaining_time(
    const float & _arg)
  {
    this->remaining_time = _arg;
    return *this;
  }
  Type & set__current_object(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->current_object = _arg;
    return *this;
  }
  Type & set__objects_collected(
    const int32_t & _arg)
  {
    this->objects_collected = _arg;
    return *this;
  }
  Type & set__total_objects(
    const int32_t & _arg)
  {
    this->total_objects = _arg;
    return *this;
  }
  Type & set__current_position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->current_position = _arg;
    return *this;
  }
  Type & set__next_checkpoint(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->next_checkpoint = _arg;
    return *this;
  }
  Type & set__race_completed(
    const bool & _arg)
  {
    this->race_completed = _arg;
    return *this;
  }
  Type & set__race_failed(
    const bool & _arg)
  {
    this->race_failed = _arg;
    return *this;
  }
  Type & set__failure_reason(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->failure_reason = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    race_orchestrator::msg::RaceStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const race_orchestrator::msg::RaceStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      race_orchestrator::msg::RaceStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      race_orchestrator::msg::RaceStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__race_orchestrator__msg__RaceStatus
    std::shared_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__race_orchestrator__msg__RaceStatus
    std::shared_ptr<race_orchestrator::msg::RaceStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RaceStatus_ & other) const
  {
    if (this->race_id != other.race_id) {
      return false;
    }
    if (this->robot_id != other.robot_id) {
      return false;
    }
    if (this->current_time != other.current_time) {
      return false;
    }
    if (this->remaining_time != other.remaining_time) {
      return false;
    }
    if (this->current_object != other.current_object) {
      return false;
    }
    if (this->objects_collected != other.objects_collected) {
      return false;
    }
    if (this->total_objects != other.total_objects) {
      return false;
    }
    if (this->current_position != other.current_position) {
      return false;
    }
    if (this->next_checkpoint != other.next_checkpoint) {
      return false;
    }
    if (this->race_completed != other.race_completed) {
      return false;
    }
    if (this->race_failed != other.race_failed) {
      return false;
    }
    if (this->failure_reason != other.failure_reason) {
      return false;
    }
    return true;
  }
  bool operator!=(const RaceStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RaceStatus_

// alias to use template instance with default allocator
using RaceStatus =
  race_orchestrator::msg::RaceStatus_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace race_orchestrator

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_STATUS__STRUCT_HPP_
