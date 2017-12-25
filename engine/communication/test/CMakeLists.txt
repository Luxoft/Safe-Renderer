
include(GoogleTest)

function(GUNITTEST_COMMUNICATION)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_COMMUNICATION "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_COMMUNICATION_WORKING_DIRECTORY)
        set(GUNITTEST_COMMUNICATION_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "communication_${GUNITTEST_COMMUNICATION_NAME}"
        LIBS ${GUNITTEST_COMMUNICATION_LIBS} ${ENGINE_PROJECT_NAME} pgw
        WORKING_DIRECTORY ${GUNITTEST_COMMUNICATION_WORKING_DIRECTORY}
        FILES ${GUNITTEST_COMMUNICATION_FILES}
    )
endfunction()

GUNITTEST_COMMUNICATION(
    NAME PgwOdiComSessionTest
    FILES PgwOdiComSessionTest.cpp
          PgwOdiComSessionTestAuxiliary.h
)

GUNITTEST_COMMUNICATION(
    NAME PgwMsgTransmitterTest
    FILES PgwMsgTransmitterTest.cpp
)

GUNITTEST_COMMUNICATION(
    NAME PgwOdiComSessionUtilsTest
    FILES PgwOdiComSessionUtilsTest.cpp
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

