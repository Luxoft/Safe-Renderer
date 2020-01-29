cmake_minimum_required(VERSION 2.8.12)

project("display")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED DISPLAY_PREFIX)
    set(DISPLAY_PREFIX "${ENGINE_PREFIX}/display")
endif()

if(NOT DEFINED DISPLAY_BASE)
    set(DISPLAY_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${LSRROOT}/gil/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${DISPLAY_BASE}/api
    ${DISPLAY_BASE}/src
    ${HMI_PROJECT_PATH}
)

set(DISPLAY_HEADERS
    ${DISPLAY_BASE}/api/Canvas.h
    ${DISPLAY_BASE}/api/DisplayManager.h
    ${DISPLAY_BASE}/api/Texture.h
    ${DISPLAY_BASE}/api/TextureCache.h
    ${DISPLAY_BASE}/api/WindowCanvas.h
    ${DISPLAY_BASE}/api/WindowDefinition.h
)

set(DISPLAY_SOURCES
    ${DISPLAY_BASE}/src/Canvas.cpp
    ${DISPLAY_BASE}/src/DisplayManager.cpp
    ${DISPLAY_BASE}/src/Texture.cpp
    ${DISPLAY_BASE}/src/TextureCache.cpp
    ${DISPLAY_BASE}/src/WindowCanvas.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${DISPLAY_HEADERS}
    ${DISPLAY_SOURCES}
)

install(DIRECTORY api
    DESTINATION "${DISPLAY_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${DISPLAY_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
