include(GoogleTest)

function(GUNITTEST_GILSAMPLE)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_GILSAMPLE "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_GILSAMPLE_WORKING_DIRECTORY)
        set(GUNITTEST_GILSAMPLE_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "gilsample_${GUNITTEST_GILSAMPLE_NAME}"
        LIBS gilSample pilSample
        WORKING_DIRECTORY ${GUNITTEST_GILSAMPLE_WORKING_DIRECTORY}
        FILES ${GUNITTEST_GILSAMPLE_FILES}
    )
endfunction()

GUNITTEST_GILSAMPLE(
    NAME GilSampleTest
    FILES GilSampleTest.cpp
)

#GUNITTEST_GILSAMPLE(
#    NAME GilSwWin32Test
#    FILES Gil_sw_win32_Test.cpp
#)

