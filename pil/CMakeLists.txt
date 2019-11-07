cmake_minimum_required(VERSION 2.8.12)

project("pilSample")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED PIL_PREFIX)
    set(PIL_PREFIX "pil")
endif()

if(NOT DEFINED PIL_BASE)
    set(PIL_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${PIL_BASE}/api
)

if(SIMULATION OR UNIT_TESTS)
    set(PIL_HEADERS
        ${PIL_BASE}/api/pil.h
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


if(SIMULATION OR UNIT_TESTS)
    add_library(${PROJECT_NAME}
        ${PIL_HEADERS}
        ${PIL_SOURCES}
    )

    target_link_libraries(${PROJECT_NAME} ${PIL_LIBS})

    install(DIRECTORY api
        DESTINATION "${PIL_PREFIX}"
    )

    install(DIRECTORY src
        DESTINATION "${PIL_PREFIX}"
    )

    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${PIL_PREFIX}
        LIBRARY DESTINATION ${PIL_PREFIX}
        ARCHIVE DESTINATION ${PIL_PREFIX}
    )
else()
    install(FILES ${PIL_HEADERS}
        DESTINATION "${PIL_PREFIX}/api"
    )
endif()


