/******************************************************************************
**
**   File:        OutputStreamTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <OutputStream.h>

#include "OutputStreamCorrupter.h"

using namespace lsr;

TEST(OutputStreamTest, TestNormalInitialization)
{
    uint8_t buffer[1024] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(0u, stream.bytesWritten());
    EXPECT_EQ(sizeof(buffer), stream.bytesAvailable());
    EXPECT_EQ(buffer, stream.getBuffer());
}

TEST(OutputStreamTest, TestNoBufferModificationDuringInitialization)
{
    uint8_t buffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t proxyBuffer[255] = {0u};
    memcpy (proxyBuffer, buffer, sizeof(proxyBuffer));

    OutputStream stream(proxyBuffer, sizeof(proxyBuffer));

    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        EXPECT_EQ(buffer[index], proxyBuffer[index]);
    }
}

TEST(OutputStreamTest, TestInitializationWithZeroBuffer)
{
    OutputStream stream(NULL, 0u);

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(0u, stream.bytesWritten());
    EXPECT_EQ(0u, stream.bytesAvailable());
    EXPECT_EQ(NULL, stream.getBuffer());
}

TEST(OutputStreamTest, TestInitializationWithWrongBuffer)
{
    uint8_t buffer[1024] = {0u};
    OutputStream stream1(NULL, sizeof(buffer));

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream1.getError());
    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(0u, stream1.bytesAvailable());
    EXPECT_EQ(NULL, stream1.getBuffer());

    OutputStream stream2(buffer, 0u);

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream2.getError());
    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(0u, stream2.bytesAvailable());
    EXPECT_EQ(NULL, stream2.getBuffer());
}

TEST(OutputStreamTest, TestBytesWritten)
{
    uint8_t buffer[10] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    uint32_t expected = 0u;
    EXPECT_EQ(expected, stream.bytesWritten());

    uint8_t data[4] = {5u};
    stream.write(data, sizeof(data));
    expected += sizeof(data);

    EXPECT_EQ(expected, stream.bytesWritten());

    stream.write(data, sizeof(data));
    expected += sizeof(data);

    EXPECT_EQ(expected, stream.bytesWritten());
}

TEST(InputStreamTest, TestBytesWrittenWithCorruptedData)
{
    uint8_t buffer[32] = {0u};
    OutputStream stream(buffer, sizeof(buffer));
    OutputStreamCorrupter* corrupter = reinterpret_cast<OutputStreamCorrupter*>(&stream);

    uint32_t expected = 0u;
    EXPECT_EQ(expected, stream.bytesWritten());

    corrupter->setPos(31);
    expected = 31;
    EXPECT_EQ(expected, stream.bytesWritten());

    uint16_t data16 = 50u;
    stream << data16;
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(expected, stream.bytesWritten());

    corrupter->setError(COM_NO_ERROR);

    uint8_t data8 = 34u;
    stream << data8;
    expected = 32;
    EXPECT_EQ(expected, stream.bytesWritten());

    corrupter->setPos(320);
    EXPECT_EQ(expected, stream.bytesWritten());
}

TEST(OutputStreamTest, TestBytesAvailable)
{
    uint8_t buffer[10] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    uint32_t expected = sizeof(buffer);
    EXPECT_EQ(expected, stream.bytesAvailable());

    uint8_t data[4] = {5u};
    stream.write(data, sizeof(data));
    expected -= sizeof(data);

    EXPECT_EQ(expected, stream.bytesAvailable());

    stream.write(data, sizeof(data));
    expected -= sizeof(data);

    EXPECT_EQ(expected, stream.bytesAvailable());

    stream.write(data, sizeof(data));
    expected = 2;

    EXPECT_EQ(expected, stream.bytesAvailable());
}

TEST(InputStreamTest, TestBytesAvailableWithCorruptedData)
{
    uint8_t buffer[32] = {0u};
    OutputStream stream(buffer, sizeof(buffer));
    OutputStreamCorrupter* corrupter = reinterpret_cast<OutputStreamCorrupter*>(&stream);

    uint32_t expected = sizeof(buffer);
    EXPECT_EQ(expected, stream.bytesAvailable());

    corrupter->setPos(31);
    expected = 1;
    EXPECT_EQ(expected, stream.bytesAvailable());

    uint16_t data16 = 0;
    stream << data16;
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(expected, stream.bytesAvailable());

    corrupter->setError(COM_NO_ERROR);

    corrupter->setPos(32);
    expected = 0;
    EXPECT_EQ(expected, stream.bytesAvailable());

    corrupter->setPos(320);
    EXPECT_EQ(expected, stream.bytesAvailable());
}

TEST(OutputStreamTest, TestWrite)
{
    uint8_t buffer[255] = {0u};

    uint8_t expectedBuffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        expectedBuffer[index] = index;
    }

    OutputStream stream(buffer, sizeof(buffer));
    uint32_t writtenDataSize = stream.write(expectedBuffer, sizeof(expectedBuffer));

    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeof(expectedBuffer), writtenDataSize);

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestWriteZeroData1)
{
    uint8_t buffer[255] = {0u};

    uint8_t expectedBuffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        expectedBuffer[index] = index;
    }

    OutputStream stream(buffer, sizeof(buffer));
    uint32_t writtenDataSize = stream.write(NULL, sizeof(expectedBuffer));

    EXPECT_EQ(COM_NOT_ENOUGH_INPUT_DATA, stream.getError());
    EXPECT_EQ(0u, writtenDataSize);
}

TEST(OutputStreamTest, TestWriteZeroData2)
{
    uint8_t buffer[255] = {0u};

    uint8_t expectedBuffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        expectedBuffer[index] = index;
    }

    OutputStream stream(buffer, sizeof(buffer));
    uint32_t writtenDataSize = stream.write(expectedBuffer, 0);

    EXPECT_EQ(COM_NOT_ENOUGH_INPUT_DATA, stream.getError());
    EXPECT_EQ(0u, writtenDataSize);
}

TEST(OutputStreamTest, TestWriteWithBigDataBySteps)
{
    uint8_t buffer[150] = {0u};

    uint8_t expectedBuffer[180] = {0u};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        expectedBuffer[index] = index;
    }
    const uint32_t sizeOfDataToWrite = 60;
    const uint8_t* data = expectedBuffer;
    OutputStream stream(buffer, sizeof(buffer));
    uint32_t writtenDataSize = stream.write(data, sizeOfDataToWrite);
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeOfDataToWrite, writtenDataSize);

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    for (uint8_t index = 0; index < stream.bytesWritten(); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }

    data += sizeOfDataToWrite;
    writtenDataSize = stream.write(data, sizeOfDataToWrite);
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeOfDataToWrite, writtenDataSize);

    for (uint8_t index = 0; index < stream.bytesWritten(); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }

    data += sizeOfDataToWrite;
    writtenDataSize = stream.write(data, sizeOfDataToWrite);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(0u, writtenDataSize);
    for (uint8_t index = 0; index < stream.bytesWritten(); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
    for (uint8_t index = stream.bytesWritten(); index < sizeof(buffer); ++index)
    {
        EXPECT_EQ(0u, actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestWriteWithBigDataByOneStep)
{
    uint8_t buffer[50] = {0u};

    uint8_t expectedBuffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        expectedBuffer[index] = index;
    }

    OutputStream stream(buffer, sizeof(buffer));
    stream.write(expectedBuffer, sizeof(expectedBuffer));
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        EXPECT_EQ(0u, actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestWriteToFullBuffer)
{
    uint8_t buffer[255] = {0u};

    uint8_t expectedBuffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        expectedBuffer[index] = index;
    }

    OutputStream stream(buffer, sizeof(buffer));
    stream.write(expectedBuffer, sizeof(expectedBuffer));
    EXPECT_EQ(COM_NO_ERROR, stream.getError());

    stream.write(expectedBuffer, sizeof(expectedBuffer));
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());

    stream.write(expectedBuffer, sizeof(expectedBuffer));
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(OutputStreamTest, TestOperatorWithBool)
{
    uint8_t buffer[5] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    bool value = true;
    stream << value;
    value = false;
    stream << value;
    value = true;
    stream << value << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    uint8_t expectedBuffer[4] = {0x01, 0x00, 0x01, 0x01};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestOperatorWithInt8)
{
    uint8_t buffer[5] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    int8_t value = 0x05;
    stream << value;
    value = int8_t(0xFD);
    stream << value;
    value = int8_t(0x40);
    stream << value;
    value = int8_t(0x7F);
    stream << value;
    value = int8_t(0xAC);
    stream << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    const uint8_t expectedBuffer[5] = {0x05, 0xFD, 0x40, 0x7F, 0xAC};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestOperatorWithUInt8)
{
    uint8_t buffer[5] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    uint8_t value = 0x05;
    stream << value;
    value = 0xFD;
    stream << value;
    value = 0x40;
    stream << value;
    value = 0x7F;
    stream << value;
    value = 0xAC;
    stream << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    const uint8_t expectedBuffer[5] = {0x05, 0xFD, 0x40, 0x7F, 0xAC};
    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestOperatorWithInt16)
{
    uint8_t buffer[6] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    int16_t value = 0x05AC;
    stream << value;
    value = int16_t(0xFD03);
    stream << value;
    value = int16_t(0x4004);
    stream << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    const uint8_t expectedBuffer[6] = {
        0x05, 0xAC,
        0xFD, 0x03,
        0x40, 0x04
    };

    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestOperatorWithUInt16)
{
    uint8_t buffer[6] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    uint16_t value = 0x05AC;
    stream << value;
    value = 0xFD03;
    stream << value;
    value = 0x4004;
    stream << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    const uint8_t expectedBuffer[6] = {
        0x05, 0xAC,
        0xFD, 0x03,
        0x40, 0x04
    };

    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestOperatorWithInt32)
{
    uint8_t buffer[12] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    int32_t value = 0x05ACFD03;
    stream << value;
    value = 0xFD030598;
    stream << value;
    value = 0x400479AC;
    stream << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    const uint8_t expectedBuffer[12] = {
        0x05, 0xAC, 0xFD, 0x03,
        0xFD, 0x03, 0x05, 0x98,
        0x40, 0x04, 0x79, 0xAC
    };

    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

TEST(OutputStreamTest, TestOperatorWithUInt32)
{
    uint8_t buffer[12] = {0u};
    OutputStream stream(buffer, sizeof(buffer));

    uint32_t value = 0x05ACFD03;
    stream << value;
    value = 0xFD030598;
    stream << value;
    value = 0x400479AC;
    stream << value;

    const uint8_t* actualBuffer = static_cast<const uint8_t*>(stream.getBuffer());

    const uint8_t expectedBuffer[12] = {
        0x05, 0xAC, 0xFD, 0x03,
        0xFD, 0x03, 0x05, 0x98,
        0x40, 0x04, 0x79, 0xAC
    };

    for (uint8_t index = 0; index < sizeof(expectedBuffer); ++index)
    {
        EXPECT_EQ(expectedBuffer[index], actualBuffer[index]);
    }
}

