cmake_minimum_required(VERSION 2.8.12)

project("datahandler")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED DATAHANDLER_PREFIX)
    set(DATAHANDLER_PREFIX "datahandler")
endif()

if(NOT DEFINED DATAHANDLER_BASE)
    set(DATAHANDLER_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(DataHandler.cmake)

add_library(${PROJECT_NAME} OBJECT
    ${DATAHANDLER_HEADERS}
    ${DATAHANDLER_SOURCES}
)

install(FILES DataHandler.cmake
    DESTINATION "${DATAHANDLER_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${DATAHANDLER_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${DATAHANDLER_PREFIX}"
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()
