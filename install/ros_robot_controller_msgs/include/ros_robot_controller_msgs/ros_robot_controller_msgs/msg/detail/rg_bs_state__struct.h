// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from ros_robot_controller_msgs:msg/RGBsState.idl
// generated code does not contain a copyright notice

#ifndef ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__RG_BS_STATE__STRUCT_H_
#define ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__RG_BS_STATE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'data'
#include "ros_robot_controller_msgs/msg/detail/rgb_state__struct.h"

/// Struct defined in msg/RGBsState in the package ros_robot_controller_msgs.
typedef struct ros_robot_controller_msgs__msg__RGBsState
{
  ros_robot_controller_msgs__msg__RGBState__Sequence data;
} ros_robot_controller_msgs__msg__RGBsState;

// Struct for a sequence of ros_robot_controller_msgs__msg__RGBsState.
typedef struct ros_robot_controller_msgs__msg__RGBsState__Sequence
{
  ros_robot_controller_msgs__msg__RGBsState * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} ros_robot_controller_msgs__msg__RGBsState__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // ROS_ROBOT_CONTROLLER_MSGS__MSG__DETAIL__RG_BS_STATE__STRUCT_H_
