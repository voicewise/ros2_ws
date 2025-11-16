// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:srv/StashRange.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__STASH_RANGE__BUILDER_HPP_
#define INTERFACES__SRV__DETAIL__STASH_RANGE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/srv/detail/stash_range__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_StashRange_Request_color_name
{
public:
  Init_StashRange_Request_color_name()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::srv::StashRange_Request color_name(::interfaces::srv::StashRange_Request::_color_name_type arg)
  {
    msg_.color_name = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::StashRange_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::StashRange_Request>()
{
  return interfaces::srv::builder::Init_StashRange_Request_color_name();
}

}  // namespace interfaces


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_StashRange_Response_message
{
public:
  explicit Init_StashRange_Response_message(::interfaces::srv::StashRange_Response & msg)
  : msg_(msg)
  {}
  ::interfaces::srv::StashRange_Response message(::interfaces::srv::StashRange_Response::_message_type arg)
  {
    msg_.message = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::StashRange_Response msg_;
};

class Init_StashRange_Response_success
{
public:
  Init_StashRange_Response_success()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_StashRange_Response_message success(::interfaces::srv::StashRange_Response::_success_type arg)
  {
    msg_.success = std::move(arg);
    return Init_StashRange_Response_message(msg_);
  }

private:
  ::interfaces::srv::StashRange_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::StashRange_Response>()
{
  return interfaces::srv::builder::Init_StashRange_Response_success();
}

}  // namespace interfaces

#endif  // INTERFACES__SRV__DETAIL__STASH_RANGE__BUILDER_HPP_
