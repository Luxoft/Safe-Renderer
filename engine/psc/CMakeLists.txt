cmake_minimum_required(VERSION 2.8.12)

project("psc")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED PSC_PREFIX)
    set(PSC_PREFIX "psc")
endif()

if(NOT DEFINED APP_BASE)
    set(PSC_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()


include_directories(
    ${POPULUSROOT}/pgw/api
    ${POPULUSROOT}/pgl/api
    ${POPULUSENGINE}/common/api
    ${POPULUSENGINE}/odi/api
    ${POPULUSENGINE}/communication/api
    ${POPULUSENGINE}/communication/src #TODO
    ${POPULUSENGINE}/database/api
    ${POPULUSENGINE}/database/api/gen
    ${POPULUSENGINE}/framehandler/api
    ${POPULUSENGINE}/datahandler/api
    ${POPULUSENGINE}/display/api
    ${PSC_BASE}/api
    ${PSC_BASE}/src
)

set(PSC_HEADERS
    ${PSC_BASE}/api/psc.h
)

set(PSC_SOURCES
    ${PSC_BASE}/src/psc.cpp
    ${PSC_BASE}/src/Engine.h
    ${PSC_BASE}/src/Engine.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${PSC_HEADERS}
    ${PSC_SOURCES}
)

install(DIRECTORY api
    DESTINATION "${PSC_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${PSC_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()

