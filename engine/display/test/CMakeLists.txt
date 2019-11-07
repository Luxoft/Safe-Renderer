include(GoogleTest)

GUNITTEST(NAME "display_gilSample"
    LIBS ${GUNITTEST_DISPLAY_LIBS} ${ENGINE_PROJECT_NAME} pilSample gilSample
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    FILES DisplayTest.cpp ${LSRROOT}/test/database/Telltales/Output/Telltales.cpp
)

GUNITTEST(NAME "display_gilMock"
    LIBS ${GUNITTEST_DISPLAY_LIBS} ${ENGINE_PROJECT_NAME} pilSample
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    FILES TextureTest.cpp MockGIL.h MockGIL.cpp
)

# add library with mock implementation.
# will be used in other components tests
include_directories(
    ${LSRROOT}/gil/api
    ${LSRENGINE}/lsr/api
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


add_library(displaymock OBJECT
    ${DISPLAYMOCK_HEADERS}
    ${DISPLAYMOCK_SOURCES}
)
