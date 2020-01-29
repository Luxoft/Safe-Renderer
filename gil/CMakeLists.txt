cmake_minimum_required(VERSION 2.8.12)

project("gilSample")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED GIL_PREFIX)
    set(GIL_PREFIX "gil")
endif()

if(NOT DEFINED GIL_BASE)
    set(GIL_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include_directories(
    ${GIL_BASE}/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/database/api
    ${HMI_PROJECT_PATH}
)

if(SIMULATION OR UNIT_TESTS)
    if("${GIL}" STREQUAL "${GIL_WIN32_SW}")
        # SW Renderer, win32 window
        include_directories(
            ${LSRROOT}/pil/api
        )
        set(GIL_SOURCES
            ${GIL_BASE}/src/sw/gil_assert.h
            ${GIL_BASE}/src/sw/gil_assert.c
            ${GIL_BASE}/src/sw/gil_sw_renderer.h
            ${GIL_BASE}/src/sw/gil_sw_renderer_glue.h
            ${GIL_BASE}/src/sw/gil_win32.h
            ${GIL_BASE}/src/sw/gil_sw_renderer.c
            ${GIL_BASE}/src/sw/gil_sw_renderer_glue.c
            ${GIL_BASE}/src/sw/gil_win32.c
        )
    elseif("${GIL}" STREQUAL "${GIL_EGL_X11}")
        # GLES2.0 Renderer, x11 window
        include_directories(
            ${LSRROOT}/3rdparty/opengl
        )
        set(GIL_SOURCES
            ${GIL_BASE}/src/gles2/gil.c
        )
        set(GIL_LIBS
            EGL GLESv2 X11
        )
    elseif("${GIL}" STREQUAL "${GIL_EGL_IMX6}")
        # GLES2.0 Renderer,
        include_directories(
            ${LSRROOT}/3rdparty/opengl
        )
        set(GIL_SOURCES
            ${GIL_BASE}/src/gles2/gil_imx6_vivante.c
            ${GIL_BASE}/src/gles2/imx6_demonstartor_constants.h
        )
        set(GIL_LIBS
            EGL GLESv2
        )
    elseif("${GIL}" STREQUAL "${GIL_FPGA}")
        # fpga for arp implementation
        include_directories(
            ${LSRROOT}/pil/api
        )
        set(GIL_SOURCES
            ${GIL_BASE}/src/sw/gil_assert.h
            ${GIL_BASE}/src/sw/gil_assert.c
            ${GIL_BASE}/src/sw/gil_sw_renderer.h
            ${GIL_BASE}/src/sw/gil_sw_renderer_glue.h
            ${GIL_BASE}/src/sw/gil_sw_renderer.c
            ${GIL_BASE}/src/sw/gil_sw_renderer_glue.c
            ${GIL_BASE}/src/sw/gil_memory.c
        )
    else()
         # dummy implementation
        set(GIL_SOURCES
            ${GIL_BASE}/src/dummy/gil.cpp
            ${GIL_BASE}/src/dummy/crc32.h
        )
    endif()
endif()

if(SIMULATION OR UNIT_TESTS)
    if("${GIL}" STREQUAL "${GIL_EGL_IMX6}")
        set(GIL_HEADERS
            ${GIL_BASE}/api/gil.h
            ${GIL_BASE}/api/imx6_rendering_configuration.h
        )
    elseif("${GIL}" STREQUAL "${GIL_FPGA}")
        set(GIL_HEADERS
            ${GIL_BASE}/api/gil.h
            ${GIL_BASE}/api/gil_sw_memory_configuration.h
        )
    else()
        set(GIL_HEADERS
            ${GIL_BASE}/api/gil.h
        )
    endif()
elseif()
else()
    set(GIL_HEADERS
        ${GIL_BASE}/api/gil.h
    )
endif()

if(SIMULATION OR UNIT_TESTS)
    add_library(${PROJECT_NAME} #SHARED
        ${GIL_HEADERS}
        ${GIL_SOURCES}
    )

    target_link_libraries(${PROJECT_NAME}
        ${GIL_LIBS}
    )

    # install(FILES Gil.cmake
    #     DESTINATION "${GIL_PREFIX}"
    # )

    install(DIRECTORY api
        DESTINATION "${GIL_PREFIX}"
    )

    install(DIRECTORY src
        DESTINATION "${GIL_PREFIX}"
    )

    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${GIL_PREFIX}
        LIBRARY DESTINATION ${GIL_PREFIX}
        ARCHIVE DESTINATION ${GIL_PREFIX}
    )

    if(UNIT_TESTS)
        add_subdirectory(test)
    endif()
else()
    install(FILES ${GIL_HEADERS}
        DESTINATION "${GIL_PREFIX}/api"
    )
endif()

