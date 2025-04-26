// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "race_orchestrator/msg/detail/race_status__rosidl_typesupport_introspection_c.h"
#include "race_orchestrator/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "race_orchestrator/msg/detail/race_status__functions.h"
#include "race_orchestrator/msg/detail/race_status__struct.h"


// Include directives for member types
// Member `race_id`
// Member `robot_id`
// Member `current_object`
// Member `failure_reason`
#include "rosidl_runtime_c/string_functions.h"
// Member `current_position`
// Member `next_checkpoint`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  race_orchestrator__msg__RaceStatus__init(message_memory);
}

void race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_fini_function(void * message_memory)
{
  race_orchestrator__msg__RaceStatus__fini(message_memory);
}

size_t race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__size_function__RaceStatus__current_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_const_function__RaceStatus__current_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_function__RaceStatus__current_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__fetch_function__RaceStatus__current_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_const_function__RaceStatus__current_position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__assign_function__RaceStatus__current_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_function__RaceStatus__current_position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__resize_function__RaceStatus__current_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__size_function__RaceStatus__next_checkpoint(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_const_function__RaceStatus__next_checkpoint(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_function__RaceStatus__next_checkpoint(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__fetch_function__RaceStatus__next_checkpoint(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_const_function__RaceStatus__next_checkpoint(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__assign_function__RaceStatus__next_checkpoint(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_function__RaceStatus__next_checkpoint(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__resize_function__RaceStatus__next_checkpoint(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_member_array[12] = {
  {
    "race_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, race_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "robot_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, robot_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, current_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "remaining_time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, remaining_time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_object",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, current_object),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "objects_collected",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, objects_collected),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "total_objects",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, total_objects),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "current_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, current_position),  // bytes offset in struct
    NULL,  // default value
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__size_function__RaceStatus__current_position,  // size() function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_const_function__RaceStatus__current_position,  // get_const(index) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_function__RaceStatus__current_position,  // get(index) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__fetch_function__RaceStatus__current_position,  // fetch(index, &value) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__assign_function__RaceStatus__current_position,  // assign(index, value) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__resize_function__RaceStatus__current_position  // resize(index) function pointer
  },
  {
    "next_checkpoint",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, next_checkpoint),  // bytes offset in struct
    NULL,  // default value
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__size_function__RaceStatus__next_checkpoint,  // size() function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_const_function__RaceStatus__next_checkpoint,  // get_const(index) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__get_function__RaceStatus__next_checkpoint,  // get(index) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__fetch_function__RaceStatus__next_checkpoint,  // fetch(index, &value) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__assign_function__RaceStatus__next_checkpoint,  // assign(index, value) function pointer
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__resize_function__RaceStatus__next_checkpoint  // resize(index) function pointer
  },
  {
    "race_completed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, race_completed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "race_failed",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, race_failed),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "failure_reason",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceStatus, failure_reason),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_members = {
  "race_orchestrator__msg",  // message namespace
  "RaceStatus",  // message name
  12,  // number of fields
  sizeof(race_orchestrator__msg__RaceStatus),
  race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_member_array,  // message members
  race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_init_function,  // function to initialize message memory (memory has to be allocated)
  race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_type_support_handle = {
  0,
  &race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_race_orchestrator
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, race_orchestrator, msg, RaceStatus)() {
  if (!race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_type_support_handle.typesupport_identifier) {
    race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &race_orchestrator__msg__RaceStatus__rosidl_typesupport_introspection_c__RaceStatus_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
