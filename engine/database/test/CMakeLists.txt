include(GoogleTest)

function(GUNITTEST_DATABASE)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_DATABASE "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_DATABASE_WORKING_DIRECTORY)
        set(GUNITTEST_DATABASE_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "database_${GUNITTEST_DATABASE_NAME}"
        LIBS ${GUNITTEST_DATABASE_LIBS} ${ENGINE_PROJECT_NAME} gilSample
        WORKING_DIRECTORY ${GUNITTEST_DATABASE_WORKING_DIRECTORY}
        FILES ${GUNITTEST_DATABASE_FILES}
    )
endfunction()


# add library with mock implementation.
# will be used in other components tests

include_directories(
    ${LSRROOT}/pil/api
    ${LSRENGINE}/common/api
    ${LSRENGINE}/framehandler/api
    ${LSRENGINE}/lsr/api
    ${DATABASE_BASE}/api
    ${DATABASE_BASE}/api/gen
    ${DATABASE_BASE}/src
    ${HMI_PROJECT_PATH}
)

set(DATABASEMOCK_HEADERS
    ${DATABASE_HEADERS}
)

set(DATABASEMOCK_SOURCES
    ${DATABASE_BASE}/src/Area.cpp
    ${DATABASE_BASE}/src/LsrImage.cpp
    ${DATABASE_BASE}/test/DatabaseMock.cpp
)

add_library(databasemock OBJECT
    ${DATABASEMOCK_HEADERS}
    ${DATABASEMOCK_SOURCES}
)

set(TEST_SOURCES
    AreaTest.cpp
    ColorTest.cpp
    DatabaseTest.cpp
    LsrImageTest.cpp
    DDHTypeTest.cpp
    pil.cpp
    ${LSRROOT}/test/database/Telltales/Output/Telltales.cpp
)


GUNITTEST_DATABASE(
    NAME DatabaseTest
    FILES ${TEST_SOURCES}
)
