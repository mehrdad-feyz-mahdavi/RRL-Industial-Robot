// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from race_orchestrator:msg/RaceStatus.idl
// generated code does not contain a copyright notice
#include "race_orchestrator/msg/detail/race_status__rosidl_typesupport_fastrtps_cpp.hpp"
#include "race_orchestrator/msg/detail/race_status__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions

namespace race_orchestrator
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_race_orchestrator
cdr_serialize(
  const race_orchestrator::msg::RaceStatus & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: race_id
  cdr << ros_message.race_id;
  // Member: robot_id
  cdr << ros_message.robot_id;
  // Member: current_time
  cdr << ros_message.current_time;
  // Member: remaining_time
  cdr << ros_message.remaining_time;
  // Member: current_object
  cdr << ros_message.current_object;
  // Member: objects_collected
  cdr << ros_message.objects_collected;
  // Member: total_objects
  cdr << ros_message.total_objects;
  // Member: current_position
  {
    cdr << ros_message.current_position;
  }
  // Member: next_checkpoint
  {
    cdr << ros_message.next_checkpoint;
  }
  // Member: race_completed
  cdr << (ros_message.race_completed ? true : false);
  // Member: race_failed
  cdr << (ros_message.race_failed ? true : false);
  // Member: failure_reason
  cdr << ros_message.failure_reason;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_race_orchestrator
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  race_orchestrator::msg::RaceStatus & ros_message)
{
  // Member: race_id
  cdr >> ros_message.race_id;

  // Member: robot_id
  cdr >> ros_message.robot_id;

  // Member: current_time
  cdr >> ros_message.current_time;

  // Member: remaining_time
  cdr >> ros_message.remaining_time;

  // Member: current_object
  cdr >> ros_message.current_object;

  // Member: objects_collected
  cdr >> ros_message.objects_collected;

  // Member: total_objects
  cdr >> ros_message.total_objects;

  // Member: current_position
  {
    cdr >> ros_message.current_position;
  }

  // Member: next_checkpoint
  {
    cdr >> ros_message.next_checkpoint;
  }

  // Member: race_completed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.race_completed = tmp ? true : false;
  }

  // Member: race_failed
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.race_failed = tmp ? true : false;
  }

  // Member: failure_reason
  cdr >> ros_message.failure_reason;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_race_orchestrator
get_serialized_size(
  const race_orchestrator::msg::RaceStatus & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: race_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.race_id.size() + 1);
  // Member: robot_id
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.robot_id.size() + 1);
  // Member: current_time
  {
    size_t item_size = sizeof(ros_message.current_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: remaining_time
  {
    size_t item_size = sizeof(ros_message.remaining_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: current_object
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.current_object.size() + 1);
  // Member: objects_collected
  {
    size_t item_size = sizeof(ros_message.objects_collected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: total_objects
  {
    size_t item_size = sizeof(ros_message.total_objects);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: current_position
  {
    size_t array_size = ros_message.current_position.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.current_position[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: next_checkpoint
  {
    size_t array_size = ros_message.next_checkpoint.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.next_checkpoint[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: race_completed
  {
    size_t item_size = sizeof(ros_message.race_completed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: race_failed
  {
    size_t item_size = sizeof(ros_message.race_failed);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: failure_reason
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.failure_reason.size() + 1);

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_race_orchestrator
max_serialized_size_RaceStatus(
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


  // Member: race_id
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

  // Member: robot_id
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

  // Member: current_time
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: remaining_time
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: current_object
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

  // Member: objects_collected
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: total_objects
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint32_t);
    current_alignment += array_size * sizeof(uint32_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint32_t));
  }

  // Member: current_position
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

  // Member: next_checkpoint
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

  // Member: race_completed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: race_failed
  {
    size_t array_size = 1;

    last_member_size = array_size * sizeof(uint8_t);
    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: failure_reason
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
    using DataType = race_orchestrator::msg::RaceStatus;
    is_plain =
      (
      offsetof(DataType, failure_reason) +
      last_member_size
      ) == ret_val;
  }

  return ret_val;
}

static bool _RaceStatus__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const race_orchestrator::msg::RaceStatus *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _RaceStatus__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<race_orchestrator::msg::RaceStatus *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _RaceStatus__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const race_orchestrator::msg::RaceStatus *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _RaceStatus__max_serialized_size(char & bounds_info)
{
  bool full_bounded;
  bool is_plain;
  size_t ret_val;

  ret_val = max_serialized_size_RaceStatus(full_bounded, is_plain, 0);

  bounds_info =
    is_plain ? ROSIDL_TYPESUPPORT_FASTRTPS_PLAIN_TYPE :
    full_bounded ? ROSIDL_TYPESUPPORT_FASTRTPS_BOUNDED_TYPE : ROSIDL_TYPESUPPORT_FASTRTPS_UNBOUNDED_TYPE;
  return ret_val;
}

static message_type_support_callbacks_t _RaceStatus__callbacks = {
  "race_orchestrator::msg",
  "RaceStatus",
  _RaceStatus__cdr_serialize,
  _RaceStatus__cdr_deserialize,
  _RaceStatus__get_serialized_size,
  _RaceStatus__max_serialized_size
};

static rosidl_message_type_support_t _RaceStatus__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_RaceStatus__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace race_orchestrator

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_race_orchestrator
const rosidl_message_type_support_t *
get_message_type_support_handle<race_orchestrator::msg::RaceStatus>()
{
  return &race_orchestrator::msg::typesupport_fastrtps_cpp::_RaceStatus__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, race_orchestrator, msg, RaceStatus)() {
  return &race_orchestrator::msg::typesupport_fastrtps_cpp::_RaceStatus__handle;
}

#ifdef __cplusplus
}
#endif
