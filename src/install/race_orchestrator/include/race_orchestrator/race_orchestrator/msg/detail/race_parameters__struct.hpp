// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice

#ifndef RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__STRUCT_HPP_
#define RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__race_orchestrator__msg__RaceParameters __attribute__((deprecated))
#else
# define DEPRECATED__race_orchestrator__msg__RaceParameters __declspec(deprecated)
#endif

namespace race_orchestrator
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct RaceParameters_
{
  using Type = RaceParameters_<ContainerAllocator>;

  explicit RaceParameters_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->race_id = "";
      this->time_limit = 0.0f;
      this->enable_obstacles = false;
      this->obstacle_density = 0.0f;
    }
  }

  explicit RaceParameters_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : race_id(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->race_id = "";
      this->time_limit = 0.0f;
      this->enable_obstacles = false;
      this->obstacle_density = 0.0f;
    }
  }

  // field types and members
  using _race_id_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _race_id_type race_id;
  using _object_sequence_type =
    std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>>;
  _object_sequence_type object_sequence;
  using _time_limit_type =
    float;
  _time_limit_type time_limit;
  using _checkpoints_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _checkpoints_type checkpoints;
  using _enable_obstacles_type =
    bool;
  _enable_obstacles_type enable_obstacles;
  using _obstacle_density_type =
    float;
  _obstacle_density_type obstacle_density;
  using _start_position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _start_position_type start_position;
  using _goal_position_type =
    std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>>;
  _goal_position_type goal_position;

  // setters for named parameter idiom
  Type & set__race_id(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->race_id = _arg;
    return *this;
  }
  Type & set__object_sequence(
    const std::vector<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>>> & _arg)
  {
    this->object_sequence = _arg;
    return *this;
  }
  Type & set__time_limit(
    const float & _arg)
  {
    this->time_limit = _arg;
    return *this;
  }
  Type & set__checkpoints(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->checkpoints = _arg;
    return *this;
  }
  Type & set__enable_obstacles(
    const bool & _arg)
  {
    this->enable_obstacles = _arg;
    return *this;
  }
  Type & set__obstacle_density(
    const float & _arg)
  {
    this->obstacle_density = _arg;
    return *this;
  }
  Type & set__start_position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->start_position = _arg;
    return *this;
  }
  Type & set__goal_position(
    const std::vector<float, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<float>> & _arg)
  {
    this->goal_position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    race_orchestrator::msg::RaceParameters_<ContainerAllocator> *;
  using ConstRawPtr =
    const race_orchestrator::msg::RaceParameters_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      race_orchestrator::msg::RaceParameters_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      race_orchestrator::msg::RaceParameters_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__race_orchestrator__msg__RaceParameters
    std::shared_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__race_orchestrator__msg__RaceParameters
    std::shared_ptr<race_orchestrator::msg::RaceParameters_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const RaceParameters_ & other) const
  {
    if (this->race_id != other.race_id) {
      return false;
    }
    if (this->object_sequence != other.object_sequence) {
      return false;
    }
    if (this->time_limit != other.time_limit) {
      return false;
    }
    if (this->checkpoints != other.checkpoints) {
      return false;
    }
    if (this->enable_obstacles != other.enable_obstacles) {
      return false;
    }
    if (this->obstacle_density != other.obstacle_density) {
      return false;
    }
    if (this->start_position != other.start_position) {
      return false;
    }
    if (this->goal_position != other.goal_position) {
      return false;
    }
    return true;
  }
  bool operator!=(const RaceParameters_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct RaceParameters_

// alias to use template instance with default allocator
using RaceParameters =
  race_orchestrator::msg::RaceParameters_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace race_orchestrator

#endif  // RACE_ORCHESTRATOR__MSG__DETAIL__RACE_PARAMETERS__STRUCT_HPP_
