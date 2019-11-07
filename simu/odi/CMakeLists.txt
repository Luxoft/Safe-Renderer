    cmake_minimum_required(VERSION 2.8.12)

project("odi")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED ODI_PREFIX)
    set(ODI_PREFIX "${ENGINE_PREFIX}/odi")
endif()

if(NOT DEFINED ODI_BASE)
    set(ODI_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${ODI_BASE}/api
    ${LSRROOT}/engine/common/api
    ${LSRROOT}/simu/communication/api
)

set(ODI_HEADERS
    ${ODI_BASE}/api/AliveMessage.h
    ${ODI_BASE}/api/DataResponseMessage.h
    ${ODI_BASE}/api/EventMessage.h
    ${ODI_BASE}/api/IndicationDataMessage.h
    ${ODI_BASE}/api/OdiMessageUtils.h
    ${ODI_BASE}/api/OdiMsgHeader.h
    ${ODI_BASE}/api/OdiTypes.h
    ${ODI_BASE}/api/RegistrationMsgBuilder.h
    ${ODI_BASE}/api/RegistrationMsgConstants.h
    ${ODI_BASE}/api/RegistrationMsgReader.h
)

set(ODI_SOURCES
    ${ODI_BASE}/src/AliveMessage.cpp
    ${ODI_BASE}/src/DataResponseMessage.cpp
    ${ODI_BASE}/src/EventMessage.cpp
    ${ODI_BASE}/src/IndicationDataMessage.cpp
    ${ODI_BASE}/src/OdiMessageUtils.cpp
    ${ODI_BASE}/src/OdiMsgHeader.cpp
    ${ODI_BASE}/src/RegistrationMsgBuilder.cpp
    ${ODI_BASE}/src/RegistrationMsgReader.cpp
)

add_library(${PROJECT_NAME} OBJECT
   ${ODI_HEADERS}
   ${ODI_SOURCES}
)

install(DIRECTORY api
    DESTINATION "${ODI_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${ODI_PREFIX}"
)

if (UNIT_TESTS)
    add_subdirectory(test)
endif()
