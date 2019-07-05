#
# Variables which could be set outside cmake.
#

if(NOT DEFINED BUILD_SHARED_LIBS)
    option(BUILD_SHARED_LIBS "Build Shared Libraries" OFF)
endif()
message(STATUS "--> BUILD_SHARED_LIBS: ${BUILD_SHARED_LIBS}")

if(NOT DEFINED UNIT_TESTS)
    option(UNIT_TESTS "Building unit tests" OFF)
    set(UNIT_TESTS OFF)
endif()
message(STATUS "--> UNIT_TESTS: ${UNIT_TESTS}")

#
# Compiler configuration
#

if(NOT DEFINED COVERAGE)
    option(COVERAGE "Enables coverage" OFF)
    set(COVERAGE OFF)
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
# Install path
#
message(STATUS "--> Installation path: ${CMAKE_INSTALL_PREFIX}")

#
# Internal variables
#
if(NOT DEFINED LSRROOT)
    set(LSRROOT "${CMAKE_CURRENT_LIST_DIR}/..")
    message(STATUS "--> LSRROOT: ${LSRROOT}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${LSRROOT}/engine")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

#
# GIL version
#
set(GIL_DUMMY "dummy" CACHE STRING "")
set(GIL_WIN32_SW "sw_win32" CACHE STRING "")
set(GIL_EGL_X11 "egl_x11" CACHE STRING "")
set(GIL_EGL_IMX6 "egl_imx6" CACHE STRING "")
set(GIL_FPGA "egl_fpga" CACHE STRING "")

if(NOT DEFINED GIL)
    set(GIL ${GIL_DUMMY} CACHE STRING "GIL Implementation")
    set_property(CACHE GIL PROPERTY STRINGS ${GIL_DUMMY}
                                            ${GIL_WIN32_SW}
                                            ${GIL_EGL_X11}
                                            ${GIL_EGL_IMX6}
                                            ${GIL_FPGA})
endif()

message(STATUS "--> GIL: ${GIL}")

#
# Simu building
#
if(NOT DEFINED SIMULATION)
    option(SIMULATION "Building simulation project" OFF)
    set(SIMULATION OFF)
endif()
message(STATUS "--> SIMULATION: ${SIMULATION}")
