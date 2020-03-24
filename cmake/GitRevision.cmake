include(CMakeParseArguments)

# Get git revision
# Parameters:
#   GIT_DIRECTORY      - where git is located (optional)
#   WORKING_FOLDER     - where repository is located (optional)
#   REVISION_VAR       - variable name for (full) git hash (optional)
#   SHORT_REVISION_VAR - variable name for short git hash (optional)
function(getGitRevision)
    set(optionsArgs)
    set(oneValueArgs GIT_DIRECTORY WORKING_FOLDER REVISION_VAR SHORT_REVISION_VAR)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${optionsArgs}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(ARG_GIT_DIRECTORY)
        set(CMAKE_PROGRAM_PATH "${CMAKE_PROGRAM_PATH};${ARG_GIT_DIRECTORY}")
    elseif(WIN32)
        set(CMAKE_PROGRAM_PATH "${CMAKE_PROGRAM_PATH};C:/Program Files/Git/bin")
    else()
        set(CMAKE_PROGRAM_PATH "${CMAKE_PROGRAM_PATH};/usr/local/bin;/usr/bin;/bin")
    endif()
    find_package(Git)
    if(NOT GIT_FOUND)
        message(FATAL_ERROR "git not found")
    endif()

    if(NOT ARG_WORKING_FOLDER)
        set(ARG_WORKING_FOLDER ${CMAKE_SOURCE_DIR})
    endif()

    if(ARG_REVISION_VAR)
        execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
            WORKING_DIRECTORY "${ARG_WORKING_FOLDER}"
            RESULT_VARIABLE EXIT_CODE
            OUTPUT_VARIABLE GIT_REVISION
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(NOT EXIT_CODE EQUAL 0)
            set(GIT_REVISION "GIT-ERROR")
        endif()
        set(${ARG_REVISION_VAR} ${GIT_REVISION} PARENT_SCOPE)
    endif()

    if(ARG_SHORT_REVISION_VAR)
        execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
            WORKING_DIRECTORY "${ARG_WORKING_FOLDER}"
            RESULT_VARIABLE EXIT_CODE
            OUTPUT_VARIABLE GIT_REVISION_SHORT
            ERROR_QUIET
            OUTPUT_STRIP_TRAILING_WHITESPACE)
        if(NOT EXIT_CODE EQUAL 0)
            set(GIT_REVISION_SHORT "GIT-ERROR")
        endif()
        set(${ARG_SHORT_REVISION_VAR} ${GIT_REVISION_SHORT} PARENT_SCOPE)
    endif()
endfunction()
