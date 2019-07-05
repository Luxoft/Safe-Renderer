cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

if(NOT DEFINED PIL_BASE)
    set(PIL_BASE "${LSRENGINE}/pil")
    message(STATUS "--> PIL_BASE: ${PIL_BASE}")
endif()

include_directories(
    ${PIL_BASE}/api
)

if(SIMULATION OR UNIT_TESTS)
    set(PIL_HEADERS
        ${PIL_BASE}/api/pil.h
        ${PIL_BASE}/src/sample/Circbuf.h
        ${PIL_BASE}/src/sample/pil_config.h
        ${PIL_BASE}/src/sample/pil_platform.h
    )

    set(PIL_SOURCES
        ${PIL_BASE}/src/sample/pil.cpp
    )

    if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        set(PIL_SOURCES
            ${PIL_SOURCES}
            ${PIL_BASE}/src/sample/pil_platform_win32.c
        )
        set(PIL_LIBS
            winmm
        )
    elseif(${CMAKE_SYSTEM_NAME} MATCHES "ARP")
        set(PIL_SOURCES
            ${PIL_SOURCES}
            ${PIL_BASE}/src/sample/pil_platform_arp.c
        )
        set(PIL_LIBS
            winmm
        )
    else()
        set(PIL_SOURCES
            ${PIL_SOURCES}
            ${PIL_BASE}/src/sample/pil_platform_linux.c
        )
    endif()
elseif()
    # in case of release installation
    set(PIL_HEADERS
        ${PIL_BASE}/api/pil.h
    )
endif()
