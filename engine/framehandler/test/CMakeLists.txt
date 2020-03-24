include(GoogleTest)

add_library(test_framehandler STATIC
    $<TARGET_OBJECTS:common>
    $<TARGET_OBJECTS:databasemock>
    $<TARGET_OBJECTS:framehandler>
    ${LSRENGINE}/display/src/DisplayManager.cpp
    ${LSRENGINE}/display/src/WindowCanvas.cpp
    ${LSRENGINE}/display/src/TextureCache.cpp
    ${LSRENGINE}/display/src/Texture.cpp
    MockCanvas.cpp
    TestCanvas.h
)

function(GUNITTEST_FRAMEHANDLER)
    set(oneValueArgs NAME WORKING_DIRECTORY)
    set(multiValueArgs LIBS FILES)
    cmake_parse_arguments(GUNITTEST_FRAMEHANDLER "" "${oneValueArgs}" "${multiValueArgs}" ${ARGN})

    if(NOT GUNITTEST_FRAMEHANDLER_WORKING_DIRECTORY)
        set(GUNITTEST_FRAMEHANDLER_WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
    endif()

    GUNITTEST(NAME "framehandler_${GUNITTEST_FRAMEHANDLER_NAME}"
        LIBS ${GUNITTEST_FRAMEHANDLER_LIBS} test_framehandler pilSample gilSample
        WORKING_DIRECTORY ${GUNITTEST_FRAMEHANDLER_WORKING_DIRECTORY}
        FILES ${GUNITTEST_FRAMEHANDLER_FILES}
    )
endfunction()

include_directories(
    ${FRAMEHANDLER_BASE}/test
    ${FRAMEHANDLER_BASE}/test/ddhbuilders
    ${LSRENGINE}/database/test
    ${LSRENGINE}/common/test
    ${LSRENGINE}/display/test
    ${LSRENGINE}/lsr/api
)

GUNITTEST_FRAMEHANDLER(
    NAME FrameHandlerTest
    FILES FrameHandlerTest.cpp
          MockWidget.h
          WidgetTestBase.h
          ${LSRROOT}/test/database/Telltales/Output/Telltales.cpp
)

GUNITTEST_FRAMEHANDLER(
    NAME WidgetsTest
    FILES BitmapFieldTest.cpp
          FrameTest.cpp
          MockWidget.h
          PanelTest.cpp
          ReferenceBitmapFieldTest.cpp
          WidgetTest.cpp
          WidgetTestBase.h
          WindowTest.cpp
          ${LSRROOT}/test/database/Telltales/Output/Telltales.cpp
)
