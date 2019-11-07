
include(GoogleTest)

GUNITTEST(NAME "odi"
    LIBS engine odicomm
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    FILES RegistrationMsgBuilderTest.cpp
          RegistrationMsgBufferTest.cpp
          RegistrationMsgReaderTest.cpp
          DataResponseMessageTest.cpp
          EventMessageTest.cpp
          IndicationDataMessageTest.cpp
          AliveMessageTest.cpp
          OdiMessageUtilsTest.cpp
          OdiMsgHeaderTest.cpp
)
