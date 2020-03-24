
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
        FILES ${GUNITTEST_DATAHANDLER_FILES} ${DATAHANDLER_SOURCES}
    )
endfunction()

include_directories(
    ${LSRENGINE}/lsr/api
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
    NAME DataHandlerTest
    FILES DataHandlerTest.cpp
)
