// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "race_orchestrator/msg/detail/race_parameters__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace race_orchestrator
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void RaceParameters_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) race_orchestrator::msg::RaceParameters(_init);
}

void RaceParameters_fini_function(void * message_memory)
{
  auto typed_message = static_cast<race_orchestrator::msg::RaceParameters *>(message_memory);
  typed_message->~RaceParameters();
}

size_t size_function__RaceParameters__object_sequence(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return member->size();
}

const void * get_const_function__RaceParameters__object_sequence(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void * get_function__RaceParameters__object_sequence(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<std::string> *>(untyped_member);
  return &member[index];
}

void fetch_function__RaceParameters__object_sequence(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const std::string *>(
    get_const_function__RaceParameters__object_sequence(untyped_member, index));
  auto & value = *reinterpret_cast<std::string *>(untyped_value);
  value = item;
}

void assign_function__RaceParameters__object_sequence(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<std::string *>(
    get_function__RaceParameters__object_sequence(untyped_member, index));
  const auto & value = *reinterpret_cast<const std::string *>(untyped_value);
  item = value;
}

void resize_function__RaceParameters__object_sequence(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<std::string> *>(untyped_member);
  member->resize(size);
}

size_t size_function__RaceParameters__checkpoints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__RaceParameters__checkpoints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__RaceParameters__checkpoints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__RaceParameters__checkpoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__RaceParameters__checkpoints(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__RaceParameters__checkpoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__RaceParameters__checkpoints(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__RaceParameters__checkpoints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__RaceParameters__start_position(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__RaceParameters__start_position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__RaceParameters__start_position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__RaceParameters__start_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__RaceParameters__start_position(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__RaceParameters__start_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__RaceParameters__start_position(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__RaceParameters__start_position(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

size_t size_function__RaceParameters__goal_position(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<float> *>(untyped_member);
  return member->size();
}

const void * get_const_function__RaceParameters__goal_position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<float> *>(untyped_member);
  return &member[index];
}

void * get_function__RaceParameters__goal_position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<float> *>(untyped_member);
  return &member[index];
}

void fetch_function__RaceParameters__goal_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const float *>(
    get_const_function__RaceParameters__goal_position(untyped_member, index));
  auto & value = *reinterpret_cast<float *>(untyped_value);
  value = item;
}

void assign_function__RaceParameters__goal_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<float *>(
    get_function__RaceParameters__goal_position(untyped_member, index));
  const auto & value = *reinterpret_cast<const float *>(untyped_value);
  item = value;
}

void resize_function__RaceParameters__goal_position(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<float> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember RaceParameters_message_member_array[8] = {
  {
    "race_id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, race_id),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "object_sequence",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, object_sequence),  // bytes offset in struct
    nullptr,  // default value
    size_function__RaceParameters__object_sequence,  // size() function pointer
    get_const_function__RaceParameters__object_sequence,  // get_const(index) function pointer
    get_function__RaceParameters__object_sequence,  // get(index) function pointer
    fetch_function__RaceParameters__object_sequence,  // fetch(index, &value) function pointer
    assign_function__RaceParameters__object_sequence,  // assign(index, value) function pointer
    resize_function__RaceParameters__object_sequence  // resize(index) function pointer
  },
  {
    "time_limit",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, time_limit),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "checkpoints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, checkpoints),  // bytes offset in struct
    nullptr,  // default value
    size_function__RaceParameters__checkpoints,  // size() function pointer
    get_const_function__RaceParameters__checkpoints,  // get_const(index) function pointer
    get_function__RaceParameters__checkpoints,  // get(index) function pointer
    fetch_function__RaceParameters__checkpoints,  // fetch(index, &value) function pointer
    assign_function__RaceParameters__checkpoints,  // assign(index, value) function pointer
    resize_function__RaceParameters__checkpoints  // resize(index) function pointer
  },
  {
    "enable_obstacles",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, enable_obstacles),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "obstacle_density",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, obstacle_density),  // bytes offset in struct
    nullptr,  // default value
    nullptr,  // size() function pointer
    nullptr,  // get_const(index) function pointer
    nullptr,  // get(index) function pointer
    nullptr,  // fetch(index, &value) function pointer
    nullptr,  // assign(index, value) function pointer
    nullptr  // resize(index) function pointer
  },
  {
    "start_position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, start_position),  // bytes offset in struct
    nullptr,  // default value
    size_function__RaceParameters__start_position,  // size() function pointer
    get_const_function__RaceParameters__start_position,  // get_const(index) function pointer
    get_function__RaceParameters__start_position,  // get(index) function pointer
    fetch_function__RaceParameters__start_position,  // fetch(index, &value) function pointer
    assign_function__RaceParameters__start_position,  // assign(index, value) function pointer
    resize_function__RaceParameters__start_position  // resize(index) function pointer
  },
  {
    "goal_position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator::msg::RaceParameters, goal_position),  // bytes offset in struct
    nullptr,  // default value
    size_function__RaceParameters__goal_position,  // size() function pointer
    get_const_function__RaceParameters__goal_position,  // get_const(index) function pointer
    get_function__RaceParameters__goal_position,  // get(index) function pointer
    fetch_function__RaceParameters__goal_position,  // fetch(index, &value) function pointer
    assign_function__RaceParameters__goal_position,  // assign(index, value) function pointer
    resize_function__RaceParameters__goal_position  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers RaceParameters_message_members = {
  "race_orchestrator::msg",  // message namespace
  "RaceParameters",  // message name
  8,  // number of fields
  sizeof(race_orchestrator::msg::RaceParameters),
  RaceParameters_message_member_array,  // message members
  RaceParameters_init_function,  // function to initialize message memory (memory has to be allocated)
  RaceParameters_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t RaceParameters_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &RaceParameters_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace race_orchestrator


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<race_orchestrator::msg::RaceParameters>()
{
  return &::race_orchestrator::msg::rosidl_typesupport_introspection_cpp::RaceParameters_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, race_orchestrator, msg, RaceParameters)() {
  return &::race_orchestrator::msg::rosidl_typesupport_introspection_cpp::RaceParameters_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
