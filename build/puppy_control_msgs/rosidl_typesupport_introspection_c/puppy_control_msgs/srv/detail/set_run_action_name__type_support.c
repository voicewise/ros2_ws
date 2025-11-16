// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from puppy_control_msgs:srv/SetRunActionName.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "puppy_control_msgs/srv/detail/set_run_action_name__rosidl_typesupport_introspection_c.h"
#include "puppy_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "puppy_control_msgs/srv/detail/set_run_action_name__functions.h"
#include "puppy_control_msgs/srv/detail/set_run_action_name__struct.h"


// Include directives for member types
// Member `name`
#include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  puppy_control_msgs__srv__SetRunActionName_Request__init(message_memory);
}

void puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_fini_function(void * message_memory)
{
  puppy_control_msgs__srv__SetRunActionName_Request__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_member_array[2] = {
  {
    "name",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__srv__SetRunActionName_Request, name),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "wait",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__srv__SetRunActionName_Request, wait),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_members = {
  "puppy_control_msgs__srv",  // message namespace
  "SetRunActionName_Request",  // message name
  2,  // number of fields
  sizeof(puppy_control_msgs__srv__SetRunActionName_Request),
  puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_member_array,  // message members
  puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_init_function,  // function to initialize message memory (memory has to be allocated)
  puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_type_support_handle = {
  0,
  &puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_puppy_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName_Request)() {
  if (!puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_type_support_handle.typesupport_identifier) {
    puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &puppy_control_msgs__srv__SetRunActionName_Request__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

// already included above
// #include <stddef.h>
// already included above
// #include "puppy_control_msgs/srv/detail/set_run_action_name__rosidl_typesupport_introspection_c.h"
// already included above
// #include "puppy_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "rosidl_typesupport_introspection_c/field_types.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
// already included above
// #include "rosidl_typesupport_introspection_c/message_introspection.h"
// already included above
// #include "puppy_control_msgs/srv/detail/set_run_action_name__functions.h"
// already included above
// #include "puppy_control_msgs/srv/detail/set_run_action_name__struct.h"


// Include directives for member types
// Member `message`
// already included above
// #include "rosidl_runtime_c/string_functions.h"

#ifdef __cplusplus
extern "C"
{
#endif

void puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  puppy_control_msgs__srv__SetRunActionName_Response__init(message_memory);
}

void puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_fini_function(void * message_memory)
{
  puppy_control_msgs__srv__SetRunActionName_Response__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_member_array[2] = {
  {
    "success",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_BOOLEAN,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__srv__SetRunActionName_Response, success),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "message",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_STRING,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(puppy_control_msgs__srv__SetRunActionName_Response, message),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_members = {
  "puppy_control_msgs__srv",  // message namespace
  "SetRunActionName_Response",  // message name
  2,  // number of fields
  sizeof(puppy_control_msgs__srv__SetRunActionName_Response),
  puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_member_array,  // message members
  puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_init_function,  // function to initialize message memory (memory has to be allocated)
  puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_type_support_handle = {
  0,
  &puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_puppy_control_msgs
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName_Response)() {
  if (!puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_type_support_handle.typesupport_identifier) {
    puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &puppy_control_msgs__srv__SetRunActionName_Response__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif

#include "rosidl_runtime_c/service_type_support_struct.h"
// already included above
// #include "puppy_control_msgs/msg/rosidl_typesupport_introspection_c__visibility_control.h"
// already included above
// #include "puppy_control_msgs/srv/detail/set_run_action_name__rosidl_typesupport_introspection_c.h"
// already included above
// #include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/service_introspection.h"

// this is intentionally not const to allow initialization later to prevent an initialization race
static rosidl_typesupport_introspection_c__ServiceMembers puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_members = {
  "puppy_control_msgs__srv",  // service namespace
  "SetRunActionName",  // service name
  // these two fields are initialized below on the first access
  NULL,  // request message
  // puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_Request_message_type_support_handle,
  NULL  // response message
  // puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_Response_message_type_support_handle
};

static rosidl_service_type_support_t puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_type_support_handle = {
  0,
  &puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_members,
  get_service_typesupport_handle_function,
};

// Forward declaration of request/response type support functions
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName_Request)();

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName_Response)();

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_puppy_control_msgs
const rosidl_service_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__SERVICE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName)() {
  if (!puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_type_support_handle.typesupport_identifier) {
    puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  rosidl_typesupport_introspection_c__ServiceMembers * service_members =
    (rosidl_typesupport_introspection_c__ServiceMembers *)puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_type_support_handle.data;

  if (!service_members->request_members_) {
    service_members->request_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName_Request)()->data;
  }
  if (!service_members->response_members_) {
    service_members->response_members_ =
      (const rosidl_typesupport_introspection_c__MessageMembers *)
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, puppy_control_msgs, srv, SetRunActionName_Response)()->data;
  }

  return &puppy_control_msgs__srv__detail__set_run_action_name__rosidl_typesupport_introspection_c__SetRunActionName_service_type_support_handle;
}
