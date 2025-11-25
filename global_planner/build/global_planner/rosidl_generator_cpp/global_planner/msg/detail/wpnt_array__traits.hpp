// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice

#ifndef GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__TRAITS_HPP_
#define GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__TRAITS_HPP_

#include <stdint.h>

#include <sstream>
#include <string>
#include <type_traits>

#include "global_planner/msg/detail/wpnt_array__struct.hpp"
#include "rosidl_runtime_cpp/traits.hpp"

// Include directives for member types
// Member 'waypoints'
#include "global_planner/msg/detail/wpnt__traits.hpp"

namespace global_planner
{

namespace msg
{

inline void to_flow_style_yaml(
  const WpntArray & msg,
  std::ostream & out)
{
  out << "{";
  // member: waypoints
  {
    if (msg.waypoints.size() == 0) {
      out << "waypoints: []";
    } else {
      out << "waypoints: [";
      size_t pending_items = msg.waypoints.size();
      for (auto item : msg.waypoints) {
        to_flow_style_yaml(item, out);
        if (--pending_items > 0) {
          out << ", ";
        }
      }
      out << "]";
    }
  }
  out << "}";
}  // NOLINT(readability/fn_size)

inline void to_block_style_yaml(
  const WpntArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: waypoints
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.waypoints.size() == 0) {
      out << "waypoints: []\n";
    } else {
      out << "waypoints:\n";
      for (auto item : msg.waypoints) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "-\n";
        to_block_style_yaml(item, out, indentation + 2);
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const WpntArray & msg, bool use_flow_style = false)
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
  const global_planner::msg::WpntArray & msg,
  std::ostream & out, size_t indentation = 0)
{
  global_planner::msg::to_block_style_yaml(msg, out, indentation);
}

[[deprecated("use global_planner::msg::to_yaml() instead")]]
inline std::string to_yaml(const global_planner::msg::WpntArray & msg)
{
  return global_planner::msg::to_yaml(msg);
}

template<>
inline const char * data_type<global_planner::msg::WpntArray>()
{
  return "global_planner::msg::WpntArray";
}

template<>
inline const char * name<global_planner::msg::WpntArray>()
{
  return "global_planner/msg/WpntArray";
}

template<>
struct has_fixed_size<global_planner::msg::WpntArray>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<global_planner::msg::WpntArray>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<global_planner::msg::WpntArray>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // GLOBAL_PLANNER__MSG__DETAIL__WPNT_ARRAY__TRAITS_HPP_
