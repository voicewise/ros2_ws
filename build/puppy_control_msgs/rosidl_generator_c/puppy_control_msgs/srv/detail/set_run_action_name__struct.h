// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from puppy_control_msgs:srv/SetRunActionName.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__STRUCT_H_
#define PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetRunActionName in the package puppy_control_msgs.
typedef struct puppy_control_msgs__srv__SetRunActionName_Request
{
  rosidl_runtime_c__String name;
  bool wait;
} puppy_control_msgs__srv__SetRunActionName_Request;

// Struct for a sequence of puppy_control_msgs__srv__SetRunActionName_Request.
typedef struct puppy_control_msgs__srv__SetRunActionName_Request__Sequence
{
  puppy_control_msgs__srv__SetRunActionName_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} puppy_control_msgs__srv__SetRunActionName_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/SetRunActionName in the package puppy_control_msgs.
typedef struct puppy_control_msgs__srv__SetRunActionName_Response
{
  bool success;
  rosidl_runtime_c__String message;
} puppy_control_msgs__srv__SetRunActionName_Response;

// Struct for a sequence of puppy_control_msgs__srv__SetRunActionName_Response.
typedef struct puppy_control_msgs__srv__SetRunActionName_Response__Sequence
{
  puppy_control_msgs__srv__SetRunActionName_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} puppy_control_msgs__srv__SetRunActionName_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__STRUCT_H_
