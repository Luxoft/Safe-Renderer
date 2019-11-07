
include(GoogleTest)

GUNITTEST(
    NAME "communication"
    LIBS engine pilSample odicomm
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    FILES OutputStreamTest.cpp
          InputStreamTest.cpp
          MessageHeaderTest.cpp
)

include_directories(
    "communication_${GUNITTEST_COMMUNICATION_NAME}"
    ${LSRROOT}/pil/src/sample
)
