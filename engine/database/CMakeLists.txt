cmake_minimum_required(VERSION 2.8.12)

project("database")

message(STATUS "Start process project ${PROJECT_NAME}")

if(NOT DEFINED LSR_INITED)
    message(FATAL_ERROR "Project wasn't properly initialized.")
endif()

if(NOT DEFINED DATABASE_PREFIX)
    set(DATABASE_PREFIX "${ENGINE_PREFIX}/database")
endif()

if(NOT DEFINED DATABASE_BASE)
    set(DATABASE_BASE "${CMAKE_CURRENT_SOURCE_DIR}")
endif()

cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

include_directories(
    ${LSRROOT}/pil/api
    ${LSRENGINE}/common/api
    ${DATABASE_BASE}/api
    ${DATABASE_BASE}/api/gen
    ${DATABASE_BASE}/src
)

set(DATABASE_HEADERS
    ${DATABASE_BASE}/api/ddh_defs.h
    ${DATABASE_BASE}/api/Area.h
    ${DATABASE_BASE}/api/Color.h
    ${DATABASE_BASE}/api/Database.h
    ${DATABASE_BASE}/api/DatabaseTypes.h
    ${DATABASE_BASE}/api/LsrImage.h
    ${DATABASE_BASE}/api/ResourceBuffer.h
    ${DATABASE_BASE}/api/StaticBitmap.h
    ${DATABASE_BASE}/api/gen/AreaType.h
    ${DATABASE_BASE}/api/gen/BaseFieldChoiceType.h
    ${DATABASE_BASE}/api/gen/BitmapStateDefinitionType.h
    ${DATABASE_BASE}/api/gen/DDHType.h
    ${DATABASE_BASE}/api/gen/DisplaySizeType.h
    ${DATABASE_BASE}/api/gen/ExpressionTermType.h
    ${DATABASE_BASE}/api/gen/HMIGlobalSettingsType.h
    ${DATABASE_BASE}/api/gen/PanelDatabaseType.h
    ${DATABASE_BASE}/api/gen/PanelType.h
    ${DATABASE_BASE}/api/gen/BitmapDatabaseType.h
    ${DATABASE_BASE}/api/gen/BitmapType.h
    ${DATABASE_BASE}/api/gen/SkinnedBitmapType.h
    ${DATABASE_BASE}/api/gen/StaticBitmapFieldType.h
)

set(DATABASE_SOURCES
    ${DATABASE_BASE}/src/Area.cpp
    ${DATABASE_BASE}/src/Database.cpp
    ${DATABASE_BASE}/src/LsrImage.cpp
)

add_library(${PROJECT_NAME} OBJECT
    ${DATABASE_HEADERS}
    ${DATABASE_SOURCES}
)

if(UNIT_TESTS)
    add_subdirectory(test)
endif()

install(DIRECTORY api
    DESTINATION "${DATABASE_PREFIX}"
)

install(DIRECTORY src
    DESTINATION "${DATABASE_PREFIX}"
)
