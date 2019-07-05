
include(GoogleTest)

function(GUNITTEST_COMMUNICATION)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_COMMUNICATION "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_COMMUNICATION_WORKING_DIRECTORY)
        set(GUNITTEST_COMMUNICATION_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "communication_${GUNITTEST_COMMUNICATION_NAME}"
        LIBS ${GUNITTEST_COMMUNICATION_LIBS} ${ENGINE_PROJECT_NAME} pilSample
        WORKING_DIRECTORY ${GUNITTEST_COMMUNICATION_WORKING_DIRECTORY}
        FILES ${GUNITTEST_COMMUNICATION_FILES}
    )
endfunction()

GUNITTEST_COMMUNICATION(
    NAME PilOdiComSessionTest
    FILES PilOdiComSessionTest.cpp
          PilOdiComSessionTestAuxiliary.h
)

GUNITTEST_COMMUNICATION(
    NAME PilMsgTransmitterTest
    FILES PilMsgTransmitterTest.cpp
)

GUNITTEST_COMMUNICATION(
    NAME PilOdiComSessionUtilsTest
    FILES PilOdiComSessionUtilsTest.cpp
)

GUNITTEST_COMMUNICATION(
    NAME OutputStreamTest
    FILES OutputStreamTest.cpp
)

GUNITTEST_COMMUNICATION(
    NAME InputStreamTest
    FILES InputStreamTest.cpp
)

GUNITTEST_COMMUNICATION(
    NAME MessageHeaderTest
    FILES MessageHeaderTest.cpp
)

