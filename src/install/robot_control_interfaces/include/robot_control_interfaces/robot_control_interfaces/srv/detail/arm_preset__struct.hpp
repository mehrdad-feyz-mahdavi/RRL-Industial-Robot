// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from robot_control_interfaces:srv/ArmPreset.idl
// generated code does not contain a copyright notice

#ifndef ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__STRUCT_HPP_
#define ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__robot_control_interfaces__srv__ArmPreset_Request __attribute__((deprecated))
#else
# define DEPRECATED__robot_control_interfaces__srv__ArmPreset_Request __declspec(deprecated)
#endif

namespace robot_control_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArmPreset_Request_
{
  using Type = ArmPreset_Request_<ContainerAllocator>;

  explicit ArmPreset_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->preset_num = 0;
    }
  }

  explicit ArmPreset_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->preset_num = 0;
    }
  }

  // field types and members
  using _preset_num_type =
    uint8_t;
  _preset_num_type preset_num;

  // setters for named parameter idiom
  Type & set__preset_num(
    const uint8_t & _arg)
  {
    this->preset_num = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_control_interfaces__srv__ArmPreset_Request
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_control_interfaces__srv__ArmPreset_Request
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArmPreset_Request_ & other) const
  {
    if (this->preset_num != other.preset_num) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArmPreset_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArmPreset_Request_

// alias to use template instance with default allocator
using ArmPreset_Request =
  robot_control_interfaces::srv::ArmPreset_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_control_interfaces


#ifndef _WIN32
# define DEPRECATED__robot_control_interfaces__srv__ArmPreset_Response __attribute__((deprecated))
#else
# define DEPRECATED__robot_control_interfaces__srv__ArmPreset_Response __declspec(deprecated)
#endif

namespace robot_control_interfaces
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct ArmPreset_Response_
{
  using Type = ArmPreset_Response_<ContainerAllocator>;

  explicit ArmPreset_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit ArmPreset_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__robot_control_interfaces__srv__ArmPreset_Response
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__robot_control_interfaces__srv__ArmPreset_Response
    std::shared_ptr<robot_control_interfaces::srv::ArmPreset_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ArmPreset_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const ArmPreset_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ArmPreset_Response_

// alias to use template instance with default allocator
using ArmPreset_Response =
  robot_control_interfaces::srv::ArmPreset_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace robot_control_interfaces

namespace robot_control_interfaces
{

namespace srv
{

struct ArmPreset
{
  using Request = robot_control_interfaces::srv::ArmPreset_Request;
  using Response = robot_control_interfaces::srv::ArmPreset_Response;
};

}  // namespace srv

}  // namespace robot_control_interfaces

#endif  // ROBOT_CONTROL_INTERFACES__SRV__DETAIL__ARM_PRESET__STRUCT_HPP_
