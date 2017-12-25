/******************************************************************************
**
**   File:        OdiMsgHeaderTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <OdiMsgHeader.h>
#include <OdiTypes.h>

using namespace psc;

TEST(OdiMsgHeaderTest, TestInitializing)
{
    const DataMessageTypes::Val expectedOdiType = DataMessageTypes::UNKNOWN;

    OdiMsgHeader header(expectedOdiType);

    EXPECT_EQ(expectedOdiType, header.getOdiType());
}

TEST(OdiMsgHeaderTest, TestConstrFromStream)
{
    U8 buffer[1] = {0U};

    const DataMessageTypes::Val expectedOdiType = DataMessageTypes::EVENT;

    buffer[0] = static_cast<U8>(expectedOdiType);

    InputStream stream(buffer, sizeof(buffer));
    OdiMsgHeader header = OdiMsgHeader::fromStream(stream);

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(expectedOdiType, header.getOdiType());
}

TEST(OdiMsgHeaderTest, TestGetSize)
{
    const U16 expectedSize = 1U;
    OdiMsgHeader header1(DataMessageTypes::EVENT);
    EXPECT_EQ(expectedSize, header1.getSize());

    OdiMsgHeader header2(DataMessageTypes::UNKNOWN);
    EXPECT_EQ(expectedSize, header2.getSize());
}

TEST(OdiMsgHeaderTest, TestSerialize)
{
    U8 buffer[1] = {0U};
    OutputStream stream(buffer, sizeof(buffer));

    const DataMessageTypes::Val expectedOdiType = DataMessageTypes::EVENT;

    OdiMsgHeader header(expectedOdiType);

    const U16 expectedMsgSize = header.getSize();
    stream << header;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = static_cast<U8>(expectedOdiType);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST(OdiMsgHeaderTest, TestSerializeWithWrongBuffer)
{
    U8 buffer[1] = {0U};

    const DataMessageTypes::Val expectedOdiType = DataMessageTypes::EVENT;

    OdiMsgHeader header(expectedOdiType);

    OutputStream stream1(NULL, sizeof(buffer));
    stream1 << header;

    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    OutputStream stream2(buffer, 0u);
    stream2 << header;

    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}

TEST(OdiMsgHeaderTest, TestDeserializeWith)
{
    U8 buffer[1] = {0U};

    const DataMessageTypes::Val expectedOdiType = DataMessageTypes::EVENT;

    buffer[0] = static_cast<U8>(expectedOdiType);

    InputStream stream(buffer, sizeof(buffer));
    OdiMsgHeader header(DataMessageTypes::UNKNOWN);
    stream >> header;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(expectedOdiType, header.getOdiType());
}

TEST(OdiMsgHeaderTest, TestSerializeDeserialize)
{
    U8 buffer[1] = {0U};
    OutputStream outStream(buffer, sizeof(buffer));

    const DataMessageTypes::Val expectedOdiType = DataMessageTypes::EVENT;

    OdiMsgHeader outHeader(expectedOdiType);

    outStream << outHeader;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), outStream.getError());

    OdiMsgHeader inHeader(DataMessageTypes::UNKNOWN);

    InputStream inStream(buffer, sizeof(buffer));
    inStream >> inHeader;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), inStream.getError());

    EXPECT_EQ(expectedOdiType, inHeader.getOdiType());
}

TEST(OdiMsgHeaderTest, TestDeserializeWithWrongDataMsgType)
{
    U8 buffer[1] = {0U};

    buffer[0] = static_cast<U8>(DataMessageTypes::INDICATION + 1);

    OdiMsgHeader header(DataMessageTypes::UNKNOWN);

    InputStream stream(buffer, sizeof(buffer));
    stream >> header;

    EXPECT_EQ(PSCError(PSC_COMM_INVALID_FIELD_IN_MSG), stream.getError());
}

TEST(OdiMsgHeaderTest, TestDeserializeWithWrongBuffer)
{
    U8 buffer[1] = {0U};

    buffer[0] = static_cast<U8>(DataMessageTypes::INDICATION);

    InputStream stream1(NULL, sizeof(buffer));
    OdiMsgHeader header1(DataMessageTypes::UNKNOWN);
    stream1 >> header1;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    InputStream stream2(buffer, 0U);
    OdiMsgHeader header2(DataMessageTypes::UNKNOWN);
    stream2 >> header2;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}
