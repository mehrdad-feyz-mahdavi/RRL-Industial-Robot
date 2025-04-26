// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "race_orchestrator/msg/detail/race_parameters__rosidl_typesupport_introspection_c.h"
#include "race_orchestrator/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "race_orchestrator/msg/detail/race_parameters__functions.h"
#include "race_orchestrator/msg/detail/race_parameters__struct.h"


// Include directives for member types
// Member `race_id`
// Member `object_sequence`
#include "rosidl_runtime_c/string_functions.h"
// Member `checkpoints`
// Member `start_position`
// Member `goal_position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  race_orchestrator__msg__RaceParameters__init(message_memory);
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_fini_function(void * message_memory)
{
  race_orchestrator__msg__RaceParameters__fini(message_memory);
}

size_t race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__object_sequence(
  const void * untyped_member)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return member->size;
}

const void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__object_sequence(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__String__Sequence * member =
    (const rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__object_sequence(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  return &member->data[index];
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__object_sequence(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const rosidl_runtime_c__String * item =
    ((const rosidl_runtime_c__String *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__object_sequence(untyped_member, index));
  rosidl_runtime_c__String * value =
    (rosidl_runtime_c__String *)(untyped_value);
  *value = *item;
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__object_sequence(
  void * untyped_member, size_t index, const void * untyped_value)
{
  rosidl_runtime_c__String * item =
    ((rosidl_runtime_c__String *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__object_sequence(untyped_member, index));
  const rosidl_runtime_c__String * value =
    (const rosidl_runtime_c__String *)(untyped_value);
  *item = *value;
}

bool race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__object_sequence(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__String__Sequence * member =
    (rosidl_runtime_c__String__Sequence *)(untyped_member);
  rosidl_runtime_c__String__Sequence__fini(member);
  return rosidl_runtime_c__String__Sequence__init(member, size);
}

size_t race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__checkpoints(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__checkpoints(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__checkpoints(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__checkpoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__checkpoints(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__checkpoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__checkpoints(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__checkpoints(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__start_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__start_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__start_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__start_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__start_position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__start_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__start_position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__start_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

size_t race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__goal_position(
  const void * untyped_member)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return member->size;
}

const void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__goal_position(
  const void * untyped_member, size_t index)
{
  const rosidl_runtime_c__float__Sequence * member =
    (const rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void * race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__goal_position(
  void * untyped_member, size_t index)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  return &member->data[index];
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__goal_position(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const float * item =
    ((const float *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__goal_position(untyped_member, index));
  float * value =
    (float *)(untyped_value);
  *value = *item;
}

void race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__goal_position(
  void * untyped_member, size_t index, const void * untyped_value)
{
  float * item =
    ((float *)
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__goal_position(untyped_member, index));
  const float * value =
    (const float *)(untyped_value);
  *item = *value;
}

bool race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__goal_position(
  void * untyped_member, size_t size)
{
  rosidl_runtime_c__float__Sequence * member =
    (rosidl_runtime_c__float__Sequence *)(untyped_member);
  rosidl_runtime_c__float__Sequence__fini(member);
  return rosidl_runtime_c__float__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_member_array[8] = {
  {
    "race_id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, race_id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "object_sequence",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, object_sequence),  // bytes offset in struct
    NULL,  // default value
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__object_sequence,  // size() function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__object_sequence,  // get_const(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__object_sequence,  // get(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__object_sequence,  // fetch(index, &value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__object_sequence,  // assign(index, value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__object_sequence  // resize(index) function pointer
  },
  {
    "time_limit",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, time_limit),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "checkpoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, checkpoints),  // bytes offset in struct
    NULL,  // default value
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__checkpoints,  // size() function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__checkpoints,  // get_const(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__checkpoints,  // get(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__checkpoints,  // fetch(index, &value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__checkpoints,  // assign(index, value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__checkpoints  // resize(index) function pointer
  },
  {
    "enable_obstacles",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, enable_obstacles),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "obstacle_density",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, obstacle_density),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "start_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, start_position),  // bytes offset in struct
    NULL,  // default value
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__start_position,  // size() function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__start_position,  // get_const(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__start_position,  // get(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__start_position,  // fetch(index, &value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__start_position,  // assign(index, value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__start_position  // resize(index) function pointer
  },
  {
    "goal_position",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(race_orchestrator__msg__RaceParameters, goal_position),  // bytes offset in struct
    NULL,  // default value
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__size_function__RaceParameters__goal_position,  // size() function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_const_function__RaceParameters__goal_position,  // get_const(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__get_function__RaceParameters__goal_position,  // get(index) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__fetch_function__RaceParameters__goal_position,  // fetch(index, &value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__assign_function__RaceParameters__goal_position,  // assign(index, value) function pointer
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__resize_function__RaceParameters__goal_position  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_members = {
  "race_orchestrator__msg",  // message namespace
  "RaceParameters",  // message name
  8,  // number of fields
  sizeof(race_orchestrator__msg__RaceParameters),
  race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_member_array,  // message members
  race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_init_function,  // function to initialize message memory (memory has to be allocated)
  race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_type_support_handle = {
  0,
  &race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_race_orchestrator
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, race_orchestrator, msg, RaceParameters)() {
  if (!race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_type_support_handle.typesupport_identifier) {
    race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &race_orchestrator__msg__RaceParameters__rosidl_typesupport_introspection_c__RaceParameters_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
