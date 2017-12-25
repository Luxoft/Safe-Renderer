cmake_minimum_required(VERSION 2.8.12)

if(NOT DEFINED POPULUSENGINE)
    set(POPULUSENGINE "${CMAKE_CURRENT_SOURCE_DIR}/..")
    message(STATUS "--> POPULUSENGINE: ${POPULUSENGINE}")
endif()

if(NOT DEFINED FRAMEHANDLER_BASE)
    set(FRAMEHANDLER_BASE "${POPULUSENGINE}/framehandler")
    message(STATUS "--> FRAMEHANDLER_BASE: ${FRAMEHANDLER_BASE}")
endif()

include_directories(
    ${POPULUSENGINE}/common/api
    ${POPULUSENGINE}/communication/api
    ${POPULUSENGINE}/database/api
    ${POPULUSENGINE}/database/api/gen
    ${POPULUSENGINE}/datahandler/api
    ${POPULUSENGINE}/display/api
    ${POPULUSROOT}/pgl/api
    ${FRAMEHANDLER_BASE}/api
    ${FRAMEHANDLER_BASE}/src
)

set(FRAMEHANDLER_HEADERS
    ${FRAMEHANDLER_BASE}/api/BitmapField.h
    ${FRAMEHANDLER_BASE}/api/Field.h
    ${FRAMEHANDLER_BASE}/api/Frame.h
    ${FRAMEHANDLER_BASE}/api/FrameHandler.h
    ${FRAMEHANDLER_BASE}/api/Panel.h
    ${FRAMEHANDLER_BASE}/api/ReferenceBitmapField.h
    ${FRAMEHANDLER_BASE}/api/Widget.h
    ${FRAMEHANDLER_BASE}/api/WidgetPool.h
    ${FRAMEHANDLER_BASE}/api/Window.h
)

set(FRAMEHANDLER_SOURCES
    ${FRAMEHANDLER_BASE}/src/BitmapField.cpp
    ${FRAMEHANDLER_BASE}/src/Field.cpp
    ${FRAMEHANDLER_BASE}/src/Frame.cpp
    ${FRAMEHANDLER_BASE}/src/FrameHandler.cpp
    ${FRAMEHANDLER_BASE}/src/Panel.cpp
    ${FRAMEHANDLER_BASE}/src/ReferenceBitmapField.cpp
    ${FRAMEHANDLER_BASE}/src/Widget.cpp
    ${FRAMEHANDLER_BASE}/src/Window.cpp
)

if(UNIT_TESTS)
    include_directories(
        ${FRAMEHANDLER_BASE}/test
        ${FRAMEHANDLER_BASE}/test/ddhbuilders
        ${POPULUSENGINE}/datahandler/test
        ${POPULUSENGINE}/database/test
        ${POPULUSENGINE}/common/test
        ${POPULUSENGINE}/display/test
    )

    set(DATAHANDLER_HEADERS
        ${FRAMEHANDLER_HEADERS}
        ${FRAMEHANDLER_BASE}/test/ddhbuilders/DdhBuilder.h
        ${FRAMEHANDLER_BASE}/test/ddhbuilders/DdhPageBuilder.h
        ${FRAMEHANDLER_BASE}/test/ddhbuilders/DdhPanelBuilder.h
        ${FRAMEHANDLER_BASE}/test/ddhbuilders/DdhStaticBitmapFieldBuilder.h
        ${FRAMEHANDLER_BASE}/test/ddhbuilders/DdhReferenceBitmapFieldBuilder.h
        ${FRAMEHANDLER_BASE}/test/FrameHandlerCorrupter.h
        ${FRAMEHANDLER_BASE}/test/MockWidget.h
        ${FRAMEHANDLER_BASE}/test/PglHelper.h
        ${FRAMEHANDLER_BASE}/test/TestCanvas.h
        ${FRAMEHANDLER_BASE}/test/WidgetPoolCorrupter.h
        ${FRAMEHANDLER_BASE}/test/WidgetPoolHelper.h
        ${FRAMEHANDLER_BASE}/test/WidgetTestBase.h
        ${FRAMEHANDLER_BASE}/test/WrongWidget.h
    )
endif()
