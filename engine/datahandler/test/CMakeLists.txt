
include(GoogleTest)

function(GUNITTEST_DATAHANDLER)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_DATAHANDLER "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_DATAHANDLER_WORKING_DIRECTORY)
        set(GUNITTEST_DATAHANDLER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "datahandler_${GUNITTEST_DATAHANDLER_NAME}"
        LIBS ${GUNITTEST_DATAHANDLER_LIBS} ${ENGINE_PROJECT_NAME} pilSample
        WORKING_DIRECTORY ${GUNITTEST_DATAHANDLER_WORKING_DIRECTORY}
        FILES ${GUNITTEST_DATAHANDLER_FILES}
    )
endfunction()

include_directories(
    ${LSRENGINE}/lsr/api
)

GUNITTEST_DATAHANDLER(
    NAME ExpressionTest
    FILES BitmapExpressionTest.cpp
          BoolExpressionTest.cpp
          ExpressionBooleanOperatorsTest.cpp
          ExpressionFallbackTest.cpp
          ExpressionItemAtOperatorTest.cpp
          ExpressionMinMaxOperatorTest.cpp
          ExpressionRedundancyTest.cpp
          ExpressionSubscriptionTest.cpp
          ExpressionTest.cpp
          ExpressionTestFixture.h
          MockDataHandler.h
          NumberExpressionTest.cpp
)

GUNITTEST_DATAHANDLER(
    NAME NumberTest
    FILES NumberTest.cpp
)

GUNITTEST_DATAHANDLER(
    NAME DataStatusTest
    FILES DataStatusTest.cpp
)

GUNITTEST_DATAHANDLER(
    NAME DataContextTest
    FILES DataContextTest.cpp
)

GUNITTEST_DATAHANDLER(
    NAME DataHandlerTest
    FILES DataHandlerTest.cpp
          ${LSRROOT}/test/database/Telltales/Output/Telltales.cpp
)
