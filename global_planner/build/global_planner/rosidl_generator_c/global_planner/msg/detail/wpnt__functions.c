// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from global_planner:msg/Wpnt.idl
// generated code does not contain a copyright notice
#include "global_planner/msg/detail/wpnt__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
global_planner__msg__Wpnt__init(global_planner__msg__Wpnt * msg)
{
  if (!msg) {
    return false;
  }
  // x
  // y
  // yaw
  // curvature
  // velocity
  return true;
}

void
global_planner__msg__Wpnt__fini(global_planner__msg__Wpnt * msg)
{
  if (!msg) {
    return;
  }
  // x
  // y
  // yaw
  // curvature
  // velocity
}

bool
global_planner__msg__Wpnt__are_equal(const global_planner__msg__Wpnt * lhs, const global_planner__msg__Wpnt * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // x
  if (lhs->x != rhs->x) {
    return false;
  }
  // y
  if (lhs->y != rhs->y) {
    return false;
  }
  // yaw
  if (lhs->yaw != rhs->yaw) {
    return false;
  }
  // curvature
  if (lhs->curvature != rhs->curvature) {
    return false;
  }
  // velocity
  if (lhs->velocity != rhs->velocity) {
    return false;
  }
  return true;
}

bool
global_planner__msg__Wpnt__copy(
  const global_planner__msg__Wpnt * input,
  global_planner__msg__Wpnt * output)
{
  if (!input || !output) {
    return false;
  }
  // x
  output->x = input->x;
  // y
  output->y = input->y;
  // yaw
  output->yaw = input->yaw;
  // curvature
  output->curvature = input->curvature;
  // velocity
  output->velocity = input->velocity;
  return true;
}

global_planner__msg__Wpnt *
global_planner__msg__Wpnt__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  global_planner__msg__Wpnt * msg = (global_planner__msg__Wpnt *)allocator.allocate(sizeof(global_planner__msg__Wpnt), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(global_planner__msg__Wpnt));
  bool success = global_planner__msg__Wpnt__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
global_planner__msg__Wpnt__destroy(global_planner__msg__Wpnt * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    global_planner__msg__Wpnt__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
global_planner__msg__Wpnt__Sequence__init(global_planner__msg__Wpnt__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  global_planner__msg__Wpnt * data = NULL;

  if (size) {
    data = (global_planner__msg__Wpnt *)allocator.zero_allocate(size, sizeof(global_planner__msg__Wpnt), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = global_planner__msg__Wpnt__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        global_planner__msg__Wpnt__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
global_planner__msg__Wpnt__Sequence__fini(global_planner__msg__Wpnt__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      global_planner__msg__Wpnt__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

global_planner__msg__Wpnt__Sequence *
global_planner__msg__Wpnt__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  global_planner__msg__Wpnt__Sequence * array = (global_planner__msg__Wpnt__Sequence *)allocator.allocate(sizeof(global_planner__msg__Wpnt__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = global_planner__msg__Wpnt__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
global_planner__msg__Wpnt__Sequence__destroy(global_planner__msg__Wpnt__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    global_planner__msg__Wpnt__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
global_planner__msg__Wpnt__Sequence__are_equal(const global_planner__msg__Wpnt__Sequence * lhs, const global_planner__msg__Wpnt__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!global_planner__msg__Wpnt__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
global_planner__msg__Wpnt__Sequence__copy(
  const global_planner__msg__Wpnt__Sequence * input,
  global_planner__msg__Wpnt__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(global_planner__msg__Wpnt);
    rcutils_allocator_t allocator = rcutils_get_default_allocator();
    global_planner__msg__Wpnt * data =
      (global_planner__msg__Wpnt *)allocator.reallocate(
      output->data, allocation_size, allocator.state);
    if (!data) {
      return false;
    }
    // If reallocation succeeded, memory may or may not have been moved
    // to fulfill the allocation request, invalidating output->data.
    output->data = data;
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!global_planner__msg__Wpnt__init(&output->data[i])) {
        // If initialization of any new item fails, roll back
        // all previously initialized items. Existing items
        // in output are to be left unmodified.
        for (; i-- > output->capacity; ) {
          global_planner__msg__Wpnt__fini(&output->data[i]);
        }
        return false;
      }
    }
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!global_planner__msg__Wpnt__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
