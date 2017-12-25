cmake_minimum_required(VERSION 2.8.12)

project("framehandler")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED FRAMEHANDLER_PREFIX)
    set(FRAMEHANDLER_PREFIX "framehandler")
endif()

if(NOT DEFINED FRAMEHANDLER_BASE)
    set(FRAMEHANDLER_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(FrameHandler.cmake)

add_library(${PROJECT_NAME} OBJECT
    ${FRAMEHANDLER_HEADERS}
    ${FRAMEHANDLER_SOURCES}
)

install(FILES FrameHandler.cmake
    DESTINATION "${FRAMEHANDLER_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${FRAMEHANDLER_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${FRAMEHANDLER_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
