cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

if(NOT DEFINED DISPLAY_BASE)
    set(DISPLAY_BASE "${POPULUSENGINE}/display")
    message(STATUS "--> DISPLAY_BASE: ${DISPLAY_BASE}")
endif()

include_directories(
    ${POPULUSROOT}/pgl/api
    ${POPULUSENGINE}/common/api
    ${POPULUSENGINE}/database/api
    ${POPULUSENGINE}/database/api/gen
    ${DISPLAY_BASE}/api
    ${DISPLAY_BASE}/src
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

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
