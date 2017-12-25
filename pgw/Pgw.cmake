cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

if(NOT DEFINED PGW_BASE)
    set(PGW_BASE "${POPULUSENGINE}/pgw")
    message(STATUS "--> PGW_BASE: ${PGW_BASE}")
endif()

include_directories(
    ${PGW_BASE}/api
)

set(PGW_HEADERS
    ${PGW_BASE}/api/pgw.h
)

set(PGW_HEADERS
    ${PGW_HEADERS}
    ${PGW_BASE}/src/sample/Circbuf.h
    ${PGW_BASE}/src/sample/pgw_config.h
    ${PGW_BASE}/src/sample/pgw_platform.h
)

set(PGW_SOURCES
    ${PGW_BASE}/src/sample/pgw.cpp
)


if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(PGW_SOURCES
        ${PGW_SOURCES}
        ${PGW_BASE}/src/sample/pgw_platform_win32.c
    )
    set(PGW_LIBS
        winmm
    )
else()
    set(PGW_SOURCES
        ${PGW_SOURCES}
        ${PGW_BASE}/src/sample/pgw_platform_linux.c
    )
endif()

