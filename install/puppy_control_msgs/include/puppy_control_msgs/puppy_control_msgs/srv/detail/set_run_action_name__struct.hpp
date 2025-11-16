// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from puppy_control_msgs:srv/SetRunActionName.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__STRUCT_HPP_
#define PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Request __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Request __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetRunActionName_Request_
{
  using Type = SetRunActionName_Request_<ContainerAllocator>;

  explicit SetRunActionName_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->wait = false;
    }
  }

  explicit SetRunActionName_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : name(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->name = "";
      this->wait = false;
    }
  }

  // field types and members
  using _name_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _name_type name;
  using _wait_type =
    bool;
  _wait_type wait;

  // setters for named parameter idiom
  Type & set__name(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->name = _arg;
    return *this;
  }
  Type & set__wait(
    const bool & _arg)
  {
    this->wait = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Request
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Request
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetRunActionName_Request_ & other) const
  {
    if (this->name != other.name) {
      return false;
    }
    if (this->wait != other.wait) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetRunActionName_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetRunActionName_Request_

// alias to use template instance with default allocator
using SetRunActionName_Request =
  puppy_control_msgs::srv::SetRunActionName_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace puppy_control_msgs


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Response __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Response __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetRunActionName_Response_
{
  using Type = SetRunActionName_Response_<ContainerAllocator>;

  explicit SetRunActionName_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetRunActionName_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  // field types and members
  using _success_type =
    bool;
  _success_type success;
  using _message_type =
    std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>>;
  _message_type message;

  // setters for named parameter idiom
  Type & set__success(
    const bool & _arg)
  {
    this->success = _arg;
    return *this;
  }
  Type & set__message(
    const std::basic_string<char, std::char_traits<char>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<char>> & _arg)
  {
    this->message = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Response
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__srv__SetRunActionName_Response
    std::shared_ptr<puppy_control_msgs::srv::SetRunActionName_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetRunActionName_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetRunActionName_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetRunActionName_Response_

// alias to use template instance with default allocator
using SetRunActionName_Response =
  puppy_control_msgs::srv::SetRunActionName_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace puppy_control_msgs

namespace puppy_control_msgs
{

namespace srv
{

struct SetRunActionName
{
  using Request = puppy_control_msgs::srv::SetRunActionName_Request;
  using Response = puppy_control_msgs::srv::SetRunActionName_Response;
};

}  // namespace srv

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_RUN_ACTION_NAME__STRUCT_HPP_
