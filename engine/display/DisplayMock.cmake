cmake_minimum_required(VERSION 2.8.12)

include_directories(
    ${LSRROOT}/gil/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${DISPLAY_BASE}/api
    ${DISPLAY_BASE}/src
)

set(DISPLAYMOCK_HEADERS
    ${DISPLAY_HEADERS}
    ${DISPLAY_BASE}/test/DisplayAccessor.h
)

set(DISPLAYMOCK_SOURCES
    ${DISPLAY_BASE}/src/DisplayManager.cpp
    ${DISPLAY_BASE}/src/Texture.cpp
    ${DISPLAY_BASE}/src/TextureCache.cpp
    ${DISPLAY_BASE}/src/WindowCanvas.cpp
    ${DISPLAY_BASE}/test/CanvasMock.cpp
)
