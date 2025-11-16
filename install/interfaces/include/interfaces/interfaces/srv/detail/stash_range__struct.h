// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from interfaces:srv/StashRange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__STASH_RANGE__STRUCT_H_
#define INTERFACES__SRV__DETAIL__STASH_RANGE__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'color_name'
#include "rosidl_runtime_c/string.h"

/// Struct defined in srv/StashRange in the package interfaces.
typedef struct interfaces__srv__StashRange_Request
{
  rosidl_runtime_c__String color_name;
} interfaces__srv__StashRange_Request;

// Struct for a sequence of interfaces__srv__StashRange_Request.
typedef struct interfaces__srv__StashRange_Request__Sequence
{
  interfaces__srv__StashRange_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__srv__StashRange_Request__Sequence;


// Constants defined in the message

// Include directives for member types
// Member 'message'
// already included above
// #include "rosidl_runtime_c/string.h"

/// Struct defined in srv/StashRange in the package interfaces.
typedef struct interfaces__srv__StashRange_Response
{
  bool success;
  rosidl_runtime_c__String message;
} interfaces__srv__StashRange_Response;

// Struct for a sequence of interfaces__srv__StashRange_Response.
typedef struct interfaces__srv__StashRange_Response__Sequence
{
  interfaces__srv__StashRange_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} interfaces__srv__StashRange_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // INTERFACES__SRV__DETAIL__STASH_RANGE__STRUCT_H_
