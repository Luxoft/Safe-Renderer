cmake_minimum_required(VERSION 2.8.12)

project("lsr")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED LSR_PREFIX)
    set(LSR_PREFIX "${ENGINE_PREFIX}/lsr")
endif()

if(NOT DEFINED APP_BASE)
    set(LSR_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()


include_directories(
    ${LSRROOT}/pil/api
    ${LSRROOT}/gil/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/odi/api
    ${LSRENGINE}/communication/api
    ${LSRENGINE}/communication/src #TODO
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${LSRENGINE}/framehandler/api
    ${LSRENGINE}/datahandler/api
    ${LSRENGINE}/display/api
    ${LSR_BASE}/api
    ${LSR_BASE}/src
)

set(LSR_HEADERS
    ${LSR_BASE}/api/lsr.h
)

set(LSR_SOURCES
    ${LSR_BASE}/src/lsr.cpp
    ${LSR_BASE}/src/Engine.h
    ${LSR_BASE}/src/Engine.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${LSR_HEADERS}
    ${LSR_SOURCES}
)

install(DIRECTORY api
    DESTINATION "${LSR_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${LSR_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()

