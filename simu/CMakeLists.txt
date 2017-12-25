cmake_minimum_required(VERSION 2.8.12)

project("psc_simu")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED POPULUS_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED SIMU_PREFIX)
    set(SIMU_PREFIX "pgl")
endif()

if(NOT DEFINED SIMU_BASE)
    set(SIMU_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include_directories(
    ${POPULUSROOT}/engine/common/api
    ${POPULUSROOT}/engine/communication/api #for FUBridge
    ${POPULUSROOT}/engine/odi/api #for FUBridge
    ${POPULUSROOT}/engine/database/api/gen #for FUBridge
    ${POPULUSROOT}/engine/database/api #for FUBridge
    ${POPULUSROOT}/engine/psc/api
    ${POPULUSROOT}/engine/framehandler/api
    ${POPULUSROOT}/engine/datahandler/api
    ${POPULUSROOT}/engine/display/api
    ${POPULUSROOT}/pgl/api
    ${POPULUSROOT}/pgw/api
    ${SIMU_BASE}/src
)

set(SIMU_HEADERS
    ${SIMU_BASE}/src/getopt.h
    ${SIMU_BASE}/src/FUBridge.h
    ${SIMU_BASE}/src/ODIComSession.h
    ${SIMU_BASE}/src/MsgTransceiverTCP.h
)

set(SIMU_SOURCES
    ${SIMU_BASE}/src/main.cpp
    ${SIMU_BASE}/src/getopt_long.c
    ${SIMU_BASE}/src/FUBridge.cpp
    ${SIMU_BASE}/src/ODIComSession.cpp
    ${SIMU_BASE}/src/MsgTransceiverTCP.cpp
)

add_definitions(-Dlint)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SIMU_LIBS ws2_32)
else()
endif()


add_executable(psc_simu
    ${SIMU_HEADERS}
    ${SIMU_SOURCES}
)

if (MSVC)
    target_compile_options(psc_simu PRIVATE "/wd4996")
endif()

target_link_libraries(psc_simu
    engine pgl pgw  ${SIMU_LIBS}
)

# install(FILES Pgl.cmake
#     DESTINATION "${SIMU_PREFIX}"
# )

#install(DIRECTORY api
#    DESTINATION "${SIMU_PREFIX}"
#)

#install(DIRECTORY src
#    DESTINATION "${SIMU_PREFIX}"
#)

