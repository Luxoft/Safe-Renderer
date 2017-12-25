add_definitions(-DWIN32)

delete_compilers_flags("/M[DT]d?")

#
# We can't set CMAKE_C_FLAGS like this in the following if
# set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} /MD")
# because some libs (i.e. gtest) use only this variable and
# ignore debug and release versions. It leads to conflict:
# libs linked with LIBCMT.lib (/MT) conflict with other linked with LIBCMTD.lib (/MTd)
# Also there can be a conflict if in DEBUG mode the suffix 'd' won't be set (ex. /MD).
# In such case some libs would linked with release instance of LIBCMT, some - with debug: LIBCMTD.
# So, we set flags independently.
#

if(BUILD_SHARED_LIBS)
    set_separate_compiler_flags("/MD" "/MDd" "/MD" "/MD")
else()
    set_separate_compiler_flags("/MT" "/MTd" "/MT" "/MT")
endif()

set_compiler_flags("/W3")

if(COMPILER_WARNING_IS_ERROR)
    set_compiler_flags("/WX")
    message(STATUS "Compiler warnings are treated as errors")
else()
    message(WARNING "COMPILER_WARNING_IS_ERROR is DISABLED: Compiler warnings are NOT treated as errors!")
endif()

if(NOT DEFINED CPACK_GENERATOR)
    set(CPACK_GENERATOR "ZIP")
endif()
