// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:srv/ChangeRange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__CHANGE_RANGE__BUILDER_HPP_
#define INTERFACES__SRV__DETAIL__CHANGE_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/srv/detail/change_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_ChangeRange_Request_max
{
public:
  explicit Init_ChangeRange_Request_max(::interfaces::srv::ChangeRange_Request & msg)
  : msg_(msg)
  {}
  ::interfaces::srv::ChangeRange_Request max(::interfaces::srv::ChangeRange_Request::_max_type arg)
  {
    msg_.max = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::ChangeRange_Request msg_;
};

class Init_ChangeRange_Request_min
{
public:
  Init_ChangeRange_Request_min()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeRange_Request_max min(::interfaces::srv::ChangeRange_Request::_min_type arg)
  {
    msg_.min = std::move(arg);
    return Init_ChangeRange_Request_max(msg_);
  }

private:
  ::interfaces::srv::ChangeRange_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::ChangeRange_Request>()
{
  return interfaces::srv::builder::Init_ChangeRange_Request_min();
}

}  // namespace interfaces


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_ChangeRange_Response_message
{
public:
  explicit Init_ChangeRange_Response_message(::interfaces::srv::ChangeRange_Response & msg)
  : msg_(msg)
  {}
  ::interfaces::srv::ChangeRange_Response message(::interfaces::srv::ChangeRange_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::ChangeRange_Response msg_;
};

class Init_ChangeRange_Response_success
{
public:
  Init_ChangeRange_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ChangeRange_Response_message success(::interfaces::srv::ChangeRange_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_ChangeRange_Response_message(msg_);
  }

private:
  ::interfaces::srv::ChangeRange_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::ChangeRange_Response>()
{
  return interfaces::srv::builder::Init_ChangeRange_Response_success();
}

}  // namespace interfaces

#endif  // INTERFACES__SRV__DETAIL__CHANGE_RANGE__BUILDER_HPP_
