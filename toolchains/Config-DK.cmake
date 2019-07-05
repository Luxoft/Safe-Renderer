set(DK_ROOT "$ENV{DK_ROOT}")
file(TO_CMAKE_PATH ${DK_ROOT} DK_ROOT)

if(DK_ROOT)
	message(STATUS "DK_ROOT at ${DK_ROOT}")
else()
	message(FATAL_ERROR "Undefined DK_ROOT env var.")
endif()

set(CMAKE_MODULE_PATH "${DK_ROOT}/cmake" ${CMAKE_MODULE_PATH})
find_package(DK REQUIRED)
