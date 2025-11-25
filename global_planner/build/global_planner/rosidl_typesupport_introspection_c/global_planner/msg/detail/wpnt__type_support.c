// generated from rosidl_typesupport_introspection_c/resource/idl__type_support.c.em
// with input from global_planner:msg/Wpnt.idl
// generated code does not contain a copyright notice

#include <stddef.h>
#include "global_planner/msg/detail/wpnt__rosidl_typesupport_introspection_c.h"
#include "global_planner/msg/rosidl_typesupport_introspection_c__visibility_control.h"
#include "rosidl_typesupport_introspection_c/field_types.h"
#include "rosidl_typesupport_introspection_c/identifier.h"
#include "rosidl_typesupport_introspection_c/message_introspection.h"
#include "global_planner/msg/detail/wpnt__functions.h"
#include "global_planner/msg/detail/wpnt__struct.h"


#ifdef __cplusplus
extern "C"
{
#endif

void global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_init_function(
  void * message_memory, enum rosidl_runtime_c__message_initialization _init)
{
  // TODO(karsten1987): initializers are not yet implemented for typesupport c
  // see https://github.com/ros2/ros2/issues/397
  (void) _init;
  global_planner__msg__Wpnt__init(message_memory);
}

void global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_fini_function(void * message_memory)
{
  global_planner__msg__Wpnt__fini(message_memory);
}

static rosidl_typesupport_introspection_c__MessageMember global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_member_array[5] = {
  {
    "x",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner__msg__Wpnt, x),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "y",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner__msg__Wpnt, y),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "yaw",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner__msg__Wpnt, yaw),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "curvature",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner__msg__Wpnt, curvature),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  },
  {
    "velocity",  // name
    rosidl_typesupport_introspection_c__ROS_TYPE_FLOAT,  // type
    0,  // upper bound of string
    NULL,  // members of sub message
    false,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(global_planner__msg__Wpnt, velocity),  // bytes offset in struct
    NULL,  // default value
    NULL,  // size() function pointer
    NULL,  // get_const(index) function pointer
    NULL,  // get(index) function pointer
    NULL,  // fetch(index, &value) function pointer
    NULL,  // assign(index, value) function pointer
    NULL  // resize(index) function pointer
  }
};

static const rosidl_typesupport_introspection_c__MessageMembers global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_members = {
  "global_planner__msg",  // message namespace
  "Wpnt",  // message name
  5,  // number of fields
  sizeof(global_planner__msg__Wpnt),
  global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_member_array,  // message members
  global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_init_function,  // function to initialize message memory (memory has to be allocated)
  global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_fini_function  // function to terminate message instance (will not free memory)
};

// this is not const since it must be initialized on first access
// since C does not allow non-integral compile-time constants
static rosidl_message_type_support_t global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_type_support_handle = {
  0,
  &global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_members,
  get_message_typesupport_handle_function,
};

ROSIDL_TYPESUPPORT_INTROSPECTION_C_EXPORT_global_planner
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_c, global_planner, msg, Wpnt)() {
  if (!global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_type_support_handle.typesupport_identifier) {
    global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_type_support_handle.typesupport_identifier =
      rosidl_typesupport_introspection_c__identifier;
  }
  return &global_planner__msg__Wpnt__rosidl_typesupport_introspection_c__Wpnt_message_type_support_handle;
}
#ifdef __cplusplus
}
#endif
