/******************************************************************************
**
**   File:        IndicationDataMessageTest.cpp
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

#include <IndicationDataMessage.h>
#include <OdiTypes.h>

using namespace psc;

class IndicationDataMessageTest : public ::testing::Test
{
protected:
    void SetUp()
    {
        m_fuId = 0x8118;
        memset(m_indications, 0, IndicationDataMessage::NUMBER_INDICATION_BYTES);

        m_msgSize = 14;
        m_countIndications = IndicationDataMessage::NUMBER_INDICATION_BYTES * 8;

        m_msg = new IndicationDataMessage();
    }

    void TearDown()
    {
        delete m_msg;
    }

    void InitMessage()
    {
        m_msg->setFuId(m_fuId);
        for (U8 i = 1; i <= m_countIndications; ++i)
        {
            if (0 == i % 2)
            {
                m_msg->setIndication(i, true);
            }
        }
    }

    FUClassId m_fuId;
    U8 m_indications[IndicationDataMessage::NUMBER_INDICATION_BYTES];
    U16 m_msgSize;
    U8 m_countIndications;
    IndicationDataMessage* m_msg;
};

TEST_F(IndicationDataMessageTest, TestInitializing)
{
    const MessageTypes::Val expectedType = MessageTypes::ODI;
    const U16 expectedSize = m_msgSize;
    const FUClassId expectedFuId = 0;
    bool expectedIndicator = false;

    EXPECT_EQ(expectedType, m_msg->getType());
    EXPECT_EQ(expectedSize, m_msg->getSize());
    EXPECT_EQ(expectedFuId, m_msg->getFuId());
    for (U8 i = 1; i <= m_countIndications; ++i)
    {
        EXPECT_EQ(expectedIndicator, m_msg->getIndication(static_cast<IndicationId>(i)));
    }
}

TEST_F(IndicationDataMessageTest, TestConstrFromStream)
{
    U8 buffer[14] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = U8(0x55);
    buffer[3] = U8(0x55);
    buffer[4] = U8(0x55);
    buffer[5] = U8(0x55);
    buffer[6] = U8(0x55);
    buffer[7] = U8(0x55);
    buffer[8] = U8(0x55);
    buffer[9] = U8(0x55);
    buffer[10] = U8(0x55);
    buffer[11] = U8(0x55);
    buffer[12] = U8(0x55);
    buffer[13] = U8(0x55);


    InputStream stream(buffer, sizeof(buffer));
    IndicationDataMessage msg = IndicationDataMessage::fromStream(stream);

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_fuId, msg.getFuId());
    bool expectedValue = false;
    for (U8 indicationId = 1; indicationId <= m_countIndications; ++indicationId)
    {
        expectedValue = (0 == indicationId % 2);
        EXPECT_EQ(expectedValue, msg.getIndication(indicationId));
    }
}


TEST_F(IndicationDataMessageTest, TestGetType)
{
    const MessageTypes::Val expectedType = MessageTypes::ODI;
    EXPECT_EQ(expectedType, m_msg->getType());
}

TEST_F(IndicationDataMessageTest, TestSetFuId)
{
    InitMessage();
    EXPECT_EQ(m_fuId, m_msg->getFuId());
}

TEST_F(IndicationDataMessageTest, TestSetIndicators1)
{
    const bool value = true;

    for (U8 indicationId = 1;
         indicationId <= m_countIndications;
         ++indicationId)
    {
        m_msg->setIndication(indicationId, value);
        EXPECT_EQ(value, m_msg->getIndication(indicationId));
    }
}

TEST_F(IndicationDataMessageTest, TestSetIndicators2)
{
    bool value = true;

    for (U8 indicationId = 1;
         indicationId <= m_countIndications;
         ++indicationId)
    {
        m_msg->setIndication(indicationId, value);
    }

    value = false;
    for (U8 indicationId = 1;
         indicationId <= m_countIndications;
         ++indicationId)
    {
        m_msg->setIndication(indicationId, value);
        EXPECT_EQ(value, m_msg->getIndication(indicationId));
    }
}

TEST_F(IndicationDataMessageTest, TestSetIndicatorsWithWrongID)
{
    m_msg->setIndication(0, true);
    m_msg->setIndication(IndicationDataMessage::NUMBER_INDICATORS + 1, true);

    bool value = false;
    for (U8 indicationId = 1;
         indicationId <= m_countIndications;
         ++indicationId)
    {
        EXPECT_EQ(value, m_msg->getIndication(indicationId));
    }
}

TEST_F(IndicationDataMessageTest, TestGetIndicatorsWithWrongID)
{
    bool value = false;

    EXPECT_EQ(value, m_msg->getIndication(0));
    EXPECT_EQ(value, m_msg->getIndication(IndicationDataMessage::NUMBER_INDICATORS + 1));
}

TEST_F(IndicationDataMessageTest, TestGetSizeAfterInit)
{
    InitMessage();
    EXPECT_EQ(m_msgSize, m_msg->getSize());
}

TEST_F(IndicationDataMessageTest, TestSerialize)
{
    InitMessage();

    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    expectedBuffer[0] = static_cast<U8>(m_fuId >> 8);
    expectedBuffer[1] = static_cast<U8>(m_fuId);
    expectedBuffer[2] = U8(0x55);
    expectedBuffer[3] = U8(0x55);
    expectedBuffer[4] = U8(0x55);
    expectedBuffer[5] = U8(0x55);
    expectedBuffer[6] = U8(0x55);
    expectedBuffer[7] = U8(0x55);
    expectedBuffer[8] = U8(0x55);
    expectedBuffer[9] = U8(0x55);
    expectedBuffer[10] = U8(0x55);
    expectedBuffer[11] = U8(0x55);
    expectedBuffer[12] = U8(0x55);
    expectedBuffer[13] = U8(0x55);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(IndicationDataMessageTest, TestSerializeNotInitedObject)
{
    U8 buffer[1024] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    const U16 expectedMsgSize = m_msg->getSize();
    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());
    EXPECT_EQ(expectedMsgSize, stream.bytesWritten());

    U8* expectedBuffer = new U8[expectedMsgSize];
    memset(expectedBuffer, 0, expectedMsgSize);

    for (U8 index=0; index < expectedMsgSize; ++index)
    {
        EXPECT_EQ(expectedBuffer[index], buffer[index]);
    }

    delete[] expectedBuffer;
}

TEST_F(IndicationDataMessageTest, TestSerializeWithNotEnoughBuffer)
{
    InitMessage();

    U8 buffer[13] = {0};
    OutputStream stream(buffer, sizeof(buffer));

    stream << *m_msg;
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(IndicationDataMessageTest, TestSerializeWithWrongBuffer)
{
    InitMessage();

    U8 buffer[15] = {0};
    OutputStream stream1(NULL, sizeof(buffer));
    stream1 << *m_msg;

    EXPECT_EQ(0u, stream1.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    OutputStream stream2(buffer, 0u);
    stream2 << *m_msg;

    EXPECT_EQ(0u, stream2.bytesWritten());
    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}


TEST_F(IndicationDataMessageTest, TestDeserialize)
{
    U8 buffer[14] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = U8(0x55);
    buffer[3] = U8(0x55);
    buffer[4] = U8(0x55);
    buffer[5] = U8(0x55);
    buffer[6] = U8(0x55);
    buffer[7] = U8(0x55);
    buffer[8] = U8(0x55);
    buffer[9] = U8(0x55);
    buffer[10] = U8(0x55);
    buffer[11] = U8(0x55);
    buffer[12] = U8(0x55);
    buffer[13] = U8(0x55);


    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_fuId, m_msg->getFuId());
    bool expectedValue = false;
    for (U8 indicationId = 1; indicationId <= m_countIndications; ++indicationId)
    {
        expectedValue = (0 == indicationId % 2);
        EXPECT_EQ(expectedValue, m_msg->getIndication(indicationId));
    }
}

TEST_F(IndicationDataMessageTest, TestSerializeDeserialize)
{
    InitMessage();

    U8 buffer[1024] = {0};
    OutputStream outStream(buffer, sizeof(buffer));

    outStream << *m_msg;
    EXPECT_EQ(PSCError(PSC_NO_ERROR), outStream.getError());

    IndicationDataMessage msg;

    InputStream stream(buffer, sizeof(buffer));
    stream >> msg;

    EXPECT_EQ(PSCError(PSC_NO_ERROR), stream.getError());

    EXPECT_EQ(m_msg->getFuId(), msg.getFuId());
    for (U8 indicationId = 1; indicationId <= m_countIndications; ++indicationId)
    {
        EXPECT_EQ(m_msg->getIndication(indicationId), msg.getIndication(indicationId));
    }
}

TEST_F(IndicationDataMessageTest, TestDeserializeWithNotFullSize)
{
    U8 buffer[13] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = U8(0x55);
    buffer[3] = U8(0x55);
    buffer[4] = U8(0x55);
    buffer[5] = U8(0x55);
    buffer[6] = U8(0x55);
    buffer[7] = U8(0x55);
    buffer[8] = U8(0x55);
    buffer[9] = U8(0x55);
    buffer[10] = U8(0x55);
    buffer[11] = U8(0x55);
    buffer[12] = U8(0x55);

    InputStream stream(buffer, sizeof(buffer));
    stream >> *m_msg;

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream.getError());
}

TEST_F(IndicationDataMessageTest, TestDeserializeWithWrongBuffer)
{
    U8 buffer[14] = {0};

    buffer[0] = static_cast<U8>(m_fuId >> 8);
    buffer[1] = static_cast<U8>(m_fuId);
    buffer[2] = U8(0x55);
    buffer[3] = U8(0x55);
    buffer[4] = U8(0x55);
    buffer[5] = U8(0x55);
    buffer[6] = U8(0x55);
    buffer[7] = U8(0x55);
    buffer[8] = U8(0x55);
    buffer[9] = U8(0x55);
    buffer[10] = U8(0x55);
    buffer[11] = U8(0x55);
    buffer[12] = U8(0x55);
    buffer[13] = U8(0x55);

    const MessageTypes::Val expectedType = MessageTypes::ODI;
    const U16 expectedSize = m_msgSize;
    const FUClassId expectedFuId = 0;
    bool expectedIndicator = false;

    InputStream stream1(NULL, sizeof(buffer));
    IndicationDataMessage msg1;
    stream1 >> msg1;

    EXPECT_EQ(expectedType, m_msg->getType());
    EXPECT_EQ(expectedSize, m_msg->getSize());
    EXPECT_EQ(expectedFuId, m_msg->getFuId());
    for (U8 i = 1; i <= m_countIndications; ++i)
    {
        EXPECT_EQ(expectedIndicator, m_msg->getIndication(static_cast<IndicationId>(i)));
    }

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream1.getError());

    InputStream stream2(buffer, 0u);
    IndicationDataMessage msg2;
    stream2 >> msg2;

    EXPECT_EQ(expectedType, m_msg->getType());
    EXPECT_EQ(expectedSize, m_msg->getSize());
    EXPECT_EQ(expectedFuId, m_msg->getFuId());
    for (U8 i = 1; i <= m_countIndications; ++i)
    {
        EXPECT_EQ(expectedIndicator, m_msg->getIndication(static_cast<IndicationId>(i)));
    }

    EXPECT_EQ(PSCError(PSC_COMM_NOT_ENOUGH_BUFFER_SIZE), stream2.getError());
}

