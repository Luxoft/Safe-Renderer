include(CMakeParseArguments)

# Set package name
# Parameters:
#   MAJOR      - major version
#   MINOR      - minor version
#   PATCH      - patch version
#   HASH       - revison hash
#   VENDOR     - package vendor (optional)
#   DEV_BUILD  - flag for development build (optional)
#   UNIT_TESTS - flag whether unittests are used (optional)
function(setPackageName)
    set(optionsArgs)
    set(oneValueArgs MAJOR MINOR PATCH HASH VENDOR DEV_BUILD UNIT_TESTS)
    set(multiValueArgs)
    cmake_parse_arguments(ARG "${optionsArgs}" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT ARG_VENDOR)
        set(ARG_VENDOR "Luxoft")
    endif()

    set(CPACK_PACKAGE_VERSION "${ARG_MAJOR}.${ARG_MINOR}.${ARG_PATCH}")
    set(CPACK_PACKAGE_VERSION_MAJOR "${ARG_MAJOR}")
    set(CPACK_PACKAGE_VERSION_MINOR "${ARG_MINOR}")
    set(CPACK_PACKAGE_VERSION_PATCH "${ARG_PATCH}")

    set(CPACK_PACKAGE_VENDOR ${ARG_VENDOR})
    set(CPACK_PACKAGE_NAME "${CPACK_PACKAGE_VENDOR} ${PROJECT_NAME}")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CPACK_PACKAGE_VENDOR} ${PROJECT_NAME} installation pack")

    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${ARG_MAJOR}.${ARG_MINOR}.${ARG_PATCH}")

    if(DEV_BUILD)
        if(ARG_HASH)
            set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${ARG_HASH}")
        else()
            set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-UNKNOWNHASH")
        endif()
    endif()

    if(NOT DEFINED CPACK_SYSTEM_NAME)
        if(NOT DEFINED CMAKE_SYSTEM_NAME)
            set(CPACK_SYSTEM_NAME "UNKNOWNSYS")
        elseif("${CMAKE_SYSTEM_NAME}" MATCHES "Windows")
            if(CMAKE_CL_64)
                set(CPACK_SYSTEM_NAME "win64")
            else()
                set(CPACK_SYSTEM_NAME "win32")
            endif()
        elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
            set(CPACK_SYSTEM_NAME "linux")
        else()
            set(CPACK_SYSTEM_NAME ${CMAKE_SYSTEM_NAME})
        endif()
    endif()

    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-${CPACK_SYSTEM_NAME}")

    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-Dbg")
    elseif(CMAKE_BUILD_TYPE STREQUAL "RelWithDebInfo")
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-RelWDbg")
    endif()

    if(UNIT_TESTS)
        set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}-UnitTest")
    endif()

    # keep the filename between cmake's runs
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}" CACHE INTERNAL "" FORCE)

    # export to parent scope
    set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_FILE_NAME}" PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION "${CPACK_PACKAGE_VERSION}" PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION_MAJOR "${CPACK_PACKAGE_VERSION_MAJOR}" PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION_MINOR "${CPACK_PACKAGE_VERSION_MINOR}" PARENT_SCOPE)
    set(CPACK_PACKAGE_VERSION_PATCH "${CPACK_PACKAGE_VERSION_PATCH}" PARENT_SCOPE)
    set(CPACK_PACKAGE_VENDOR "${CPACK_PACKAGE_VENDOR}" PARENT_SCOPE)
    set(CPACK_PACKAGE_NAME "${CPACK_PACKAGE_NAME}" PARENT_SCOPE)
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CPACK_PACKAGE_DESCRIPTION_SUMMARY}" PARENT_SCOPE)
endfunction()
