cmake_minimum_required(VERSION 2.8.12)

project("common")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED COMMON_PREFIX)
    set(COMMON_PREFIX "${ENGINE_PREFIX}/common")
endif()

if(NOT DEFINED COMMON_BASE)
    set(COMMON_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(Common.cmake)

add_library(${PROJECT_NAME} OBJECT
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
)

install(FILES Common.cmake
    DESTINATION ${COMMON_PREFIX}
)

install(DIRECTORY api
    DESTINATION ${COMMON_PREFIX}
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
