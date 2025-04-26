// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_control_interfaces:msg/ArmCommand.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__STRUCT_HPP_
#define ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_control_interfaces__msg__ArmCommand __attribute__((deprecated))
#else
# define DEPRECATED__robot_control_interfaces__msg__ArmCommand __declspec(deprecated)
#endif

namespace robot_control_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ArmCommand_
{
  using Type = ArmCommand_<ContainerAllocator>;

  explicit ArmCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->joint_num = 0;
      this->angle = 0l;
      this->speed = 0;
    }
  }

  explicit ArmCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->joint_num = 0;
      this->angle = 0l;
      this->speed = 0;
    }
  }

  // field types and members
  using _joint_num_type =
    uint8_t;
  _joint_num_type joint_num;
  using _angle_type =
    int32_t;
  _angle_type angle;
  using _speed_type =
    uint8_t;
  _speed_type speed;

  // setters for named parameter idiom
  Type & set__joint_num(
    const uint8_t & _arg)
  {
    this->joint_num = _arg;
    return *this;
  }
  Type & set__angle(
    const int32_t & _arg)
  {
    this->angle = _arg;
    return *this;
  }
  Type & set__speed(
    const uint8_t & _arg)
  {
    this->speed = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_control_interfaces::msg::ArmCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_control_interfaces::msg::ArmCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_control_interfaces::msg::ArmCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_control_interfaces::msg::ArmCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_control_interfaces__msg__ArmCommand
    std::shared_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_control_interfaces__msg__ArmCommand
    std::shared_ptr<robot_control_interfaces::msg::ArmCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArmCommand_ & other) const
  {
    if (this->joint_num != other.joint_num) {
      return false;
    }
    if (this->angle != other.angle) {
      return false;
    }
    if (this->speed != other.speed) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArmCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArmCommand_

// alias to use template instance with default allocator
using ArmCommand =
  robot_control_interfaces::msg::ArmCommand_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace robot_control_interfaces

#endif  // ROBOT_CONTROL_INTERFACES__MSG__DETAIL__ARM_COMMAND__STRUCT_HPP_
