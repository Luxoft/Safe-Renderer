cmake_minimum_required(VERSION 2.8.12)

project("pgl")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED PGL_PREFIX)
    set(PGL_PREFIX "pgl")
endif()

if(NOT DEFINED PGL_BASE)
    set(PGL_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include_directories(
    ${PGL_BASE}/api
)

if(NOT DEFINED PGL)
    message(WARNING "pgl implementation not defined, using dummy.")
    set(PGL "dummy")
endif()

if (${PGL} STREQUAL "sw_win32")
    # SW Renderer, win32 window
    set(PGL_SOURCES
        ${PGL_BASE}/src/sw/pgl_assert.h
        ${PGL_BASE}/src/sw/pgl_sw_renderer.h
        ${PGL_BASE}/src/sw/pgl_sw_renderer_glue.h
        ${PGL_BASE}/src/sw/pgl_win32.h
        ${PGL_BASE}/src/sw/pgl_sw_renderer.c
        ${PGL_BASE}/src/sw/pgl_sw_renderer_glue.c
        ${PGL_BASE}/src/sw/pgl_win32.c
    )
elseif(${PGL} STREQUAL "egl_x11")
    # GLES2.0 Renderer, x11 window
    include_directories(
        ${POPULUSROOT}/3rdparty/opengl
    )
    set(PGL_SOURCES
        ${PGL_BASE}/src/gles2/pgl.c
    )
    set(PGL_LIBS
        EGL GLESv2 X11
    )
elseif(${PGL} STREQUAL "dummy")
    # dummy implementation
    set(PGL_SOURCES
        ${PGL_BASE}/src/dummy/pgl.c
        ${PGL_BASE}/src/dummy/crc32.h
    )
else()
    message(FATAL_ERROR "pgl implementation not found: ${PGL}")
endif()

set(PGL_HEADERS
    ${PGL_BASE}/api/pgl.h
)

# pgl library for unit tests
add_library(pglMock
    ${PGL_HEADERS}
    ${PGL_BASE}/src/dummy/pgl.c
    ${PGL_BASE}/src/dummy/crc32.h
)

add_library(${PROJECT_NAME} #SHARED
    ${PGL_HEADERS}
    ${PGL_SOURCES}
)

target_link_libraries(${PROJECT_NAME}
    ${PGL_LIBS}
)

# install(FILES Pgl.cmake
#     DESTINATION "${PGL_PREFIX}"
# )

install(DIRECTORY api
    DESTINATION "${PGL_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${PGL_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
