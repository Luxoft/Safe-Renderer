/******************************************************************************
**
**   File:        InputStreamTest.cpp
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

#include <InputStream.h>

#include "InputStreamCorrupter.h"

using namespace lsr;

TEST(InputStreamTest, TestNormalInitialization)
{
    uint8_t buffer[1024] = {0u};
    InputStream stream(buffer, sizeof(buffer));

    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeof(buffer), stream.bytesToRead());
}

TEST(InputStreamTest, TestInitializationWithZeroBuffer)
{
    InputStream stream(NULL, 0u);

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(0u, stream.bytesToRead());
}

TEST(InputStreamTest, TestInitializationWithWrongBuffer)
{
    uint8_t buffer[1024] = {0u};
    InputStream stream1(NULL, sizeof(buffer));

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream1.getError());
    EXPECT_EQ(0u, stream1.bytesToRead());

    InputStream stream2(buffer, 0u);

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream2.getError());
    EXPECT_EQ(0u, stream2.bytesToRead());
}

TEST(InputStreamTest, TestBytesToRead)
{
    uint8_t buffer[5] = {0u};
    InputStream stream(buffer, sizeof(buffer));

    uint32_t expected = sizeof(buffer);
    EXPECT_EQ(expected, stream.bytesToRead());

    uint8_t data1 = 0;
    stream >> data1;
    expected -= sizeof(data1);
    EXPECT_EQ(expected, stream.bytesToRead());

    stream >> data1;
    expected -= sizeof(data1);
    EXPECT_EQ(expected, stream.bytesToRead());

    uint16_t data2 = 0;
    stream >> data2;
    expected -= sizeof(data2);
    EXPECT_EQ(expected, stream.bytesToRead());

    stream >> data1;
    expected -= sizeof(data1);
    EXPECT_EQ(0u, stream.bytesToRead());

    stream >> data1;
    EXPECT_EQ(0u, stream.bytesToRead());
}

TEST(InputStreamTest, TestBytesToReadWithCorruptedData)
{
    uint8_t buffer[32] = {0u};
    InputStream stream(buffer, sizeof(buffer));
    InputStreamCorrupter* corrupter = reinterpret_cast<InputStreamCorrupter*>(&stream);

    uint32_t expected = sizeof(buffer);
    EXPECT_EQ(expected, stream.bytesToRead());

    corrupter->setPos(31);
    expected = 1;
    EXPECT_EQ(expected, stream.bytesToRead());

    uint16_t data16 = 0;
    stream >> data16;
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(expected, stream.bytesToRead());

    corrupter->setError(COM_NO_ERROR);

    corrupter->setPos(32);
    expected = 0;
    EXPECT_EQ(expected, stream.bytesToRead());

    corrupter->setPos(320);
    EXPECT_EQ(expected, stream.bytesToRead());
}

TEST(InputStreamTest, TestRead)
{
    uint8_t buffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t actualBuffer[50] = {0u};

    InputStream stream(buffer, sizeof(buffer));
    uint32_t readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));

    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeof(actualBuffer), readedDataLen);

    for (uint8_t index = 0; index < sizeof(actualBuffer); ++index)
    {
        EXPECT_EQ(buffer[index], actualBuffer[index]);
    }
}

TEST(InputStreamTest, TestReadToEmptyBuffer1)
{
    uint8_t buffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t actualBuffer[50] = {0u};

    InputStream stream(buffer, sizeof(buffer));
    uint32_t readedDataLen = stream.read(NULL, sizeof(actualBuffer));

    EXPECT_EQ(COM_NOT_ENOUGH_INPUT_DATA, stream.getError());
    EXPECT_EQ(0u, readedDataLen);
}

TEST(InputStreamTest, TestReadToEmptyBuffer2)
{
    uint8_t buffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t actualBuffer[50] = {0u};

    InputStream stream(buffer, sizeof(buffer));
    uint32_t readedDataLen = stream.read(actualBuffer, 0);

    EXPECT_EQ(COM_NOT_ENOUGH_INPUT_DATA, stream.getError());
    EXPECT_EQ(0u, readedDataLen);
}

TEST(InputStreamTest, TestReadWithBigDataBySteps)
{
    uint8_t buffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t actualBuffer[100] = {0u};

    InputStream stream(buffer, sizeof(buffer));
    uint32_t readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));

    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeof(actualBuffer), readedDataLen);

    uint8_t expIndex = 0;
    for (uint8_t index = 0; index < sizeof(actualBuffer); ++index, ++expIndex)
    {
        EXPECT_EQ(buffer[expIndex], actualBuffer[index]);
    }

    readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));
    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeof(actualBuffer), readedDataLen);

    for (uint8_t actIndex = 0; actIndex < sizeof(actualBuffer); ++actIndex, ++expIndex)
    {
        EXPECT_EQ(buffer[expIndex], actualBuffer[actIndex]);
    }

    readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(0u, readedDataLen);
}

TEST(InputStreamTest, TestReadWithBigDataByOneStep)
{
    uint8_t buffer[255] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t actualBuffer[500] = {0u};

    InputStream stream(buffer, sizeof(buffer));
    uint32_t readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));

    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(0u, readedDataLen);

    for (uint16_t actIndex = 0; actIndex < sizeof(actualBuffer); ++actIndex)
    {
        EXPECT_EQ(0u, actualBuffer[actIndex]);
    }
}

TEST(InputStreamTest, TestReadFromEmptyBuffer)
{
    uint8_t buffer[50] = {0u};
    for (uint8_t index = 0; index < sizeof(buffer); ++index)
    {
        buffer[index] = index;
    }

    uint8_t actualBuffer[50] = {0u};

    InputStream stream(buffer, sizeof(buffer));
    uint32_t readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));

    EXPECT_EQ(COM_NO_ERROR, stream.getError());
    EXPECT_EQ(sizeof(actualBuffer), readedDataLen);

    for (uint8_t index = 0; index < sizeof(actualBuffer); ++index)
    {
        EXPECT_EQ(buffer[index], actualBuffer[index]);
    }

    readedDataLen = stream.read(actualBuffer, sizeof(actualBuffer));
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
    EXPECT_EQ(0u, readedDataLen);
}

TEST(InputStreamTest, TestSetError)
{
    uint8_t buffer[1024] = {0u};
    InputStream stream(buffer, sizeof(buffer));

    ComError error = COM_NOT_ENOUGH_BUFFER_SIZE;
    stream.setError(error);

    EXPECT_EQ(error, stream.getError());

    stream.setError(COM_NOT_ENOUGH_INPUT_DATA);
    EXPECT_EQ(error, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithBool)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, sizeof(buffer));

    bool expValue1 = true;
    bool expValue2 = false;
    bool expValue3 = true;
    bool expValue4 = true;
    bool expValue5 = false;

    bool actValue = false;
    bool actValue2 = false;
    stream >> actValue;
    EXPECT_EQ(expValue1, actValue);
    stream >> actValue;
    EXPECT_EQ(expValue2, actValue);
    stream >> actValue;
    EXPECT_EQ(expValue3, actValue);
    stream >> actValue >> actValue2;
    EXPECT_EQ(expValue4, actValue);
    EXPECT_EQ(expValue5, actValue2);
}

TEST(InputStreamTest, TestOperatorWithBoolWithEmptyBuffer)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[5] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    bool expValue = false;
    bool actValue = false;
    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithBoolWithWrongBuffer1)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(NULL, sizeof(buffer));

    bool expValue = false;
    bool actValue = false;
    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithBoolWithWrongBuffer2)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, 0);

    bool expValue = false;
    bool actValue = false;
    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt8)
{
    uint8_t buffer[5] = {0x05, 0xFD, 0x40, 0x7F, 0xAC };
    InputStream stream(buffer, sizeof(buffer));

    const int8_t value1 = int8_t(0x05);
    const int8_t value2 = int8_t(0xFD);
    const int8_t value3 = int8_t(0x40);
    const int8_t value4 = int8_t(0x7F);
    const int8_t value5 = int8_t(0xAC);

    int8_t actValue = 0;
    stream >> actValue;
    EXPECT_EQ(value1, actValue);
    stream >> actValue;
    EXPECT_EQ(value2, actValue);
    stream >> actValue;
    EXPECT_EQ(value3, actValue);
    stream >> actValue;
    EXPECT_EQ(value4, actValue);
    stream >> actValue;
    EXPECT_EQ(value5, actValue);
}

TEST(InputStreamTest, TestOperatorWithInt8WithEmptyBuffer)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[5] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    const int8_t expValue = 0;
    int8_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt8WithWrongBuffer1)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(NULL, sizeof(buffer));

    const int8_t expValue = 0;
    int8_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt8WithWrongBuffer2)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, 0);

    const int8_t expValue = 0;
    int8_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt8)
{
    uint8_t buffer[5] = {0x05, 0xFD, 0x40, 0x7F, 0xAC };
    InputStream stream(buffer, sizeof(buffer));

    const uint8_t value1 = 0x05;
    const uint8_t value2 = 0xFD;
    const uint8_t value3 = 0x40;
    const uint8_t value4 = 0x7F;
    const uint8_t value5 = 0xAC;

    uint8_t actValue = 0;
    stream >> actValue;
    EXPECT_EQ(value1, actValue);
    stream >> actValue;
    EXPECT_EQ(value2, actValue);
    stream >> actValue;
    EXPECT_EQ(value3, actValue);
    stream >> actValue;
    EXPECT_EQ(value4, actValue);
    stream >> actValue;
    EXPECT_EQ(value5, actValue);
}

TEST(InputStreamTest, TestOperatorWithUInt8WithEmptyBuffer)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[5] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    const uint8_t expValue = 0;
    uint8_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt8WithWrongBuffer1)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(NULL, sizeof(buffer));

    const uint8_t expValue = 0;
    uint8_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt8WithWrongBuffer2)
{
    uint8_t buffer[5] = {0x01, 0x00, 0x01, 0x01, 0x00 };
    InputStream stream(buffer, 0);

    const uint8_t expValue = 0;
    uint8_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt16)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(buffer, sizeof(buffer));

    const int16_t value1 = int16_t(0x05DF);
    const int16_t value2 = int16_t(0xFD4A);
    const int16_t value3 = int16_t(0x4004);
    const int16_t value4 = int16_t(0x7F12);
    const int16_t value5 = int16_t(0xAC01);

    int16_t actValue = 0;
    stream >> actValue;
    EXPECT_EQ(value1, actValue);
    stream >> actValue;
    EXPECT_EQ(value2, actValue);
    stream >> actValue;
    EXPECT_EQ(value3, actValue);
    stream >> actValue;
    EXPECT_EQ(value4, actValue);
    stream >> actValue;
    EXPECT_EQ(value5, actValue);
}

TEST(InputStreamTest, TestOperatorWithInt16WithEmptyBuffer)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[10] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    const int16_t expValue = 0;
    int16_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt16WithWrongBuffer1)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(NULL, sizeof(buffer));

    const int16_t expValue = 0;
    int16_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt16WithWrongBuffer2)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(buffer, 0);

    const int16_t expValue = 0;
    int16_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt16)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(buffer, sizeof(buffer));

    const uint16_t value1 = 0x05DF;
    const uint16_t value2 = 0xFD4A;
    const uint16_t value3 = 0x4004;
    const uint16_t value4 = 0x7F12;
    const uint16_t value5 = 0xAC01;

    uint16_t actValue = 0;
    stream >> actValue;
    EXPECT_EQ(value1, actValue);
    stream >> actValue;
    EXPECT_EQ(value2, actValue);
    stream >> actValue;
    EXPECT_EQ(value3, actValue);
    stream >> actValue;
    EXPECT_EQ(value4, actValue);
    stream >> actValue;
    EXPECT_EQ(value5, actValue);
}

TEST(InputStreamTest, TestOperatorWithUInt16WithEmptyBuffer)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[10] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    const uint16_t expValue = 0;
    uint16_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt16WithWrongBuffer1)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(NULL, sizeof(buffer));

    const uint16_t expValue = 0;
    uint16_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt16WithWrongBuffer2)
{
    uint8_t buffer[10] = {
        0x05, 0xDF,
        0xFD, 0x4A,
        0x40, 0x04,
        0x7F, 0x12,
        0xAC, 0x01
    };
    InputStream stream(buffer, 0);

    const uint16_t expValue = 0;
    uint16_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt32)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(buffer, sizeof(buffer));

    const int32_t value1 = 0x05DF567D;
    const int32_t value2 = 0xFD4A7E65;
    const int32_t value3 = 0x4004AA78;
    const int32_t value4 = 0x7F1200FF;
    const int32_t value5 = 0xAC0191DD;

    int32_t actValue = 0;
    stream >> actValue;
    EXPECT_EQ(value1, actValue);
    stream >> actValue;
    EXPECT_EQ(value2, actValue);
    stream >> actValue;
    EXPECT_EQ(value3, actValue);
    stream >> actValue;
    EXPECT_EQ(value4, actValue);
    stream >> actValue;
    EXPECT_EQ(value5, actValue);
}

TEST(InputStreamTest, TestOperatorWithInt32WithEmptyBuffer)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[20] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    const int32_t expValue = 0;
    int32_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt32WithWrongBuffer1)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(NULL, sizeof(buffer));

    int32_t expValue = 0;
    int32_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithInt32WithWrongBuffer2)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(buffer, 0);

    const int32_t expValue = 0;
    int32_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt32)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(buffer, sizeof(buffer));

    const uint32_t value1 = 0x05DF567D;
    const uint32_t value2 = 0xFD4A7E65;
    const uint32_t value3 = 0x4004AA78;
    const uint32_t value4 = 0x7F1200FF;
    const uint32_t value5 = 0xAC0191DD;

    uint32_t actValue = 0;
    stream >> actValue;
    EXPECT_EQ(value1, actValue);
    stream >> actValue;
    EXPECT_EQ(value2, actValue);
    stream >> actValue;
    EXPECT_EQ(value3, actValue);
    stream >> actValue;
    EXPECT_EQ(value4, actValue);
    stream >> actValue;
    EXPECT_EQ(value5, actValue);
}

TEST(InputStreamTest, TestOperatorWithUInt32WithEmptyBuffer)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(buffer, sizeof(buffer));

    uint8_t actualBuffer[20] = {0u};
    stream.read(actualBuffer, sizeof(actualBuffer));

    const uint32_t expValue = 0;
    uint32_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithUInt32WithWrongBuffer1)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(NULL, sizeof(buffer));

    const uint32_t expValue = 0;
    uint32_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}

TEST(InputStreamTest, TestOperatorWithIntU32WithWrongBuffer2)
{
    uint8_t buffer[20] = {
        0x05, 0xDF, 0x56, 0x7D,
        0xFD, 0x4A, 0x7E, 0x65,
        0x40, 0x04, 0xAA, 0x78,
        0x7F, 0x12, 0x00, 0xFF,
        0xAC, 0x01, 0x91, 0xDD,
    };
    InputStream stream(buffer, 0);

    const uint32_t expValue = 0;
    uint32_t actValue = 0;

    stream >> actValue;
    EXPECT_EQ(expValue, actValue);
    EXPECT_EQ(COM_NOT_ENOUGH_BUFFER_SIZE, stream.getError());
}
