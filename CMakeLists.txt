cmake_minimum_required(VERSION 2.8.12)
project("LSR")

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR};${CMAKE_CURRENT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
message(STATUS "--> ${PROJECT_NAME} CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

# For inforamtion about project configuration loot to the @cmake/Variable.cmake
include(Init)

add_subdirectory(engine)
add_subdirectory(gil)
add_subdirectory(pil)
if(${SIMULATION})
    add_subdirectory(simu)
endif()

include(CPack)
