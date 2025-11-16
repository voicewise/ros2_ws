// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from puppy_control_msgs:msg/SetServo.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "puppy_control_msgs/msg/detail/set_servo__rosidl_typesupport_introspection_c.h"
#include "puppy_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "puppy_control_msgs/msg/detail/set_servo__functions.h"
#include "puppy_control_msgs/msg/detail/set_servo__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  puppy_control_msgs__msg__SetServo__init(message_memory);
}

void puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_fini_function(void * message_memory)
{
  puppy_control_msgs__msg__SetServo__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_member_array[3] = {
  {
    "id",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__msg__SetServo, id),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "pulse",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__msg__SetServo, pulse),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "time",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__msg__SetServo, time),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_members = {
  "puppy_control_msgs__msg",  // message namespace
  "SetServo",  // message name
  3,  // number of fields
  sizeof(puppy_control_msgs__msg__SetServo),
  puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_member_array,  // message members
  puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_init_function,  // function to initialize message memory (memory has to be allocated)
  puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_type_support_handle = {
  0,
  &puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_puppy_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, msg, SetServo)() {
  if (!puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_type_support_handle.typesupport_identifier) {
    puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &puppy_control_msgs__msg__SetServo__rosidl_typesupport_introspection_c__SetServo_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
