cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

if(NOT DEFINED DATAHANDLER_BASE)
    set(DATAHANDLER_BASE "${POPULUSENGINE}/datahandler")
    message(STATUS "--> DATAHANDLER_BASE: ${DATAHANDLER_BASE}")
endif()

include_directories(
    ${POPULUSENGINE}/common/api
    ${POPULUSENGINE}/communication/api
    ${POPULUSENGINE}/database/api
    ${POPULUSENGINE}/database/api/gen
    ${POPULUSENGINE}/odi/api
    ${POPULUSROOT}/pgw/api
    ${DATAHANDLER_BASE}/api
    ${DATAHANDLER_BASE}/src
)

set(DATAHANDLER_HEADERS
    ${DATAHANDLER_BASE}/api/BitmapExpression.h
    ${DATAHANDLER_BASE}/api/BoolExpression.h
    ${DATAHANDLER_BASE}/api/DataContext.h
    ${DATAHANDLER_BASE}/api/DataHandler.h
    ${DATAHANDLER_BASE}/api/DataStatus.h
    ${DATAHANDLER_BASE}/api/DefaultDataContext.h
    ${DATAHANDLER_BASE}/api/Expression.h
    ${DATAHANDLER_BASE}/api/IDataHandler.h
    ${DATAHANDLER_BASE}/api/Number.h
    ${DATAHANDLER_BASE}/api/NumberExpression.h
)

set(DATAHANDLER_SOURCES
    ${DATAHANDLER_BASE}/src/BitmapExpression.cpp
    ${DATAHANDLER_BASE}/src/BoolExpression.cpp
    ${DATAHANDLER_BASE}/src/DataHandler.cpp
    ${DATAHANDLER_BASE}/src/DefaultDataContext.cpp
    ${DATAHANDLER_BASE}/src/Expression.cpp
    ${DATAHANDLER_BASE}/src/ExpressionOperators.cpp
    ${DATAHANDLER_BASE}/src/ExpressionOperators.h
    ${DATAHANDLER_BASE}/src/NumberExpression.cpp
)

if (UNIT_TESTS)
    include_directories(
        ${DATAHANDLER_BASE}/test
        ${POPULUSENGINE}/database/test
    )

    set(DATAHANDLER_HEADERS
        ${DATAHANDLER_HEADERS}
        ${DATAHANDLER_BASE}/test/ExpressionTestFixture.h
        ${DATAHANDLER_BASE}/test/MockDataHandler.h
        ${DATAHANDLER_BASE}/test/MockListener.h
        ${DATAHANDLER_BASE}/test/TestDataContext.h
    )
endif()
