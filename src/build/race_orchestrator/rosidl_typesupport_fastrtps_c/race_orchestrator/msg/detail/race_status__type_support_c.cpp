// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice
#include "race_orchestrator/msg/detail/race_status__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "race_orchestrator/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "race_orchestrator/msg/detail/race_status__struct.h"
#include "race_orchestrator/msg/detail/race_status__functions.h"
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

#include "rosidl_runtime_c/primitives_sequence.h"  // current_position, next_checkpoint
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // current_position, next_checkpoint
#include "rosidl_runtime_c/string.h"  // current_object, failure_reason, race_id, robot_id
#include "rosidl_runtime_c/string_functions.h"  // current_object, failure_reason, race_id, robot_id

// forward declare type support functions


using _RaceStatus__ros_msg_type = race_orchestrator__msg__RaceStatus;

static bool _RaceStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _RaceStatus__ros_msg_type * ros_message = static_cast<const _RaceStatus__ros_msg_type *>(untyped_ros_message);
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

  // Field name: robot_id
  {
    const rosidl_runtime_c__String * str = &ros_message->robot_id;
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

  // Field name: current_time
  {
    cdr << ros_message->current_time;
  }

  // Field name: remaining_time
  {
    cdr << ros_message->remaining_time;
  }

  // Field name: current_object
  {
    const rosidl_runtime_c__String * str = &ros_message->current_object;
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

  // Field name: objects_collected
  {
    cdr << ros_message->objects_collected;
  }

  // Field name: total_objects
  {
    cdr << ros_message->total_objects;
  }

  // Field name: current_position
  {
    size_t size = ros_message->current_position.size;
    auto array_ptr = ros_message->current_position.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: next_checkpoint
  {
    size_t size = ros_message->next_checkpoint.size;
    auto array_ptr = ros_message->next_checkpoint.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: race_completed
  {
    cdr << (ros_message->race_completed ? true : false);
  }

  // Field name: race_failed
  {
    cdr << (ros_message->race_failed ? true : false);
  }

  // Field name: failure_reason
  {
    const rosidl_runtime_c__String * str = &ros_message->failure_reason;
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

  return true;
}

static bool _RaceStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _RaceStatus__ros_msg_type * ros_message = static_cast<_RaceStatus__ros_msg_type *>(untyped_ros_message);
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

  // Field name: robot_id
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->robot_id.data) {
      rosidl_runtime_c__String__init(&ros_message->robot_id);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->robot_id,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'robot_id'\n");
      return false;
    }
  }

  // Field name: current_time
  {
    cdr >> ros_message->current_time;
  }

  // Field name: remaining_time
  {
    cdr >> ros_message->remaining_time;
  }

  // Field name: current_object
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->current_object.data) {
      rosidl_runtime_c__String__init(&ros_message->current_object);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->current_object,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'current_object'\n");
      return false;
    }
  }

  // Field name: objects_collected
  {
    cdr >> ros_message->objects_collected;
  }

  // Field name: total_objects
  {
    cdr >> ros_message->total_objects;
  }

  // Field name: current_position
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->current_position.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->current_position);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->current_position, size)) {
      fprintf(stderr, "failed to create array for field 'current_position'");
      return false;
    }
    auto array_ptr = ros_message->current_position.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: next_checkpoint
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->next_checkpoint.data) {
      rosidl_runtime_c__float__Sequence__fini(&ros_message->next_checkpoint);
    }
    if (!rosidl_runtime_c__float__Sequence__init(&ros_message->next_checkpoint, size)) {
      fprintf(stderr, "failed to create array for field 'next_checkpoint'");
      return false;
    }
    auto array_ptr = ros_message->next_checkpoint.data;
    cdr.deserializeArray(array_ptr, size);
  }

  // Field name: race_completed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->race_completed = tmp ? true : false;
  }

  // Field name: race_failed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->race_failed = tmp ? true : false;
  }

  // Field name: failure_reason
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->failure_reason.data) {
      rosidl_runtime_c__String__init(&ros_message->failure_reason);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->failure_reason,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'failure_reason'\n");
      return false;
    }
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_race_orchestrator
size_t get_serialized_size_race_orchestrator__msg__RaceStatus(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _RaceStatus__ros_msg_type * ros_message = static_cast<const _RaceStatus__ros_msg_type *>(untyped_ros_message);
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
  // field.name robot_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->robot_id.size + 1);
  // field.name current_time
  {
    size_t item_size = sizeof(ros_message->current_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name remaining_time
  {
    size_t item_size = sizeof(ros_message->remaining_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name current_object
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->current_object.size + 1);
  // field.name objects_collected
  {
    size_t item_size = sizeof(ros_message->objects_collected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name total_objects
  {
    size_t item_size = sizeof(ros_message->total_objects);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name current_position
  {
    size_t array_size = ros_message->current_position.size;
    auto array_ptr = ros_message->current_position.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name next_checkpoint
  {
    size_t array_size = ros_message->next_checkpoint.size;
    auto array_ptr = ros_message->next_checkpoint.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name race_completed
  {
    size_t item_size = sizeof(ros_message->race_completed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name race_failed
  {
    size_t item_size = sizeof(ros_message->race_failed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name failure_reason
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->failure_reason.size + 1);

  return current_alignment - initial_alignment;
}

static uint32_t _RaceStatus__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_race_orchestrator__msg__RaceStatus(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_race_orchestrator
size_t max_serialized_size_race_orchestrator__msg__RaceStatus(
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
  // member: robot_id
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
  // member: current_time
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: remaining_time
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: current_object
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
  // member: objects_collected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: total_objects
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }
  // member: current_position
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
  // member: next_checkpoint
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
  // member: race_completed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: race_failed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: failure_reason
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

  size_t ret_val = current_alignment - initial_alignment;
  if (is_plain) {
    // All members are plain, and type is not empty.
    // We still need to check that the in-memory alignment
    // is the same as the CDR mandated alignment.
    using DataType = race_orchestrator__msg__RaceStatus;
    is_plain =
      (
      offsetof(DataType, failure_reason) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static size_t _RaceStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_race_orchestrator__msg__RaceStatus(
    full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}


static message_type_support_callbacks_t __callbacks_RaceStatus = {
  "race_orchestrator::msg",
  "RaceStatus",
  _RaceStatus__cdr_serialize,
  _RaceStatus__cdr_deserialize,
  _RaceStatus__get_serialized_size,
  _RaceStatus__max_serialized_size
};

static rosidl_message_type_support_t _RaceStatus__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_RaceStatus,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, race_orchestrator, msg, RaceStatus)() {
  return &_RaceStatus__type_support;
}

#if defined(__cplusplus)
}
#endif
