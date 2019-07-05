
if(BUILD_SHARED_LIBS)
    message(FATAL_ERROR "GoogleTest doesn't support shared linking")
endif()

add_definitions(-DUNIT_TEST)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_definitions(-DGTEST_HAS_TR1_TUPLE=0 -DGTEST_USE_OWN_TR1_TUPLE=1)
endif ()

if(NOT TARGET gmock)
    # Workaround for BUILD_SHARED_LIBS flag in gmock
    set(TMP_BUILD_SHARED_LIBS ${BUILD_SHARED_LIBS})
    if(MSVC)
        add_definitions(-D_VARIADIC_MAX=10 -DGTEST_USE_OWN_TR1_TUPLE=0)
        # Google Mock does not support building in a separate DLL on Windows.
        set(BUILD_SHARED_LIBS OFF)
    endif()

    add_subdirectory(${LSRROOT}/3rdparty/gmock ${CMAKE_BINARY_DIR}/gmock)
    set_property(TARGET gmock PROPERTY FOLDER "External")
    set_property(TARGET gmock_main PROPERTY FOLDER "External")
    set_property(TARGET gtest PROPERTY FOLDER "External")
    set_property(TARGET gtest_main PROPERTY FOLDER "External")
    set(BUILD_SHARED_LIBS ${TMP_BUILD_SHARED_LIBS})
endif()

include_directories(
    "${gmock_SOURCE_DIR}/include"
    "${gmock_SOURCE_DIR}"
    "${gtest_SOURCE_DIR}/include"
    "${gtest_SOURCE_DIR}"
)

if(NOT DEFINED GUNITTEST_PREFIX)
    set(GUNITTEST_PREFIX "googleunittest_")
endif()

function(GUNITTEST_SKELETON)
    set(oneValueArgs NAME WORKING_DIRECTORY IDE_FOLDER)
    set(multiValueArgs LIBS FILES FLAGS DEFINES)
    cmake_parse_arguments(GUNITTEST_SKELETON "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    set(GUNITTEST_NAME "${GUNITTEST_PREFIX}${GUNITTEST_SKELETON_NAME}")
    add_executable(${GUNITTEST_NAME}
        ${GUNITTEST_SKELETON_FILES}
    )
    target_link_libraries(${GUNITTEST_NAME}
        ${GUNITTEST_SKELETON_LIBS}
        ${PLATFORM_SPECIFIC_LINK_LIBRARIES}
        ${SYSTEM_LINK_LIBS}
    )
    set_target_properties(${GUNITTEST_NAME} PROPERTIES COMPILE_DEFINITIONS ROOT_PATH=\"${LSRROOT}\")

    if(NOT GUNITTEST_SKELETON_IDE_FOLDER)
        set(GUNITTEST_SKELETON_IDE_FOLDER "UnitTests/GUnit")
    endif()
    set_property(TARGET ${GUNITTEST_NAME} PROPERTY FOLDER "${GUNITTEST_SKELETON_IDE_FOLDER}")

    set_source_files_properties(${GUNITTEST_SKELETON_FILES} PROPERTIES COMPILE_FLAGS "${GUNITTEST_SKELETON_FLAGS}")

    set_property(TARGET ${GUNITTEST_NAME} APPEND_STRING PROPERTY COMPILE_DEFINITIONS "${GUNITTEST_SKELETON_DEFINES}")

    if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux" OR ${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
        set_property(TARGET ${GUNITTEST_NAME} APPEND_STRING PROPERTY LINK_FLAGS "-pthread")
    endif()

    if(WIN32)
        # Fix for Visual Studio
        set(CMAKE_EXE_LINKER_FLAGS "/ignore:4199")
    endif()

    add_test(NAME ${GUNITTEST_NAME}
        COMMAND "$<TARGET_FILE:${GUNITTEST_NAME}>" --gtest_output=xml:result/${GUNITTEST_NAME}.xml
        WORKING_DIRECTORY ${GUNITTEST_SKELETON_WORKING_DIRECTORY}
    )

    install(TARGETS ${GUNITTEST_NAME}
        RUNTIME DESTINATION bin
    )
endfunction()

function(GUNITTEST)
    set(oneValueArgs NAME WORKING_DIRECTORY IDE_FOLDER)
    set(multiValueArgs LIBS FILES FLAGS DEFINES)
    cmake_parse_arguments(GUNITTEST "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    GUNITTEST_SKELETON(
        NAME ${GUNITTEST_NAME}
        WORKING_DIRECTORY ${GUNITTEST_WORKING_DIRECTORY}
        IDE_FOLDER ${GUNITTEST_IDE_FOLDER}
        LIBS ${GUNITTEST_LIBS} gmock gmock_main
        FILES ${GUNITTEST_FILES}
        FLAGS ${GUNITTEST_FLAGS}
        DEFINES ${GUNITTEST_DEFINES}
        ${GUNITTEST_UNPARSED_ARGUMENTS}
    )
endfunction()

include(CTest)
