#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "simple::simple_msgs" for configuration "Release"
set_property(TARGET simple::simple_msgs APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(simple::simple_msgs PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsimple_msgs.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS simple::simple_msgs )
list(APPEND _IMPORT_CHECK_FILES_FOR_simple::simple_msgs "${_IMPORT_PREFIX}/lib/libsimple_msgs.a" )

# Import target "simple::simple" for configuration "Release"
set_property(TARGET simple::simple APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(simple::simple PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsimple.dylib"
  IMPORTED_SONAME_RELEASE "@rpath/libsimple.dylib"
  )

list(APPEND _IMPORT_CHECK_TARGETS simple::simple )
list(APPEND _IMPORT_CHECK_FILES_FOR_simple::simple "${_IMPORT_PREFIX}/lib/libsimple.dylib" )

# Import target "simple::simple-static" for configuration "Release"
set_property(TARGET simple::simple-static APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(simple::simple-static PROPERTIES
  IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libsimple-static.a"
  )

list(APPEND _IMPORT_CHECK_TARGETS simple::simple-static )
list(APPEND _IMPORT_CHECK_FILES_FOR_simple::simple-static "${_IMPORT_PREFIX}/lib/libsimple-static.a" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
