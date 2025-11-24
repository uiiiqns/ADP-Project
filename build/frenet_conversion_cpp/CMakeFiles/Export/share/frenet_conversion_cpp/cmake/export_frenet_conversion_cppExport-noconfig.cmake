#----------------------------------------------------------------
# Generated CMake target import file.
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "frenet_conversion_cpp::frenet_conversion_cpp" for configuration ""
set_property(TARGET frenet_conversion_cpp::frenet_conversion_cpp APPEND PROPERTY IMPORTED_CONFIGURATIONS NOCONFIG)
set_target_properties(frenet_conversion_cpp::frenet_conversion_cpp PROPERTIES
  IMPORTED_LOCATION_NOCONFIG "${_IMPORT_PREFIX}/lib/libfrenet_conversion_cpp.so"
  IMPORTED_SONAME_NOCONFIG "libfrenet_conversion_cpp.so"
  )

list(APPEND _IMPORT_CHECK_TARGETS frenet_conversion_cpp::frenet_conversion_cpp )
list(APPEND _IMPORT_CHECK_FILES_FOR_frenet_conversion_cpp::frenet_conversion_cpp "${_IMPORT_PREFIX}/lib/libfrenet_conversion_cpp.so" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
