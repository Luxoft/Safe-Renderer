cmake_minimum_required(VERSION 2.8.12)

project("communication")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED COMMUNICATION_PREFIX)
    set(COMMUNICATION_PREFIX "${ENGINE_PREFIX}/communication")
endif()

if(NOT DEFINED COMMUNICATION_BASE)
    set(COMMUNICATION_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include_directories(
    ${LSRROOT}/pil/api
    ${LSRROOT}/engine/common/api
    ${LSRROOT}/simu/odi/api
    ${COMMUNICATION_BASE}/api
    ${COMMUNICATION_BASE}/src
)

set(COMMUNICATION_HEADERS
    ${COMMUNICATION_BASE}/api/IMsgDispatcher.h
    ${COMMUNICATION_BASE}/api/IMsgReceiver.h
    ${COMMUNICATION_BASE}/api/IMsgTransmitter.h
    ${COMMUNICATION_BASE}/api/IFuConnection.h
    ${COMMUNICATION_BASE}/api/InputStream.h
    ${COMMUNICATION_BASE}/api/MessageHeader.h
    ${COMMUNICATION_BASE}/api/OutputStream.h
)

set(COMMUNICATION_SOURCES
    ${COMMUNICATION_BASE}/src/InputStream.cpp
    ${COMMUNICATION_BASE}/src/MessageHeader.cpp
    ${COMMUNICATION_BASE}/src/OutputStream.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${COMMUNICATION_HEADERS}
    ${COMMUNICATION_SOURCES}
)

install(DIRECTORY api
    DESTINATION "${COMMUNICATION_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${COMMUNICATION_PREFIX}"
)

if (UNIT_TESTS)
    add_subdirectory(test)
endif()
