cmake_minimum_required(VERSION 2.8.12)

project("pilSample")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED PIL_PREFIX)
    set(PIL_PREFIX "pil")
endif()

if(NOT DEFINED PIL_BASE)
    set(PIL_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include(Pil.cmake)

if(SIMULATION OR UNIT_TESTS)
    add_library(${PROJECT_NAME}
        ${PIL_HEADERS}
        ${PIL_SOURCES}
    )

    target_link_libraries(${PROJECT_NAME} ${PIL_LIBS})

    install(FILES Pil.cmake
        DESTINATION "${PIL_PREFIX}"
    )

    install(DIRECTORY api
        DESTINATION "${PIL_PREFIX}"
    )

    install(DIRECTORY src
        DESTINATION "${PIL_PREFIX}"
    )

    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${PIL_PREFIX}
        LIBRARY DESTINATION ${PIL_PREFIX}
        ARCHIVE DESTINATION ${PIL_PREFIX}
    )
else()
    install(FILES ${PIL_HEADERS}
        DESTINATION "${PIL_PREFIX}/api"
    )
endif()


