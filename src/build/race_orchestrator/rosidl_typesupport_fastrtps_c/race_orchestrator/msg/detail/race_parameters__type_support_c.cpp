// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from race_orchestrator:msg/RaceParameters.idl
// generated code does not contain a copyright notice
#include "race_orchestrator/msg/detail/race_parameters__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "race_orchestrator/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "race_orchestrator/msg/detail/race_parameters__struct.h"
#include "race_orchestrator/msg/detail/race_parameters__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // checkpoints, goal_position, start_position
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // checkpoints, goal_position, start_position
#include "rosidl_runtime_c/string.h"  // object_sequence, race_id
#include "rosidl_runtime_c/string_functions.h"  // object_sequence, race_id

// forward declare type support functions


using _RaceParameters__ros_msg_type = race_orchestrator__msg__RaceParameters;

static bool _RaceParameters__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _RaceParameters__ros_msg_type * ros_message = static_cast<const _RaceParameters__ros_msg_type *>(untyped_ros_message);
  // Field name: race_id
  {
    const rosidl_runtime_c__String * str = &ros_message->race_id;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: object_sequence
  {
    size_t size = ros_message->object_sequence.size;
    auto array_ptr = ros_message->object_sequence.data;
    cdr << static_cast<uint32_t>(size);
    for (size_t i = 0; i < size; ++i) {
      const rosidl_runtime_c__String * str = &array_ptr[i];
      if (str->capacity == 0 || str->capacity <= str->size) {
        fprintf(stderr, "string capacity not greater than size\n");
        return false;
      }
      if (str->data[str->size] != '\0') {
        fprintf(stderr, "string not null-terminated\n");
        return false;
      }
      cdr << str->data;
    }
  }

  // Field name: time_limit
  {
    cdr << ros_message->time_limit;
  }

  // Field name: checkpoints
  {
    size_t size = ros_message->checkpoints.size;
    auto array_ptr = ros_message->checkpoints.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: enable_obstacles
  {
    cdr << (ros_message->enable_obstacles ? true : false);
  }

  // Field name: obstacle_density
  {
    cdr << ros_message->obstacle_density;
  }

  // Field name: start_position
  {
    size_t size = ros_message->start_position.size;
    auto array_ptr = ros_message->start_position.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: goal_position
  {
    size_t size = ros_message->goal_position.size;
    auto array_ptr = ros_message->goal_position.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _RaceParameters__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _RaceParameters__ros_msg_type * ros_message = static_cast<_RaceParameters__ros_msg_type *>(untyped_ros_message);
  // Field name: race_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->race_id.data) {
      rosidl_runtime_c__String__init(&ros_message->race_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->race_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'race_id'\n");
      return false;
    }
  }

  // Field name: object_sequence
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->object_sequence.data) {
      rosidl_runtime_c__String__Sequence__fini(&ros_message->object_sequence);
    }
    if (!rosidl_runtime_c__String__Sequence__init(&ros_message->object_sequence, size)) {
      fprintf(stderr, "failed to create array for field 'object_sequence'");
      return false;
    }
    auto array_ptr = ros_message->object_sequence.data;
    for (size_t i = 0; i < size; ++i) {
      std::string tmp;
      cdr >> tmp;
      auto & ros_i = array_ptr[i];
      if (!ros_i.data) {
        rosidl_runtime_c__String__init(&ros_i);
      }
      bool succeeded = rosidl_runtime_c__String__assign(
        &ros_i,
        tmp.c_str());
      if (!succeeded) {
        fprintf(stderr, "failed to assign string into field 'object_sequence'\n");
        return false;
      }
    }
  }

  // Field name: time_limit
  {
    cdr >> ros_message->time_limit;
  }

  // Field name: checkpoints
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->checkpoints.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->checkpoints);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->checkpoints, size)) {
      fprintf(stderr, "failed to create array for field 'checkpoints'");
      return false;
    }
    auto array_ptr = ros_message->checkpoints.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: enable_obstacles
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->enable_obstacles = tmp ? true : false;
  }

  // Field name: obstacle_density
  {
    cdr >> ros_message->obstacle_density;
  }

  // Field name: start_position
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->start_position.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->start_position);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->start_position, size)) {
      fprintf(stderr, "failed to create array for field 'start_position'");
      return false;
    }
    auto array_ptr = ros_message->start_position.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: goal_position
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->goal_position.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->goal_position);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->goal_position, size)) {
      fprintf(stderr, "failed to create array for field 'goal_position'");
      return false;
    }
    auto array_ptr = ros_message->goal_position.data;
    cdr.deserializeArray(array_ptr, size);
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_race_orchestrator
size_t get_serialized_size_race_orchestrator__msg__RaceParameters(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RaceParameters__ros_msg_type * ros_message = static_cast<const _RaceParameters__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name race_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->race_id.size + 1);
  // field.name object_sequence
  {
    size_t array_size = ros_message->object_sequence.size;
    auto array_ptr = ros_message->object_sequence.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        (array_ptr[index].size + 1);
    }
  }
  // field.name time_limit
  {
    size_t item_size = sizeof(ros_message->time_limit);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name checkpoints
  {
    size_t array_size = ros_message->checkpoints.size;
    auto array_ptr = ros_message->checkpoints.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name enable_obstacles
  {
    size_t item_size = sizeof(ros_message->enable_obstacles);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name obstacle_density
  {
    size_t item_size = sizeof(ros_message->obstacle_density);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name start_position
  {
    size_t array_size = ros_message->start_position.size;
    auto array_ptr = ros_message->start_position.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name goal_position
  {
    size_t array_size = ros_message->goal_position.size;
    auto array_ptr = ros_message->goal_position.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _RaceParameters__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_race_orchestrator__msg__RaceParameters(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_race_orchestrator
size_t max_serialized_size_race_orchestrator__msg__RaceParameters(
  bool & full_bounded,
  bool & is_plain,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  size_t last_member_size = 0;
  (void)last_member_size;
  (void)padding;
  (void)wchar_size;

  full_bounded = true;
  is_plain = true;

  // member: race_id
  {
    size_t array_size = 1;

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: object_sequence
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    full_bounded = false;
    is_plain = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: time_limit
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: checkpoints
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: enable_obstacles
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: obstacle_density
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: start_position
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: goal_position
  {
    size_t array_size = 0;
    full_bounded = false;
    is_plain = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = race_orchestrator__msg__RaceParameters;
    is_plain =
      (
      offsetof(DataType, goal_position) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _RaceParameters__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_race_orchestrator__msg__RaceParameters(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_RaceParameters = {
  "race_orchestrator::msg",
  "RaceParameters",
  _RaceParameters__cdr_serialize,
  _RaceParameters__cdr_deserialize,
  _RaceParameters__get_serialized_size,
  _RaceParameters__max_serialized_size
};

static rosidl_message_type_support_t _RaceParameters__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_RaceParameters,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, race_orchestrator, msg, RaceParameters)() {
  return &_RaceParameters__type_support;
}

#if defined(__cplusplus)
}
#endif
