include(GoogleTest)

function(GUNITTEST_PGL)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_PGL "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_PGL_WORKING_DIRECTORY)
        set(GUNITTEST_PGL_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "pgl_${GUNITTEST_PGL_NAME}"
        LIBS pgl
        WORKING_DIRECTORY ${GUNITTEST_PGL_WORKING_DIRECTORY}
        FILES ${GUNITTEST_PGL_FILES}
    )
endfunction()

GUNITTEST_PGL(
    NAME PglTest
    FILES PglTest.cpp
)

#GUNITTEST_PGL(
#    NAME PglSwWin32Test
#    FILES Pgl_sw_win32_Test.cpp
#)

