cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED LSRENGINE)
    set(LSRENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> LSRENGINE: ${LSRENGINE}")
endif()

if(NOT DEFINED DATAHANDLER_BASE)
    set(DATAHANDLER_BASE "${LSRENGINE}/datahandler")
    message(STATUS "--> DATAHANDLER_BASE: ${DATAHANDLER_BASE}")
endif()

include_directories(
    ${LSRENGINE}/common/api
    ${LSRENGINE}/communication/api
    ${LSRENGINE}/database/api
    ${LSRENGINE}/database/api/gen
    ${LSRENGINE}/odi/api
    ${LSRROOT}/pil/api
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
        ${LSRENGINE}/database/test
    )

    set(DATAHANDLER_HEADERS
        ${DATAHANDLER_HEADERS}
        ${DATAHANDLER_BASE}/test/ExpressionTestFixture.h
        ${DATAHANDLER_BASE}/test/MockDataHandler.h
        ${DATAHANDLER_BASE}/test/MockListener.h
        ${DATAHANDLER_BASE}/test/TestDataContext.h
    )
endif()
