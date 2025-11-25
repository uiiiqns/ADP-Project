// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__BUILDER_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__BUILDER_HPP_

#include <algorithm>
#include <utility>

#include "global_planner/msg/detail/wpnt_array__struct.hpp"
#include "rosidl_runtime_cpp/message_initialization.hpp"


namespace global_planner
{

namespace msg
{

namespace builder
{

class Init_WpntArray_waypoints
{
public:
  Init_WpntArray_waypoints()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::global_planner::msg::WpntArray waypoints(::global_planner::msg::WpntArray::_waypoints_type arg)
  {
    msg_.waypoints = std::move(arg);
    return std::move(msg_);
  }

private:
  ::global_planner::msg::WpntArray msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::global_planner::msg::WpntArray>()
{
  return global_planner::msg::builder::Init_WpntArray_waypoints();
}

}  // namespace global_planner

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__BUILDER_HPP_
