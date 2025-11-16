// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from puppy_control_msgs:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__STRUCT_H_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Struct defined in msg/Pose in the package puppy_control_msgs.
typedef struct puppy_control_msgs__msg__Pose
{
  float roll;
  float pitch;
  float yaw;
  float height;
  float x_shift;
  float stance_x;
  float stance_y;
  int32_t run_time;
} puppy_control_msgs__msg__Pose;

// Struct for a sequence of puppy_control_msgs__msg__Pose.
typedef struct puppy_control_msgs__msg__Pose__Sequence
{
  puppy_control_msgs__msg__Pose * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} puppy_control_msgs__msg__Pose__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__STRUCT_H_
