cmake_minimum_required(VERSION 2.8.12)

project("framehandler")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED FRAMEHANDLER_PREFIX)
    set(FRAMEHANDLER_PREFIX "${ENGINE_PREFIX}/framehandler")
endif()

if(NOT DEFINED FRAMEHANDLER_BASE)
    set(FRAMEHANDLER_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${LSRENGINE}/common/api
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${LSRENGINE}/datahandler/api
    ${LSRENGINE}/display/api
    ${LSRENGINE}/lsr/api
    ${LSRROOT}/gil/api
    ${FRAMEHANDLER_BASE}/api
    ${FRAMEHANDLER_BASE}/src
    ${HMI_PROJECT_PATH}
)

set(FRAMEHANDLER_HEADERS
    ${FRAMEHANDLER_BASE}/api/BitmapField.h
    ${FRAMEHANDLER_BASE}/api/Field.h
    ${FRAMEHANDLER_BASE}/api/Frame.h
    ${FRAMEHANDLER_BASE}/api/FrameHandler.h
    ${FRAMEHANDLER_BASE}/api/Panel.h
    ${FRAMEHANDLER_BASE}/api/ReferenceBitmapField.h
    ${FRAMEHANDLER_BASE}/api/Widget.h
    ${FRAMEHANDLER_BASE}/api/Window.h
)

set(FRAMEHANDLER_SOURCES
    ${FRAMEHANDLER_BASE}/src/BitmapField.cpp
    ${FRAMEHANDLER_BASE}/src/Field.cpp
    ${FRAMEHANDLER_BASE}/src/Frame.cpp
    ${FRAMEHANDLER_BASE}/src/FrameHandler.cpp
    ${FRAMEHANDLER_BASE}/src/Panel.cpp
    ${FRAMEHANDLER_BASE}/src/ReferenceBitmapField.cpp
    ${FRAMEHANDLER_BASE}/src/Widget.cpp
    ${FRAMEHANDLER_BASE}/src/Window.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${FRAMEHANDLER_HEADERS}
    ${FRAMEHANDLER_SOURCES}
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
