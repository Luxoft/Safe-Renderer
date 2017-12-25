cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

if(NOT DEFINED ODI_BASE)
    set(ODI_BASE "${POPULUSENGINE}/odi")
    message(STATUS "--> ODI_BASE: ${ODI_BASE}")
endif()

include_directories(
    ${ODI_BASE}/api
    ${POPULUSENGINE}/common/api
    ${POPULUSENGINE}/communication/api
    ${POPULUSENGINE}/database/api
    ${POPULUSENGINE}/database/api/gen
    ${POPULUSENGINE}/database/api
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

if (UNIT_TESTS)
    include_directories(
        ${ODI_BASE}/test
    )

    set(ODI_HEADERS
        ${ODI_HEADERS}
        ${ODI_BASE}/test/RegistrationMsgBuffer.h
    )
endif()
