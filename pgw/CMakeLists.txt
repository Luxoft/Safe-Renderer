cmake_minimum_required(VERSION 2.8.12)

project("pgw")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED PGW_PREFIX)
    set(PGW_PREFIX "pgw")
endif()

if(NOT DEFINED PGW_BASE)
    set(PGW_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(Pgw.cmake)

add_library(${PROJECT_NAME}
    ${PGW_HEADERS}
    ${PGW_SOURCES}
)

target_link_libraries(${PROJECT_NAME} ${PGW_LIBS})

install(FILES Pgw.cmake
    DESTINATION "${PGW_PREFIX}"
)

install(DIRECTORY api
    DESTINATION "${PGW_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${PGW_PREFIX}"
)

