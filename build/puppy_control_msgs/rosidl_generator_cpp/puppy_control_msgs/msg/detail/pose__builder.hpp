// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from puppy_control_msgs:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__BUILDER_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "puppy_control_msgs/msg/detail/pose__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace puppy_control_msgs
{

namespace msg
{

namespace builder
{

class Init_Pose_run_time
{
public:
  explicit Init_Pose_run_time(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  ::puppy_control_msgs::msg::Pose run_time(::puppy_control_msgs::msg::Pose::_run_time_type arg)
  {
    msg_.run_time = std::move(arg);
    return std::move(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_stance_y
{
public:
  explicit Init_Pose_stance_y(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_run_time stance_y(::puppy_control_msgs::msg::Pose::_stance_y_type arg)
  {
    msg_.stance_y = std::move(arg);
    return Init_Pose_run_time(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_stance_x
{
public:
  explicit Init_Pose_stance_x(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_stance_y stance_x(::puppy_control_msgs::msg::Pose::_stance_x_type arg)
  {
    msg_.stance_x = std::move(arg);
    return Init_Pose_stance_y(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_x_shift
{
public:
  explicit Init_Pose_x_shift(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_stance_x x_shift(::puppy_control_msgs::msg::Pose::_x_shift_type arg)
  {
    msg_.x_shift = std::move(arg);
    return Init_Pose_stance_x(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_height
{
public:
  explicit Init_Pose_height(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_x_shift height(::puppy_control_msgs::msg::Pose::_height_type arg)
  {
    msg_.height = std::move(arg);
    return Init_Pose_x_shift(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_yaw
{
public:
  explicit Init_Pose_yaw(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_height yaw(::puppy_control_msgs::msg::Pose::_yaw_type arg)
  {
    msg_.yaw = std::move(arg);
    return Init_Pose_height(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_pitch
{
public:
  explicit Init_Pose_pitch(::puppy_control_msgs::msg::Pose & msg)
  : msg_(msg)
  {}
  Init_Pose_yaw pitch(::puppy_control_msgs::msg::Pose::_pitch_type arg)
  {
    msg_.pitch = std::move(arg);
    return Init_Pose_yaw(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

class Init_Pose_roll
{
public:
  Init_Pose_roll()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Pose_pitch roll(::puppy_control_msgs::msg::Pose::_roll_type arg)
  {
    msg_.roll = std::move(arg);
    return Init_Pose_pitch(msg_);
  }

private:
  ::puppy_control_msgs::msg::Pose msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::puppy_control_msgs::msg::Pose>()
{
  return puppy_control_msgs::msg::builder::Init_Pose_roll();
}

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__BUILDER_HPP_
