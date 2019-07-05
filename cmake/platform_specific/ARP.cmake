# force -O3 and -DNDEBUG flags for all CMAKE_BUILD_TYPE:RelWithDebInfo builds
# LSR releases used to be built with -O3 (CMAKE_BUILD_TYPE:Release)
# switching to RelWithDebInfo made DisplayCanvasTest fail, because it goes with -O2 by default
# RelWithDebInfo default flags: -g -02 (+ -DNDEBUG for recent versions of cmake)

# LSR Linux targets commons
if(NOT DEFINED BIN_INSTALL_DIR)
    set(BIN_INSTALL_DIR "bin" CACHE PATH "Installation directory for executables")
endif()
if(NOT DEFINED LIB_INSTALL_DIR)
    set(LIB_INSTALL_DIR "lib" CACHE PATH "Installation directory for libraries")
endif()

if(NOT DEFINED SYSTEM_INCLUDE_DIR)
    set(SYSTEM_INCLUDE_DIR)
endif()
if(NOT DEFINED SYSTEM_LINK_DIR)
    set(SYSTEM_LINK_DIR)
endif()
if(NOT DEFINED SYSTEM_LIBS)
    set(SYSTEM_LIBS rt)
endif()

add_definitions(-DARP -D_ARP)

if(NOT DEFINED CPACK_GENERATOR)
    set(CPACK_GENERATOR "TGZ")
endif()

# Additional compiler flags
# if(CMAKE_COMPILER_IS_GNUCXX)
#     set_compiler_flags("-Wall")

#     if(COMPILER_WARNING_IS_ERROR)
#         set_compiler_flags("-Werror")
#         message(STATUS "Compiler warnings are treated as errors")
#     else()
#         message(WARNING "COMPILER_WARNING_IS_ERROR is DISABLED: Compiler warnings are NOT treated as errors!")
#     endif()
# endif()
