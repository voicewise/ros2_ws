// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from puppy_control_msgs:msg/Velocity.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__BUILDER_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "puppy_control_msgs/msg/detail/velocity__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace puppy_control_msgs
{

namespace msg
{

namespace builder
{

class Init_Velocity_yaw_rate
{
public:
  explicit Init_Velocity_yaw_rate(::puppy_control_msgs::msg::Velocity & msg)
  : msg_(msg)
  {}
  ::puppy_control_msgs::msg::Velocity yaw_rate(::puppy_control_msgs::msg::Velocity::_yaw_rate_type arg)
  {
    msg_.yaw_rate = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puppy_control_msgs::msg::Velocity msg_;
};

class Init_Velocity_y
{
public:
  explicit Init_Velocity_y(::puppy_control_msgs::msg::Velocity & msg)
  : msg_(msg)
  {}
  Init_Velocity_yaw_rate y(::puppy_control_msgs::msg::Velocity::_y_type arg)
  {
    msg_.y = std::move(arg);
    return Init_Velocity_yaw_rate(msg_);
  }

private:
  ::puppy_control_msgs::msg::Velocity msg_;
};

class Init_Velocity_x
{
public:
  Init_Velocity_x()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Velocity_y x(::puppy_control_msgs::msg::Velocity::_x_type arg)
  {
    msg_.x = std::move(arg);
    return Init_Velocity_y(msg_);
  }

private:
  ::puppy_control_msgs::msg::Velocity msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::puppy_control_msgs::msg::Velocity>()
{
  return puppy_control_msgs::msg::builder::Init_Velocity_x();
}

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__VELOCITY__BUILDER_HPP_
