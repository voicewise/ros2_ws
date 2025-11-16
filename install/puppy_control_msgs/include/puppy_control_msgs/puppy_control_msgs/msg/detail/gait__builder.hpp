// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from puppy_control_msgs:msg/Gait.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__BUILDER_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "puppy_control_msgs/msg/detail/gait__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace puppy_control_msgs
{

namespace msg
{

namespace builder
{

class Init_Gait_z_clearance
{
public:
  explicit Init_Gait_z_clearance(::puppy_control_msgs::msg::Gait & msg)
  : msg_(msg)
  {}
  ::puppy_control_msgs::msg::Gait z_clearance(::puppy_control_msgs::msg::Gait::_z_clearance_type arg)
  {
    msg_.z_clearance = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puppy_control_msgs::msg::Gait msg_;
};

class Init_Gait_clearance_time
{
public:
  explicit Init_Gait_clearance_time(::puppy_control_msgs::msg::Gait & msg)
  : msg_(msg)
  {}
  Init_Gait_z_clearance clearance_time(::puppy_control_msgs::msg::Gait::_clearance_time_type arg)
  {
    msg_.clearance_time = std::move(arg);
    return Init_Gait_z_clearance(msg_);
  }

private:
  ::puppy_control_msgs::msg::Gait msg_;
};

class Init_Gait_swing_time
{
public:
  explicit Init_Gait_swing_time(::puppy_control_msgs::msg::Gait & msg)
  : msg_(msg)
  {}
  Init_Gait_clearance_time swing_time(::puppy_control_msgs::msg::Gait::_swing_time_type arg)
  {
    msg_.swing_time = std::move(arg);
    return Init_Gait_clearance_time(msg_);
  }

private:
  ::puppy_control_msgs::msg::Gait msg_;
};

class Init_Gait_overlap_time
{
public:
  Init_Gait_overlap_time()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Gait_swing_time overlap_time(::puppy_control_msgs::msg::Gait::_overlap_time_type arg)
  {
    msg_.overlap_time = std::move(arg);
    return Init_Gait_swing_time(msg_);
  }

private:
  ::puppy_control_msgs::msg::Gait msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::puppy_control_msgs::msg::Gait>()
{
  return puppy_control_msgs::msg::builder::Init_Gait_overlap_time();
}

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__GAIT__BUILDER_HPP_
