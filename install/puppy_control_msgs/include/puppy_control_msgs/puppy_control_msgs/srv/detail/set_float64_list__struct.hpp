// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from puppy_control_msgs:srv/SetFloat64List.idl
// generated code does not contain a copyright notice

#ifndef PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_FLOAT64_LIST__STRUCT_HPP_
#define PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_FLOAT64_LIST__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Request __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Request __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetFloat64List_Request_
{
  using Type = SetFloat64List_Request_<ContainerAllocator>;

  explicit SetFloat64List_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SetFloat64List_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _data_type =
    std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>>;
  _data_type data;

  // setters for named parameter idiom
  Type & set__data(
    const std::vector<double, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<double>> & _arg)
  {
    this->data = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Request
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Request
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetFloat64List_Request_ & other) const
  {
    if (this->data != other.data) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetFloat64List_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetFloat64List_Request_

// alias to use template instance with default allocator
using SetFloat64List_Request =
  puppy_control_msgs::srv::SetFloat64List_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace puppy_control_msgs


#ifndef _WIN32
# define DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Response __attribute__((deprecated))
#else
# define DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Response __declspec(deprecated)
#endif

namespace puppy_control_msgs
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct SetFloat64List_Response_
{
  using Type = SetFloat64List_Response_<ContainerAllocator>;

  explicit SetFloat64List_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->success = false;
      this->message = "";
    }
  }

  explicit SetFloat64List_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
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
    puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Response
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__puppy_control_msgs__srv__SetFloat64List_Response
    std::shared_ptr<puppy_control_msgs::srv::SetFloat64List_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetFloat64List_Response_ & other) const
  {
    if (this->success != other.success) {
      return false;
    }
    if (this->message != other.message) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetFloat64List_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetFloat64List_Response_

// alias to use template instance with default allocator
using SetFloat64List_Response =
  puppy_control_msgs::srv::SetFloat64List_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace puppy_control_msgs

namespace puppy_control_msgs
{

namespace srv
{

struct SetFloat64List
{
  using Request = puppy_control_msgs::srv::SetFloat64List_Request;
  using Response = puppy_control_msgs::srv::SetFloat64List_Response;
};

}  // namespace srv

}  // namespace puppy_control_msgs

#endif  // PUPPY_CONTROL_MSGS__SRV__DETAIL__SET_FLOAT64_LIST__STRUCT_HPP_
