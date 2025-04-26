// generated from rosidl_generator_cpp/resource/rosidl_generator_cpp__visibility_control.hpp.in
// generated code does not contain a copyright notice

#ifndef MOVEIT_TASK_CONSTRUCTOR_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
#define MOVEIT_TASK_CONSTRUCTOR_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_GENERATOR_CPP_EXPORT_moveit_task_constructor_msgs __attribute__ ((dllexport))
    #define ROSIDL_GENERATOR_CPP_IMPORT_moveit_task_constructor_msgs __attribute__ ((dllimport))
  #else
    #define ROSIDL_GENERATOR_CPP_EXPORT_moveit_task_constructor_msgs __declspec(dllexport)
    #define ROSIDL_GENERATOR_CPP_IMPORT_moveit_task_constructor_msgs __declspec(dllimport)
  #endif
  #ifdef ROSIDL_GENERATOR_CPP_BUILDING_DLL_moveit_task_constructor_msgs
    #define ROSIDL_GENERATOR_CPP_PUBLIC_moveit_task_constructor_msgs ROSIDL_GENERATOR_CPP_EXPORT_moveit_task_constructor_msgs
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_moveit_task_constructor_msgs ROSIDL_GENERATOR_CPP_IMPORT_moveit_task_constructor_msgs
  #endif
#else
  #define ROSIDL_GENERATOR_CPP_EXPORT_moveit_task_constructor_msgs __attribute__ ((visibility("default")))
  #define ROSIDL_GENERATOR_CPP_IMPORT_moveit_task_constructor_msgs
  #if __GNUC__ >= 4
    #define ROSIDL_GENERATOR_CPP_PUBLIC_moveit_task_constructor_msgs __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_GENERATOR_CPP_PUBLIC_moveit_task_constructor_msgs
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // MOVEIT_TASK_CONSTRUCTOR_MSGS__MSG__ROSIDL_GENERATOR_CPP__VISIBILITY_CONTROL_HPP_
