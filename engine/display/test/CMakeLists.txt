include(GoogleTest)

add_library(gilMock
    MockGIL.cpp
    MockGIL.h
)

GUNITTEST(NAME "display"
    LIBS ${GUNITTEST_DISPLAY_LIBS} ${ENGINE_PROJECT_NAME} pilSample gilMock
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    FILES TextureTest.cpp DisplayTest.cpp TelltalesDisplayTest.cpp
)

# add library with mock implementation.
# will be used in other components tests
include_directories(
    ${LSRROOT}/gil/api
    ${LSRENGINE}/lsr/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${LSRENGINE}/framehandler/api
    ${DISPLAY_BASE}/api
    ${DISPLAY_BASE}/src
)

