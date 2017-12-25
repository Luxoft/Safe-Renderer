
include(GoogleTest)

function(GUNITTEST_ODI)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_ODI "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_ODI_WORKING_DIRECTORY)
        set(GUNITTEST_ODI_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "odi_${GUNITTEST_ODI_NAME}"
        LIBS ${GUNITTEST_ODI_LIBS} ${ENGINE_PROJECT_NAME}
        WORKING_DIRECTORY ${GUNITTEST_ODI_WORKING_DIRECTORY}
        FILES ${GUNITTEST_ODI_FILES}
    )
endfunction()

GUNITTEST_ODI(
    NAME RegistrationMsgBuilderTest
    FILES RegistrationMsgBuilderTest.cpp
)

GUNITTEST_ODI(
    NAME RegistrationMsgBufferTest
    FILES RegistrationMsgBufferTest.cpp
)

GUNITTEST_ODI(
    NAME RegistrationMsgReaderTest
    FILES RegistrationMsgReaderTest.cpp
)

GUNITTEST_ODI(
    NAME DataResponseMessageTest
    FILES DataResponseMessageTest.cpp
)

GUNITTEST_ODI(
    NAME EventMessageTest
    FILES EventMessageTest.cpp
)

GUNITTEST_ODI(
    NAME IndicationDataMessageTest
    FILES IndicationDataMessageTest.cpp
)

GUNITTEST_ODI(
    NAME AliveMessageTest
    FILES AliveMessageTest.cpp
)

GUNITTEST_ODI(
    NAME OdiMessageUtilsTest
    FILES OdiMessageUtilsTest.cpp
)

GUNITTEST_ODI(
    NAME OdiMsgHeaderTest
    FILES OdiMsgHeaderTest.cpp
)
