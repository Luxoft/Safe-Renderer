include(GoogleTest)

function(GUNITTEST_APP)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_APP "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_APP_WORKING_DIRECTORY)
        set(GUNITTEST_APP_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "psc_${GUNITTEST_APP_NAME}"
        LIBS ${GUNITTEST_APP_LIBS} ${ENGINE_PROJECT_NAME} pgw pglMock
        WORKING_DIRECTORY ${GUNITTEST_APP_WORKING_DIRECTORY}
        FILES ${GUNITTEST_APP_FILES}
    )
endfunction()

GUNITTEST_APP(
    NAME EngineAppTest
    FILES EngineAppTest.cpp
)
