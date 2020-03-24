cmake_minimum_required(VERSION 2.8.12)

project("datahandler")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED DATAHANDLER_PREFIX)
    set(DATAHANDLER_PREFIX "${ENGINE_PREFIX}/datahandler")
endif()

if(NOT DEFINED DATAHANDLER_BASE)
    set(DATAHANDLER_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${LSRENGINE}/common/api
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${LSRROOT}/pil/api
    ${DATAHANDLER_BASE}/api
    ${DATAHANDLER_BASE}/src
    ${HMI_PROJECT_PATH}
)

set(DATAHANDLER_HEADERS
    ${DATAHANDLER_BASE}/api/DataHandler.h
    ${DATAHANDLER_BASE}/api/DataStatus.h
    ${DATAHANDLER_BASE}/api/IDataHandler.h
    ${DATAHANDLER_BASE}/api/Number.h
)

set(DATAHANDLER_SOURCES
    ${DATAHANDLER_BASE}/src/DataHandler.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${DATAHANDLER_HEADERS}
    ${DATAHANDLER_SOURCES}
)

install(DIRECTORY api
    DESTINATION "${DATAHANDLER_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${DATAHANDLER_PREFIX}"
)

if (UNIT_TESTS)
    add_subdirectory(test)
endif()
