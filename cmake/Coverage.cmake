
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    message(FATAL_ERROR "No coverage support for Clang")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set_compiler_flags("-fprofile-arcs -ftest-coverage -fno-inline -fno-default-inline -fno-exceptions")

elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
    message(FATAL_ERROR "No coverage support for MSVC")

else()
    message(FATAL_ERROR "Unknown compiler for coverage")
endif()
