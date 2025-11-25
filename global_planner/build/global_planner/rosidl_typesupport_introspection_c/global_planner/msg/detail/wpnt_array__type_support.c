// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from global_planner:msg/WpntArray.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "global_planner/msg/detail/wpnt_array__rosidl_typesupport_introspection_c.h"
#include "global_planner/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "global_planner/msg/detail/wpnt_array__functions.h"
#include "global_planner/msg/detail/wpnt_array__struct.h"


// Include directives for member types
// Member `waypoints`
#include "global_planner/msg/wpnt.h"
// Member `waypoints`
#include "global_planner/msg/detail/wpnt__rosidl_typesupport_introspection_c.h"

#ifdef __cplusplus
extern "C"
{
#endif

void global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  global_planner__msg__WpntArray__init(message_memory);
}

void global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_fini_function(void * message_memory)
{
  global_planner__msg__WpntArray__fini(message_memory);
}

size_t global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__size_function__WpntArray__waypoints(
  const void * untyped_member)
{
  const global_planner__msg__Wpnt__Sequence * member =
    (const global_planner__msg__Wpnt__Sequence *)(untyped_member);
  return member->size;
}

const void * global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__get_const_function__WpntArray__waypoints(
  const void * untyped_member, size_t index)
{
  const global_planner__msg__Wpnt__Sequence * member =
    (const global_planner__msg__Wpnt__Sequence *)(untyped_member);
  return &member->data[index];
}

void * global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__get_function__WpntArray__waypoints(
  void * untyped_member, size_t index)
{
  global_planner__msg__Wpnt__Sequence * member =
    (global_planner__msg__Wpnt__Sequence *)(untyped_member);
  return &member->data[index];
}

void global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__fetch_function__WpntArray__waypoints(
  const void * untyped_member, size_t index, void * untyped_value)
{
  const global_planner__msg__Wpnt * item =
    ((const global_planner__msg__Wpnt *)
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__get_const_function__WpntArray__waypoints(untyped_member, index));
  global_planner__msg__Wpnt * value =
    (global_planner__msg__Wpnt *)(untyped_value);
  *value = *item;
}

void global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__assign_function__WpntArray__waypoints(
  void * untyped_member, size_t index, const void * untyped_value)
{
  global_planner__msg__Wpnt * item =
    ((global_planner__msg__Wpnt *)
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__get_function__WpntArray__waypoints(untyped_member, index));
  const global_planner__msg__Wpnt * value =
    (const global_planner__msg__Wpnt *)(untyped_value);
  *item = *value;
}

bool global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__resize_function__WpntArray__waypoints(
  void * untyped_member, size_t size)
{
  global_planner__msg__Wpnt__Sequence * member =
    (global_planner__msg__Wpnt__Sequence *)(untyped_member);
  global_planner__msg__Wpnt__Sequence__fini(member);
  return global_planner__msg__Wpnt__Sequence__init(member, size);
}

static rosidl_typesupport_introspection_c__MessageMember global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_member_array[1] = {
  {
    "waypoints",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_MESSAGE,  // type
    0,  // upper bound of string
    NULL,  // members of sub message (initialized later)
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner__msg__WpntArray, waypoints),  // bytes offset in struct
    NULL,  // default value
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__size_function__WpntArray__waypoints,  // size() function pointer
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__get_const_function__WpntArray__waypoints,  // get_const(index) function pointer
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__get_function__WpntArray__waypoints,  // get(index) function pointer
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__fetch_function__WpntArray__waypoints,  // fetch(index, &value) function pointer
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__assign_function__WpntArray__waypoints,  // assign(index, value) function pointer
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__resize_function__WpntArray__waypoints  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_members = {
  "global_planner__msg",  // message namespace
  "WpntArray",  // message name
  1,  // number of fields
  sizeof(global_planner__msg__WpntArray),
  global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_member_array,  // message members
  global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_init_function,  // function to initialize message memory (memory has to be allocated)
  global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_type_support_handle = {
  0,
  &global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_global_planner
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, global_planner, msg, WpntArray)() {
  global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_member_array[0].members_ =
    ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, global_planner, msg, Wpnt)();
  if (!global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_type_support_handle.typesupport_identifier) {
    global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &global_planner__msg__WpntArray__rosidl_typesupport_introspection_c__WpntArray_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
