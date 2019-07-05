include(GoogleTest)

function(GUNITTEST_DISPLAY)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_DISPLAY "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_DISPLAY_WORKING_DIRECTORY)
        set(GUNITTEST_DISPLAY_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "display_${GUNITTEST_DISPLAY_NAME}"
        LIBS ${GUNITTEST_DISPLAY_LIBS} ${ENGINE_PROJECT_NAME} pilSample gilSample
        WORKING_DIRECTORY ${GUNITTEST_DISPLAY_WORKING_DIRECTORY}
        FILES ${GUNITTEST_DISPLAY_FILES}
    )
endfunction()

GUNITTEST_DISPLAY(
    NAME DisplayTest
    FILES DisplayTest.cpp
)
