include(GoogleTest)

function(GUNITTEST_DATABASE)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_DATABASE "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_DATABASE_WORKING_DIRECTORY)
        set(GUNITTEST_DATABASE_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "database_${GUNITTEST_DATABASE_NAME}"
        LIBS ${GUNITTEST_DATABASE_LIBS} ${ENGINE_PROJECT_NAME}
        WORKING_DIRECTORY ${GUNITTEST_DATABASE_WORKING_DIRECTORY}
        FILES ${GUNITTEST_DATABASE_FILES}
    )
endfunction()

set(TEST_SOURCES
    AreaTest.cpp
    ColorTest.cpp
    DatabaseTest.cpp
    FonBinReaderTest.cpp
    PopulusImageTest.cpp
    DDHTypeTest.cpp
    pgw.cpp
)

set(TEST_HEADERS
    FonBinWriter.h
)


GUNITTEST_DATABASE(
    NAME DatabaseTest
    FILES ${TEST_SOURCES} ${TEST_HEADERS} 
)
