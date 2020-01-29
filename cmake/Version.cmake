message(STATUS "Start process ${PROJECT_NAME} version.")

if(NOT DEFINED LSR_VERSION_MAJOR)
    set(LSR_VERSION_MAJOR 0)
endif(NOT DEFINED LSR_VERSION_MAJOR)

if(NOT DEFINED LSR_VERSION_MINOR)
    set(LSR_VERSION_MINOR 3)
endif(NOT DEFINED LSR_VERSION_MINOR)

if(NOT DEFINED LSR_VERSION_PATCH)
    set(LSR_VERSION_PATCH 0)
endif(NOT DEFINED LSR_VERSION_PATCH)

message(STATUS "--> ${PROJECT_NAME} version is ${LSR_VERSION_MAJOR}.${LSR_VERSION_MINOR}.${LSR_VERSION_PATCH}")

if(NOT CMAKE_SCRIPT_MODE_FILE)
    add_definitions("-DLSR_VERSION_MAJOR=${LSR_VERSION_MAJOR}")
    add_definitions("-DLSR_VERSION_MINOR=${LSR_VERSION_MINOR}")
    add_definitions("-DLSR_VERSION_PATCH=${LSR_VERSION_PATCH}")
endif()

if(NOT DEFINED GIT_REVISION)
    if(WIN32)
        set(CMAKE_PROGRAM_PATH "${CMAKE_PROGRAM_PATH};C:/Program Files/Git/bin")
    else()
        set(CMAKE_PROGRAM_PATH "${CMAKE_PROGRAM_PATH};/usr/local/bin;/usr/bin;/bin")
    endif()
    find_package(Git)
    if(NOT GIT_FOUND)
        message(FATAL_ERROR "git not found")
    endif()

    execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse HEAD
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE res
        OUTPUT_VARIABLE GIT_REVISION
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT res EQUAL 0)
        set(GIT_REVISION "GIT-ERROR")
    endif()

    execute_process(COMMAND "${GIT_EXECUTABLE}" rev-parse --short HEAD
        WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}"
        RESULT_VARIABLE res
        OUTPUT_VARIABLE GIT_REVISION_SHORT
        ERROR_QUIET
        OUTPUT_STRIP_TRAILING_WHITESPACE)
    if(NOT res EQUAL 0)
        set(GIT_REVISION_SHORT "GIT-ERROR")
    endif()

    message(STATUS "git revision is ${GIT_REVISION}; short revision is ${GIT_REVISION_SHORT}")
endif()
