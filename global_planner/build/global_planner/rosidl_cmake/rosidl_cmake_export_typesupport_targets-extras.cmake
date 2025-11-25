# generated from
# rosidl_cmake/cmake/template/rosidl_cmake_export_typesupport_targets.cmake.in

set(_exported_typesupport_targets
  "__rosidl_generator_c:global_planner__rosidl_generator_c;__rosidl_typesupport_fastrtps_c:global_planner__rosidl_typesupport_fastrtps_c;__rosidl_generator_cpp:global_planner__rosidl_generator_cpp;__rosidl_typesupport_fastrtps_cpp:global_planner__rosidl_typesupport_fastrtps_cpp;__rosidl_typesupport_introspection_c:global_planner__rosidl_typesupport_introspection_c;__rosidl_typesupport_c:global_planner__rosidl_typesupport_c;__rosidl_typesupport_introspection_cpp:global_planner__rosidl_typesupport_introspection_cpp;__rosidl_typesupport_cpp:global_planner__rosidl_typesupport_cpp;__rosidl_generator_py:global_planner__rosidl_generator_py")

# populate global_planner_TARGETS_<suffix>
if(NOT _exported_typesupport_targets STREQUAL "")
  # loop over typesupport targets
  foreach(_tuple ${_exported_typesupport_targets})
    string(REPLACE ":" ";" _tuple "${_tuple}")
    list(GET _tuple 0 _suffix)
    list(GET _tuple 1 _target)

    set(_target "global_planner::${_target}")
    if(NOT TARGET "${_target}")
      # the exported target must exist
      message(WARNING "Package 'global_planner' exports the typesupport target '${_target}' which doesn't exist")
    else()
      list(APPEND global_planner_TARGETS${_suffix} "${_target}")
    endif()
  endforeach()
endif()
