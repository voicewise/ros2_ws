// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from interfaces:srv/GetAllColorName.idl
// generated code does not contain a copyright notice

#ifndef INTERFACES__SRV__DETAIL__GET_ALL_COLOR_NAME__BUILDER_HPP_
#define INTERFACES__SRV__DETAIL__GET_ALL_COLOR_NAME__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "interfaces/srv/detail/get_all_color_name__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace interfaces
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::GetAllColorName_Request>()
{
  return ::interfaces::srv::GetAllColorName_Request(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace interfaces


namespace interfaces
{

namespace srv
{

namespace builder
{

class Init_GetAllColorName_Response_color_names
{
public:
  Init_GetAllColorName_Response_color_names()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::interfaces::srv::GetAllColorName_Response color_names(::interfaces::srv::GetAllColorName_Response::_color_names_type arg)
  {
    msg_.color_names = std::move(arg);
    return std::move(msg_);
  }

private:
  ::interfaces::srv::GetAllColorName_Response msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::interfaces::srv::GetAllColorName_Response>()
{
  return interfaces::srv::builder::Init_GetAllColorName_Response_color_names();
}

}  // namespace interfaces

#endif  // INTERFACES__SRV__DETAIL__GET_ALL_COLOR_NAME__BUILDER_HPP_
