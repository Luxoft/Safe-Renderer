cmake_minimum_required(VERSION 2.8.12)

project("engine")

message(STATUS "Start process project ${PROJECT_NAME}")

set(ENGINE_PROJECT_NAME ${PROJECT_NAME})

if(NOT DEFINED POPULUSROOT)
    set(POPULUSROOT "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSROOT: ${POPULUSROOT}")
endif()

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE ${CMAKE_CURRENT_SOURCE_DIR})
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${POPULUSROOT}/cmake;${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if(NOT DEFINED POPULUS_INITED)
    include(Init)
endif()
include(EnginePlatformSpecific)

if(NOT DEFINED ENGINE_PREFIX)
    set(ENGINE_PREFIX "engine")
endif()

add_subdirectory(common)
add_subdirectory(communication)
add_subdirectory(odi)
add_subdirectory(database)
add_subdirectory(datahandler)
add_subdirectory(display)
add_subdirectory(psc)
add_subdirectory(framehandler)

add_library(${PROJECT_NAME} STATIC
    $<TARGET_OBJECTS:common>
    $<TARGET_OBJECTS:communication>
    $<TARGET_OBJECTS:odi>
    $<TARGET_OBJECTS:database>
    $<TARGET_OBJECTS:datahandler>
    $<TARGET_OBJECTS:display>
    $<TARGET_OBJECTS:framehandler>
    $<TARGET_OBJECTS:psc>
)

target_link_libraries(${PROJECT_NAME} ${SYSTEM_LINK_LIBS})

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${ENGINE_PREFIX}
    LIBRARY DESTINATION ${ENGINE_PREFIX}
    ARCHIVE DESTINATION ${ENGINE_PREFIX}
)

include(CPack)
