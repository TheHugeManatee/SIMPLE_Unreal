#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "simple::simple_msgs" for configuration "Debug"
set_property(TARGET simple::simple_msgs APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(simple::simple_msgs PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/simple_msgs-d.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS simple::simple_msgs )
list(APPEND _IMPORT_CHECK_FILES_FOR_simple::simple_msgs "${_IMPORT_PREFIX}/lib/simple_msgs-d.lib" )

# Import target "simple::simple" for configuration "Debug"
set_property(TARGET simple::simple APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(simple::simple PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/simple-d.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/simple-d.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS simple::simple )
list(APPEND _IMPORT_CHECK_FILES_FOR_simple::simple "${_IMPORT_PREFIX}/lib/simple-d.lib" "${_IMPORT_PREFIX}/bin/simple-d.dll" )

# Import target "simple::simple-static" for configuration "Debug"
set_property(TARGET simple::simple-static APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(simple::simple-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/simple-static-d.lib"
  )

list(APPEND _IMPORT_CHECK_TARGETS simple::simple-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_simple::simple-static "${_IMPORT_PREFIX}/lib/simple-static-d.lib" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
