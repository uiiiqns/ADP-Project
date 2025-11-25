// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "global_planner/msg/detail/wpnt_array__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace global_planner
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void WpntArray_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) global_planner::msg::WpntArray(_init);
}

void WpntArray_fini_function(void * message_memory)
{
  auto typed_message = static_cast<global_planner::msg::WpntArray *>(message_memory);
  typed_message->~WpntArray();
}

size_t size_function__WpntArray__waypoints(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<global_planner::msg::Wpnt> *>(untyped_member);
  return member->size();
}

const void * get_const_function__WpntArray__waypoints(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<global_planner::msg::Wpnt> *>(untyped_member);
  return &member[index];
}

void * get_function__WpntArray__waypoints(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<global_planner::msg::Wpnt> *>(untyped_member);
  return &member[index];
}

void fetch_function__WpntArray__waypoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const auto & item = *reinterpret_cast<const global_planner::msg::Wpnt *>(
    get_const_function__WpntArray__waypoints(untyped_member, index));
  auto & value = *reinterpret_cast<global_planner::msg::Wpnt *>(untyped_value);
  value = item;
}

void assign_function__WpntArray__waypoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  auto & item = *reinterpret_cast<global_planner::msg::Wpnt *>(
    get_function__WpntArray__waypoints(untyped_member, index));
  const auto & value = *reinterpret_cast<const global_planner::msg::Wpnt *>(untyped_value);
  item = value;
}

void resize_function__WpntArray__waypoints(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<global_planner::msg::Wpnt> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember WpntArray_message_member_array[1] = {
  {
    "waypoints",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    ::rosidl_typesupport_introspection_cpp::get_message_type_support_handle<global_planner::msg::Wpnt>(),  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner::msg::WpntArray, waypoints),  // bytes offset in struct
    nullptr,  // default value
    size_function__WpntArray__waypoints,  // size() function pointer
    get_const_function__WpntArray__waypoints,  // get_const(index) function pointer
    get_function__WpntArray__waypoints,  // get(index) function pointer
    fetch_function__WpntArray__waypoints,  // fetch(index, &value) function pointer
    assign_function__WpntArray__waypoints,  // assign(index, value) function pointer
    resize_function__WpntArray__waypoints  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers WpntArray_message_members = {
  "global_planner::msg",  // message namespace
  "WpntArray",  // message name
  1,  // number of fields
  sizeof(global_planner::msg::WpntArray),
  WpntArray_message_member_array,  // message members
  WpntArray_init_function,  // function to initialize message memory (memory has to be allocated)
  WpntArray_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t WpntArray_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &WpntArray_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace global_planner


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<global_planner::msg::WpntArray>()
{
  return &::global_planner::msg::rosidl_typesupport_introspection_cpp::WpntArray_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, global_planner, msg, WpntArray)() {
  return &::global_planner::msg::rosidl_typesupport_introspection_cpp::WpntArray_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
