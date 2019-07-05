cmake_minimum_required(VERSION 2.8.12)

project("odi")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED ODI_PREFIX)
    set(ODI_PREFIX "${ENGINE_PREFIX}/odi")
endif()

if(NOT DEFINED ODI_BASE)
    set(ODI_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(Odi.cmake)

add_library(${PROJECT_NAME} OBJECT
   ${ODI_HEADERS}
   ${ODI_SOURCES}
)

install(FILES Odi.cmake
    DESTINATION "${ODI_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${ODI_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${ODI_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
