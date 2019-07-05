cmake_minimum_required(VERSION 2.8.12)

project("communication")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED COMMUNICATION_PREFIX)
    set(COMMUNICATION_PREFIX "${ENGINE_PREFIX}/communication")
endif()

if(NOT DEFINED COMMUNICATION_BASE)
    set(COMMUNICATION_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(Communication.cmake)

add_library(${PROJECT_NAME} OBJECT
    ${COMMUNICATION_HEADERS}
    ${COMMUNICATION_SOURCES}
)

install(FILES Communication.cmake
    DESTINATION "${COMMUNICATION_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${COMMUNICATION_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${COMMUNICATION_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
