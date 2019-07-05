cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE ${CMAKE_CURRENT_SOURCE_DIR}/..)
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

if(NOT DEFINED COMMON_BASE)
    set(COMMON_BASE ${LSRENGINE}/common)
    message(STATUS "--> COMMON_BASE: ${COMMON_BASE}")
endif()

include_directories(
    ${LSRROOT}/pil/api
    ${COMMON_BASE}/api
)

set(COMMON_HEADERS
    ${COMMON_BASE}/api/Assertion.h
    ${COMMON_BASE}/api/HealthLog.h
    ${COMMON_BASE}/api/LongTermPtr.h
    ${COMMON_BASE}/api/NodeDataLength.h
    ${COMMON_BASE}/api/NonCopyable.h
    ${COMMON_BASE}/api/Pool.h
    ${COMMON_BASE}/api/PoolMarker.h
    ${COMMON_BASE}/api/PooledObjectFactory.h
    ${COMMON_BASE}/api/LSRError.h
    ${COMMON_BASE}/api/LsrLimits.h
    ${COMMON_BASE}/api/LsrTypes.h
)

set(COMMON_SOURCES
    ${COMMON_BASE}/src/Assertion.cpp
)

if (UNIT_TESTS)
    include_directories(
        ${COMMON_BASE}/test
    )

    set(COMMON_HEADERS
        ${COMMON_HEADERS}
        ${COMMON_BASE}/test/LongTermPtrCorrupter.h
        ${COMMON_BASE}/test/PoolCorrupter.h
        ${COMMON_BASE}/test/PoolTestHelper.h
        ${COMMON_BASE}/test/PoolTestTypes.h
        ${COMMON_BASE}/test/SelfCheckerClass.h
    )
endif()
