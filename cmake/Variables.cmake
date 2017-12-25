#
# Variables which could be set outside cmake.
#

if(NOT DEFINED BUILD_SHARED_LIBS)
    option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
endif()
message(STATUS "--> BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

if(NOT DEFINED UNIT_TESTS)
    option(UNIT_TESTS "Building unit tests" OFF)
endif()
message(STATUS "--> UNIT_TESTS: ${UNIT_TESTS}")

#
# Compiler configuration
#

if(NOT DEFINED COVERAGE)
    option(COVERAGE "Enables coverage" OFF)
endif()
message(STATUS "--> COVERAGE: ${COVERAGE}")

if(NOT DEFINED COMPILER_WARNING_IS_ERROR)
    option(COMPILER_WARNING_IS_ERROR "Enables warnings to be treated as errors" ON)
endif()
message(STATUS "--> COMPILER_WARNING_IS_ERROR: ${COMPILER_WARNING_IS_ERROR}")

#
# Linker configuration
#

if(NOT DEFINED FORCE_LINKER_INCREMENTAL_LINKING)
    option(FORCE_LINKER_INCREMENTAL_LINKING "Forces the linker to use incremental linking" OFF)
endif()
message(STATUS "--> FORCE_LINKER_INCREMENTAL_LINKING: ${FORCE_LINKER_INCREMENTAL_LINKING}")

#
# Internal variables
#
if(DEFINED PLATFORM_CMAKE_CXX_FLAGS_RELEASE)
    set(CMAKE_CXX_FLAGS_RELEASE ${PLATFORM_CMAKE_CXX_FLAGS_RELEASE})
    message(STATUS "--> CXX flag (release): ${CMAKE_CXX_FLAGS_RELEASE}")
endif()
if(DEFINED PLATFORM_CMAKE_CXX_FLAGS_DEBUG)
    set(CMAKE_CXX_FLAGS_DEBUG ${PLATFORM_CMAKE_CXX_FLAGS_DEBUG})
    message(STATUS "--> CXX flag (debug): ${PLATFORM_CMAKE_CXX_FLAGS_DEBUG}")
endif()

if(NOT DEFINED POPULUSROOT)
    set(POPULUSROOT "${CMAKE_CURRENT_LIST_DIR}/..")
    message(STATUS "--> POPULUSROOT: ${POPULUSROOT}")
endif()

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${POPULUSROOT}/engine")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()
