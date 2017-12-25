cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

if(NOT DEFINED COMMUNICATION_BASE)
    set(COMMUNICATION_BASE "${POPULUSENGINE}/communication")
    message(STATUS "--> COMMUNICATION_BASE: ${COMMUNICATION_BASE}")
endif()

include_directories(
    ${POPULUSROOT}/pgw/api
    ${POPULUSENGINE}/common/api
    ${POPULUSENGINE}/odi/api
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
    ${COMMUNICATION_BASE}/src/OdiRecorder.h
    ${COMMUNICATION_BASE}/src/PgwMsgTransmitter.h
    ${COMMUNICATION_BASE}/api/PgwOdiComSessionBase.h
    ${COMMUNICATION_BASE}/api/PgwOdiComSession.h
)

set(COMMUNICATION_SOURCES
    ${COMMUNICATION_BASE}/src/InputStream.cpp
    ${COMMUNICATION_BASE}/src/MessageHeader.cpp
    ${COMMUNICATION_BASE}/src/OdiRecorder.cpp
    ${COMMUNICATION_BASE}/src/OutputStream.cpp
    ${COMMUNICATION_BASE}/src/PgwOdiComSessionBase.cpp
    ${COMMUNICATION_BASE}/src/PgwMsgTransmitter.cpp
)

if (UNIT_TESTS)
    include_directories(
        ${POPULUSROOT}/pgw/src/sample
        ${COMMUNICATION_BASE}/test
    )

    set(COMMUNICATION_HEADERS
        ${COMMUNICATION_HEADERS}
        ${COMMUNICATION_BASE}/test/InputStreamCorrupter.h
        ${COMMUNICATION_BASE}/test/OutputStreamCorrupter.h
    )
endif()
