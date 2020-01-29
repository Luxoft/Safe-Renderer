
include(GoogleTest)

function(GUNITTEST_COMMON)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_COMMON "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_COMMON_WORKING_DIRECTORY)
        set(GUNITTEST_COMMON_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "common_${GUNITTEST_COMMON_NAME}"
        LIBS ${GUNITTEST_COMMON_LIBS} ${ENGINE_PROJECT_NAME}
        WORKING_DIRECTORY ${GUNITTEST_COMMON_WORKING_DIRECTORY}
        FILES ${GUNITTEST_COMMON_FILES}
    )
endfunction()

GUNITTEST_COMMON(
    NAME PoolTest
    FILES PoolTest.cpp
          PoolFaultInjectionTest.cpp
          PoolCorrupter.h
          PoolTestHelper.h
          PoolTestTypes.h
)

GUNITTEST_COMMON(
    NAME PoolMarkerTest
    FILES PoolMarkerTest.cpp
)

GUNITTEST_COMMON(
    NAME PooledObjectFactoryTest
    FILES PooledObjectFactoryTest.cpp
          SelfCheckerClass.h
)

GUNITTEST_COMMON(
    NAME NodeDataLengthTest
    FILES NodeDataLengthTest.cpp
)

GUNITTEST_COMMON(
    NAME LongTermPtrTest
    FILES LongTermPtrTest.cpp
          LongTermPtrCorrupter.h
)

GUNITTEST_COMMON(
    NAME CommonTest
    FILES AssertionTest.cpp
          LSRErrorCollectorTest.cpp
          TimerTest.cpp
)
