# set up DK parameters
set(LSR_TARGET_PLATFORM "arp-fpga")
include("${CMAKE_CURRENT_LIST_DIR}/Config-DK.cmake")

# the name of the target operating system
set(CMAKE_SYSTEM_NAME "ARP")
set(CPACK_SYSTEM_NAME "ARP")
# set(TARGETOS "arm-altera-eabi")

# project configuration
set(GIL "egl_fpga")

# set(UNIT_TESTS "OFF")
# set(GOOGLE_BREAKPAD "ON")
# set(GOOGLE_BREAKPAD_UTILS "OFF")
# set(BUILD_FREETYPE "ON" CACHE INTERNAL "" FORCE)
# set(DEVIL_DYNAMIC "ON" CACHE INTERNAL "" FORCE)
# set(DISP_MGR_CONF_OPENGL "opengles2" CACHE STRING "OpenGL version to use, valid is opengl, opengles or opengles2" FORCE)
# set(DISP_MGR_CONF_OPENVG "NONE" CACHE STRING "OpenVG config vailid is NONE or openvg_1.1" FORCE)
# set(DISP_MGR_CONF_APPWINDOW "egl" CACHE STRING "AppWindow" FORCE)

# cmake built-in settings to use find_xxx() functions
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH ${LTIBROOTFS})
