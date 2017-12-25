cmake_minimum_required(VERSION 2.8.12)

project("display")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED DISPLAY_PREFIX)
    set(DISPLAY_PREFIX "display")
endif()

if(NOT DEFINED DISPLAY_BASE)
    set(DISPLAY_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(Display.cmake)

add_library(${PROJECT_NAME} OBJECT
    ${DISPLAY_HEADERS}
    ${DISPLAY_SOURCES}
)

if(UNIT_TESTS)
    # add library with mock implementation.
    # will be used in other components tests
    include(DisplayMock.cmake)

    add_library(displaymock OBJECT
        ${DISPLAYMOCK_HEADERS}
        ${DISPLAYMOCK_SOURCES}
    )
endif()

install(FILES Display.cmake
    DESTINATION "${DISPLAY_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${DISPLAY_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${DISPLAY_PREFIX}"
)
