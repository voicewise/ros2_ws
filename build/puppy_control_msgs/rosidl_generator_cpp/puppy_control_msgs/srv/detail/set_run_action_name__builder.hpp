// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from puppy_control_msgs:srv/SetRunActionName.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__BUILDER_HPP_
#define PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "puppy_control_msgs/srv/detail/set_run_action_name__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace puppy_control_msgs
{

namespace srv
{

namespace builder
{

class Init_SetRunActionName_Request_wait
{
public:
  explicit Init_SetRunActionName_Request_wait(::puppy_control_msgs::srv::SetRunActionName_Request & msg)
  : msg_(msg)
  {}
  ::puppy_control_msgs::srv::SetRunActionName_Request wait(::puppy_control_msgs::srv::SetRunActionName_Request::_wait_type arg)
  {
    msg_.wait = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puppy_control_msgs::srv::SetRunActionName_Request msg_;
};

class Init_SetRunActionName_Request_name
{
public:
  Init_SetRunActionName_Request_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetRunActionName_Request_wait name(::puppy_control_msgs::srv::SetRunActionName_Request::_name_type arg)
  {
    msg_.name = std::move(arg);
    return Init_SetRunActionName_Request_wait(msg_);
  }

private:
  ::puppy_control_msgs::srv::SetRunActionName_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::puppy_control_msgs::srv::SetRunActionName_Request>()
{
  return puppy_control_msgs::srv::builder::Init_SetRunActionName_Request_name();
}

}  // namespace puppy_control_msgs


namespace puppy_control_msgs
{

namespace srv
{

namespace builder
{

class Init_SetRunActionName_Response_message
{
public:
  explicit Init_SetRunActionName_Response_message(::puppy_control_msgs::srv::SetRunActionName_Response & msg)
  : msg_(msg)
  {}
  ::puppy_control_msgs::srv::SetRunActionName_Response message(::puppy_control_msgs::srv::SetRunActionName_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puppy_control_msgs::srv::SetRunActionName_Response msg_;
};

class Init_SetRunActionName_Response_success
{
public:
  Init_SetRunActionName_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetRunActionName_Response_message success(::puppy_control_msgs::srv::SetRunActionName_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_SetRunActionName_Response_message(msg_);
  }

private:
  ::puppy_control_msgs::srv::SetRunActionName_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::puppy_control_msgs::srv::SetRunActionName_Response>()
{
  return puppy_control_msgs::srv::builder::Init_SetRunActionName_Response_success();
}

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__BUILDER_HPP_
