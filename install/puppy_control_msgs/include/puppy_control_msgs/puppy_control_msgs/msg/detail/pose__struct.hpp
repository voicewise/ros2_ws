// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from puppy_control_msgs:msg/Pose.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__STRUCT_HPP_
#define PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__msg__Pose __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__msg__Pose __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Pose_
{
  using Type = Pose_<ContainerAllocator>;

  explicit Pose_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw = 0.0f;
      this->height = 0.0f;
      this->x_shift = 0.0f;
      this->stance_x = 0.0f;
      this->stance_y = 0.0f;
      this->run_time = 0l;
    }
  }

  explicit Pose_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->roll = 0.0f;
      this->pitch = 0.0f;
      this->yaw = 0.0f;
      this->height = 0.0f;
      this->x_shift = 0.0f;
      this->stance_x = 0.0f;
      this->stance_y = 0.0f;
      this->run_time = 0l;
    }
  }

  // field types and members
  using _roll_type =
    float;
  _roll_type roll;
  using _pitch_type =
    float;
  _pitch_type pitch;
  using _yaw_type =
    float;
  _yaw_type yaw;
  using _height_type =
    float;
  _height_type height;
  using _x_shift_type =
    float;
  _x_shift_type x_shift;
  using _stance_x_type =
    float;
  _stance_x_type stance_x;
  using _stance_y_type =
    float;
  _stance_y_type stance_y;
  using _run_time_type =
    int32_t;
  _run_time_type run_time;

  // setters for named parameter idiom
  Type & set__roll(
    const float & _arg)
  {
    this->roll = _arg;
    return *this;
  }
  Type & set__pitch(
    const float & _arg)
  {
    this->pitch = _arg;
    return *this;
  }
  Type & set__yaw(
    const float & _arg)
  {
    this->yaw = _arg;
    return *this;
  }
  Type & set__height(
    const float & _arg)
  {
    this->height = _arg;
    return *this;
  }
  Type & set__x_shift(
    const float & _arg)
  {
    this->x_shift = _arg;
    return *this;
  }
  Type & set__stance_x(
    const float & _arg)
  {
    this->stance_x = _arg;
    return *this;
  }
  Type & set__stance_y(
    const float & _arg)
  {
    this->stance_y = _arg;
    return *this;
  }
  Type & set__run_time(
    const int32_t & _arg)
  {
    this->run_time = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    puppy_control_msgs::msg::Pose_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::msg::Pose_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::msg::Pose_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::msg::Pose_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__msg__Pose
    std::shared_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__msg__Pose
    std::shared_ptr<puppy_control_msgs::msg::Pose_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Pose_ & other) const
  {
    if (this->roll != other.roll) {
      return false;
    }
    if (this->pitch != other.pitch) {
      return false;
    }
    if (this->yaw != other.yaw) {
      return false;
    }
    if (this->height != other.height) {
      return false;
    }
    if (this->x_shift != other.x_shift) {
      return false;
    }
    if (this->stance_x != other.stance_x) {
      return false;
    }
    if (this->stance_y != other.stance_y) {
      return false;
    }
    if (this->run_time != other.run_time) {
      return false;
    }
    return true;
  }
  bool operator!=(const Pose_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Pose_

// alias to use template instance with default allocator
using Pose =
  puppy_control_msgs::msg::Pose_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__MSG__DETAIL__POSE__STRUCT_HPP_
