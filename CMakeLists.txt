cmake_minimum_required(VERSION 2.8.12)
project("PopulusSC")

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR};${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
message(STATUS "--> ${PROJECT_NAME} CMAKE_MODULE_PATH: ${CMAKE_MODULE_PATH}")

include(Init)

message(STATUS "--> ${PROJECT_NAME}: ${POPULUS_VERSION_MAJOR}.${POPULUS_VERSION_MINOR}.${POPULUS_VERSION_PATCH}")

add_subdirectory(engine)
add_subdirectory(pgl)
add_subdirectory(pgw)
add_subdirectory(simu)

include(CPack)
