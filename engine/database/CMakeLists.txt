cmake_minimum_required(VERSION 2.8.12)

project("database")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED DATABASE_PREFIX)
    set(DATABASE_PREFIX "database")
endif()

if(NOT DEFINED DATABASE_BASE)
    set(DATABASE_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(DataBase.cmake)

add_library(${PROJECT_NAME} OBJECT
    ${DATABASE_HEADERS}
    ${DATABASE_SOURCES}
)

if(UNIT_TESTS)
    # add library with mock implementation.
    # will be used in other components tests
    include(DataBaseMock.cmake)

    add_library(databasemock OBJECT
        ${DATABASEMOCK_HEADERS}
        ${DATABASEMOCK_SOURCES}
    )
endif()

install(FILES DataBase.cmake
    DESTINATION "${DATABASE_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${DATABASE_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${DATABASE_PREFIX}"
)
