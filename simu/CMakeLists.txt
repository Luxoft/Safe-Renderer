cmake_minimum_required(VERSION 2.8.12)

project("lsr_simu")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED SIMU_PREFIX)
    set(SIMU_PREFIX "simu")
endif()

if(NOT DEFINED SIMU_BASE)
    set(SIMU_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

include_directories(
    ${LSRROOT}/engine/common/api
    ${LSRROOT}/engine/communication/api #for FUBridge
    ${LSRROOT}/engine/odi/api #for FUBridge
    ${LSRROOT}/engine/database/api/gen #for FUBridge
    ${LSRROOT}/engine/database/api #for FUBridge
    ${LSRROOT}/engine/lsr/api
    ${LSRROOT}/engine/framehandler/api
    ${LSRROOT}/engine/datahandler/api
    ${LSRROOT}/engine/display/api
    ${LSRROOT}/gil/api
    ${LSRROOT}/pil/api
    ${SIMU_BASE}/src
    ${SIMU_BASE}/communication/api
    ${SIMU_BASE}/odi/api
    ${LSRROOT}/test/database/Telltales/Output
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
    ${LSRROOT}/test/database/Telltales/Output/Telltales.cpp
)

add_definitions(-Dlint -DNOMINMAX)

if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(SIMU_LIBS ws2_32)
else()
endif()

add_subdirectory(communication)
add_subdirectory(odi)

add_library(odicomm STATIC
    $<TARGET_OBJECTS:communication>
    $<TARGET_OBJECTS:odi>
)

add_executable(lsr_simu
    ${SIMU_HEADERS}
    ${SIMU_SOURCES}
)

if (MSVC)
    target_compile_options(lsr_simu PRIVATE "/wd4996")
endif()

target_link_libraries(lsr_simu
    engine gilSample pilSample odicomm ${SIMU_LIBS}
)

install(TARGETS ${PROJECT_NAME}
    RUNTIME DESTINATION ${SIMU_PREFIX}
    LIBRARY DESTINATION ${SIMU_PREFIX}
    ARCHIVE DESTINATION ${SIMU_PREFIX}
)


