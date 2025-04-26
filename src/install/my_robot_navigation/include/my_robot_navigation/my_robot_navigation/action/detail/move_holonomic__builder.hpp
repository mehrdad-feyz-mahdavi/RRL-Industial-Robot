// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from my_robot_navigation:action/MoveHolonomic.idl
// generated code does not contain a copyright notice

#ifndef MY_ROBOT_NAVIGATION__ACTION__DETAIL__MOVE_HOLONOMIC__BUILDER_HPP_
#define MY_ROBOT_NAVIGATION__ACTION__DETAIL__MOVE_HOLONOMIC__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "my_robot_navigation/action/detail/move_holonomic__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_Goal_max_velocity
{
public:
  explicit Init_MoveHolonomic_Goal_max_velocity(::my_robot_navigation::action::MoveHolonomic_Goal & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_Goal max_velocity(::my_robot_navigation::action::MoveHolonomic_Goal::_max_velocity_type arg)
  {
    msg_.max_velocity = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_Goal msg_;
};

class Init_MoveHolonomic_Goal_target_position
{
public:
  Init_MoveHolonomic_Goal_target_position()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_Goal_max_velocity target_position(::my_robot_navigation::action::MoveHolonomic_Goal::_target_position_type arg)
  {
    msg_.target_position = std::move(arg);
    return Init_MoveHolonomic_Goal_max_velocity(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_Goal msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_Goal>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_Goal_target_position();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_Result_message
{
public:
  explicit Init_MoveHolonomic_Result_message(::my_robot_navigation::action::MoveHolonomic_Result & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_Result message(::my_robot_navigation::action::MoveHolonomic_Result::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_Result msg_;
};

class Init_MoveHolonomic_Result_success
{
public:
  Init_MoveHolonomic_Result_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_Result_message success(::my_robot_navigation::action::MoveHolonomic_Result::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_MoveHolonomic_Result_message(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_Result msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_Result>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_Result_success();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_Feedback_current_pose
{
public:
  explicit Init_MoveHolonomic_Feedback_current_pose(::my_robot_navigation::action::MoveHolonomic_Feedback & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_Feedback current_pose(::my_robot_navigation::action::MoveHolonomic_Feedback::_current_pose_type arg)
  {
    msg_.current_pose = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_Feedback msg_;
};

class Init_MoveHolonomic_Feedback_distance_remaining
{
public:
  Init_MoveHolonomic_Feedback_distance_remaining()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_Feedback_current_pose distance_remaining(::my_robot_navigation::action::MoveHolonomic_Feedback::_distance_remaining_type arg)
  {
    msg_.distance_remaining = std::move(arg);
    return Init_MoveHolonomic_Feedback_current_pose(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_Feedback msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_Feedback>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_Feedback_distance_remaining();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_SendGoal_Request_goal
{
public:
  explicit Init_MoveHolonomic_SendGoal_Request_goal(::my_robot_navigation::action::MoveHolonomic_SendGoal_Request & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_SendGoal_Request goal(::my_robot_navigation::action::MoveHolonomic_SendGoal_Request::_goal_type arg)
  {
    msg_.goal = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_SendGoal_Request msg_;
};

class Init_MoveHolonomic_SendGoal_Request_goal_id
{
public:
  Init_MoveHolonomic_SendGoal_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_SendGoal_Request_goal goal_id(::my_robot_navigation::action::MoveHolonomic_SendGoal_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveHolonomic_SendGoal_Request_goal(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_SendGoal_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_SendGoal_Request>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_SendGoal_Request_goal_id();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_SendGoal_Response_stamp
{
public:
  explicit Init_MoveHolonomic_SendGoal_Response_stamp(::my_robot_navigation::action::MoveHolonomic_SendGoal_Response & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_SendGoal_Response stamp(::my_robot_navigation::action::MoveHolonomic_SendGoal_Response::_stamp_type arg)
  {
    msg_.stamp = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_SendGoal_Response msg_;
};

class Init_MoveHolonomic_SendGoal_Response_accepted
{
public:
  Init_MoveHolonomic_SendGoal_Response_accepted()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_SendGoal_Response_stamp accepted(::my_robot_navigation::action::MoveHolonomic_SendGoal_Response::_accepted_type arg)
  {
    msg_.accepted = std::move(arg);
    return Init_MoveHolonomic_SendGoal_Response_stamp(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_SendGoal_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_SendGoal_Response>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_SendGoal_Response_accepted();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_GetResult_Request_goal_id
{
public:
  Init_MoveHolonomic_GetResult_Request_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::my_robot_navigation::action::MoveHolonomic_GetResult_Request goal_id(::my_robot_navigation::action::MoveHolonomic_GetResult_Request::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_GetResult_Request msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_GetResult_Request>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_GetResult_Request_goal_id();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_GetResult_Response_result
{
public:
  explicit Init_MoveHolonomic_GetResult_Response_result(::my_robot_navigation::action::MoveHolonomic_GetResult_Response & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_GetResult_Response result(::my_robot_navigation::action::MoveHolonomic_GetResult_Response::_result_type arg)
  {
    msg_.result = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_GetResult_Response msg_;
};

class Init_MoveHolonomic_GetResult_Response_status
{
public:
  Init_MoveHolonomic_GetResult_Response_status()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_GetResult_Response_result status(::my_robot_navigation::action::MoveHolonomic_GetResult_Response::_status_type arg)
  {
    msg_.status = std::move(arg);
    return Init_MoveHolonomic_GetResult_Response_result(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_GetResult_Response msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_GetResult_Response>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_GetResult_Response_status();
}

}  // namespace my_robot_navigation


namespace my_robot_navigation
{

namespace action
{

namespace builder
{

class Init_MoveHolonomic_FeedbackMessage_feedback
{
public:
  explicit Init_MoveHolonomic_FeedbackMessage_feedback(::my_robot_navigation::action::MoveHolonomic_FeedbackMessage & msg)
  : msg_(msg)
  {}
  ::my_robot_navigation::action::MoveHolonomic_FeedbackMessage feedback(::my_robot_navigation::action::MoveHolonomic_FeedbackMessage::_feedback_type arg)
  {
    msg_.feedback = std::move(arg);
    return std::move(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_FeedbackMessage msg_;
};

class Init_MoveHolonomic_FeedbackMessage_goal_id
{
public:
  Init_MoveHolonomic_FeedbackMessage_goal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_MoveHolonomic_FeedbackMessage_feedback goal_id(::my_robot_navigation::action::MoveHolonomic_FeedbackMessage::_goal_id_type arg)
  {
    msg_.goal_id = std::move(arg);
    return Init_MoveHolonomic_FeedbackMessage_feedback(msg_);
  }

private:
  ::my_robot_navigation::action::MoveHolonomic_FeedbackMessage msg_;
};

}  // namespace builder

}  // namespace action

template<typename MessageType>
auto build();

template<>
inline
auto build<::my_robot_navigation::action::MoveHolonomic_FeedbackMessage>()
{
  return my_robot_navigation::action::builder::Init_MoveHolonomic_FeedbackMessage_goal_id();
}

}  // namespace my_robot_navigation

#endif  // MY_ROBOT_NAVIGATION__ACTION__DETAIL__MOVE_HOLONOMIC__BUILDER_HPP_
