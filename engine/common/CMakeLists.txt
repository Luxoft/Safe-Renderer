cmake_minimum_required(VERSION 2.8.12)

project("common")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED COMMON_PREFIX)
    set(COMMON_PREFIX "${ENGINE_PREFIX}/common")
endif()

if(NOT DEFINED COMMON_BASE)
    set(COMMON_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE ${CMAKE_CURRENT_SOURCE_DIR}/..)
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${LSRROOT}/pil/api
    ${COMMON_BASE}/api
)

set(COMMON_HEADERS
    ${COMMON_BASE}/api/Assertion.h
    ${COMMON_BASE}/api/LongTermPtr.h
    ${COMMON_BASE}/api/NodeDataLength.h
    ${COMMON_BASE}/api/NonCopyable.h
    ${COMMON_BASE}/api/Pool.h
    ${COMMON_BASE}/api/PoolMarker.h
    ${COMMON_BASE}/api/PooledObjectFactory.h
    ${COMMON_BASE}/api/LSREngineError.h
    ${COMMON_BASE}/api/LsrTypes.h
    ${COMMON_BASE}/api/Timer.h
)

set(COMMON_SOURCES
    ${COMMON_BASE}/src/Assertion.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${COMMON_HEADERS}
    ${COMMON_SOURCES}
)

install(DIRECTORY api
    DESTINATION ${COMMON_PREFIX}
)

if (UNIT_TESTS)
    add_subdirectory(test)
endif()
