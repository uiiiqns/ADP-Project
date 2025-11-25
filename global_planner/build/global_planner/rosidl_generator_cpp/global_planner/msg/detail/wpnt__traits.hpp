// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from global_planner:msg/Wpnt.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT__TRAITS_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "global_planner/msg/detail/wpnt__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

namespace global_planner
{

namespace msg
{

inline void to_flow_style_yaml(
  const Wpnt & msg,
  std::ostream & out)
{
  out << "{";
  // member: x
  {
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << ", ";
  }

  // member: y
  {
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << ", ";
  }

  // member: yaw
  {
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << ", ";
  }

  // member: curvature
  {
    out << "curvature: ";
    rosidl_generator_traits::value_to_yaml(msg.curvature, out);
    out << ", ";
  }

  // member: velocity
  {
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const Wpnt & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: x
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "x: ";
    rosidl_generator_traits::value_to_yaml(msg.x, out);
    out << "\n";
  }

  // member: y
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "y: ";
    rosidl_generator_traits::value_to_yaml(msg.y, out);
    out << "\n";
  }

  // member: yaw
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "yaw: ";
    rosidl_generator_traits::value_to_yaml(msg.yaw, out);
    out << "\n";
  }

  // member: curvature
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "curvature: ";
    rosidl_generator_traits::value_to_yaml(msg.curvature, out);
    out << "\n";
  }

  // member: velocity
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "velocity: ";
    rosidl_generator_traits::value_to_yaml(msg.velocity, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const Wpnt & msg, bool use_flow_style = false)
{
  std::ostringstream out;
  if (use_flow_style) {
    to_flow_style_yaml(msg, out);
  } else {
    to_block_style_yaml(msg, out);
  }
  return out.str();
}

}  // namespace msg

}  // namespace global_planner

namespace rosidl_generator_traits
{

[[deprecated("use global_planner::msg::to_block_style_yaml() instead")]]
inline void to_yaml(
  const global_planner::msg::Wpnt & msg,
  std::ostream & out, size_t indentation = 0)
{
  global_planner::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use global_planner::msg::to_yaml() instead")]]
inline std::string to_yaml(const global_planner::msg::Wpnt & msg)
{
  return global_planner::msg::to_yaml(msg);
}

template<>
inline const char * data_type<global_planner::msg::Wpnt>()
{
  return "global_planner::msg::Wpnt";
}

template<>
inline const char * name<global_planner::msg::Wpnt>()
{
  return "global_planner/msg/Wpnt";
}

template<>
struct has_fixed_size<global_planner::msg::Wpnt>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<global_planner::msg::Wpnt>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<global_planner::msg::Wpnt>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT__TRAITS_HPP_
