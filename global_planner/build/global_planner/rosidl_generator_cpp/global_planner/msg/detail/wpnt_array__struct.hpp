// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__STRUCT_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__STRUCT_HPP_

#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>

#include "rosidl_runtime_cpp/bounded_vector.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


// Include directives for member types
// Member 'waypoints'
#include "global_planner/msg/detail/wpnt__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__global_planner__msg__WpntArray __attribute__((deprecated))
#else
# define DEPRECATED__global_planner__msg__WpntArray __declspec(deprecated)
#endif

namespace global_planner
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct WpntArray_
{
  using Type = WpntArray_<ContainerAllocator>;

  explicit WpntArray_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit WpntArray_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _waypoints_type =
    std::vector<global_planner::msg::Wpnt_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<global_planner::msg::Wpnt_<ContainerAllocator>>>;
  _waypoints_type waypoints;

  // setters for named parameter idiom
  Type & set__waypoints(
    const std::vector<global_planner::msg::Wpnt_<ContainerAllocator>, typename std::allocator_traits<ContainerAllocator>::template rebind_alloc<global_planner::msg::Wpnt_<ContainerAllocator>>> & _arg)
  {
    this->waypoints = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    global_planner::msg::WpntArray_<ContainerAllocator> *;
  using ConstRawPtr =
    const global_planner::msg::WpntArray_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<global_planner::msg::WpntArray_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<global_planner::msg::WpntArray_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      global_planner::msg::WpntArray_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<global_planner::msg::WpntArray_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      global_planner::msg::WpntArray_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<global_planner::msg::WpntArray_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<global_planner::msg::WpntArray_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<global_planner::msg::WpntArray_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__global_planner__msg__WpntArray
    std::shared_ptr<global_planner::msg::WpntArray_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__global_planner__msg__WpntArray
    std::shared_ptr<global_planner::msg::WpntArray_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const WpntArray_ & other) const
  {
    if (this->waypoints != other.waypoints) {
      return false;
    }
    return true;
  }
  bool operator!=(const WpntArray_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct WpntArray_

// alias to use template instance with default allocator
using WpntArray =
  global_planner::msg::WpntArray_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace global_planner

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__STRUCT_HPP_
