cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

if(NOT DEFINED COMMUNICATION_BASE)
    set(COMMUNICATION_BASE "${LSRENGINE}/communication")
    message(STATUS "--> COMMUNICATION_BASE: ${COMMUNICATION_BASE}")
endif()

include_directories(
    ${LSRROOT}/pil/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/odi/api
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
    ${COMMUNICATION_BASE}/src/PilMsgTransmitter.h
    ${COMMUNICATION_BASE}/api/PilOdiComSessionBase.h
    ${COMMUNICATION_BASE}/api/PilOdiComSession.h
)

set(COMMUNICATION_SOURCES
    ${COMMUNICATION_BASE}/src/InputStream.cpp
    ${COMMUNICATION_BASE}/src/MessageHeader.cpp
    ${COMMUNICATION_BASE}/src/OdiRecorder.cpp
    ${COMMUNICATION_BASE}/src/OutputStream.cpp
    ${COMMUNICATION_BASE}/src/PilOdiComSessionBase.cpp
    ${COMMUNICATION_BASE}/src/PilMsgTransmitter.cpp
)

if (UNIT_TESTS)
    include_directories(
        ${LSRROOT}/pil/src/sample
        ${COMMUNICATION_BASE}/test
    )

    set(COMMUNICATION_HEADERS
        ${COMMUNICATION_HEADERS}
        ${COMMUNICATION_BASE}/test/InputStreamCorrupter.h
        ${COMMUNICATION_BASE}/test/OutputStreamCorrupter.h
    )
endif()
