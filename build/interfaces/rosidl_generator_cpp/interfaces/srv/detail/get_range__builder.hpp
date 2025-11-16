// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:srv/GetRange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__GET_RANGE__BUILDER_HPP_
#define INTERFACES__SRV__DETAIL__GET_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/srv/detail/get_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_GetRange_Request_color_name
{
public:
  Init_GetRange_Request_color_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::srv::GetRange_Request color_name(::interfaces::srv::GetRange_Request::_color_name_type arg)
  {
    msg_.color_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::GetRange_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::GetRange_Request>()
{
  return interfaces::srv::builder::Init_GetRange_Request_color_name();
}

}  // namespace interfaces


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_GetRange_Response_max
{
public:
  explicit Init_GetRange_Response_max(::interfaces::srv::GetRange_Response & msg)
  : msg_(msg)
  {}
  ::interfaces::srv::GetRange_Response max(::interfaces::srv::GetRange_Response::_max_type arg)
  {
    msg_.max = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::GetRange_Response msg_;
};

class Init_GetRange_Response_min
{
public:
  explicit Init_GetRange_Response_min(::interfaces::srv::GetRange_Response & msg)
  : msg_(msg)
  {}
  Init_GetRange_Response_max min(::interfaces::srv::GetRange_Response::_min_type arg)
  {
    msg_.min = std::move(arg);
    return Init_GetRange_Response_max(msg_);
  }

private:
  ::interfaces::srv::GetRange_Response msg_;
};

class Init_GetRange_Response_success
{
public:
  Init_GetRange_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_GetRange_Response_min success(::interfaces::srv::GetRange_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_GetRange_Response_min(msg_);
  }

private:
  ::interfaces::srv::GetRange_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::GetRange_Response>()
{
  return interfaces::srv::builder::Init_GetRange_Response_success();
}

}  // namespace interfaces

#endif  // INTERFACES__SRV__DETAIL__GET_RANGE__BUILDER_HPP_
