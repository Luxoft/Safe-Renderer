/******************************************************************************
**
**   File:        EngineAppTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   Luxoft Safe Renderer is free software: you can redistribute it and/or
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

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <fstream>
#include "Database.h"
#include "ResourceBuffer.h"
#include "lsr.h"
#include "gil.h"
#include "OutputStream.h"
#include "OdiTypes.h"
#include "OdiMsgHeader.h"
#include "MessageHeader.h"
#include "DataResponseMessage.h"
#include "DataHandler.h"
#include "FrameHandler.h"
#include "DisplayManager.h"

using namespace lsr;

const char* ddhbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.ddhbin";
const char* imgbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.imgbin";

class EngineTest : public ::testing::Test
{
public:
    static void SetUpTestCase() {
        static std::string m_ddhbinData;
        static std::string m_imgbinData;
        std::ifstream ifs1(ddhbin, std::ios::binary);
        m_ddhbinData.assign((std::istreambuf_iterator<char>(ifs1)), (std::istreambuf_iterator<char>()));
        m_ddhbin = ResourceBuffer(m_ddhbinData.c_str(), m_ddhbinData.size());
        std::ifstream ifs2(imgbin, std::ios::binary);
        m_imgbinData.assign((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
        m_imgbin = ResourceBuffer(m_imgbinData.c_str(), m_imgbinData.size());
    }

    static void TearDownTestCase() {
    }

    void SetUp() P_OVERRIDE
    {
        // pilInit();
        gilInit(NULL);
    }

    void TearDown() P_OVERRIDE
    {
        // pilClose();
    }

    /* Comment to erase mailbox from the lsr interface

    void sendValue(PILMailbox engineMailbox, PILMailbox sender, FUClassId fu, DataId dataId, U32 value, DynamicDataTypeEnumeration type)
    {
        U8 buf[256];
        OutputStream stream(buf, sizeof(buf));
        DataResponseMessage rsp;
        rsp.setFuId(fu);
        rsp.setDataId(dataId);
        rsp.setDataType(type);
        rsp.setDataValue(value);
        rsp.setInvalidFlag(false);
        OdiMsgHeader odiHeader(DataMessageTypes::DYN_DATA_RESP);
        MessageHeader msgHeader(MessageTypes::ODI, odiHeader.getSize() + rsp.getSize());
        stream << msgHeader << odiHeader << rsp;
        pilMailboxWrite(engineMailbox, sender, static_cast<const U8*>(stream.getBuffer()), stream.bytesWritten());
    }

    void sendBreakOn(PILMailbox engineMailbox, PILMailbox sender, bool value)
    {
        sendValue(engineMailbox, sender, 42, 1, value ? 1 : 0, DATATYPE_BOOLEAN);
    }

    void sendBreakOff(PILMailbox engineMailbox, PILMailbox sender, bool value)
    {
        sendValue(engineMailbox, sender, 42, 2, value ? 1 : 0, DATATYPE_BOOLEAN);
    }

    void sendAirbag(PILMailbox engineMailbox, PILMailbox sender, bool value)
    {
        sendValue(engineMailbox, sender, 42, 3, value ? 1 : 0, DATATYPE_BOOLEAN);
    }*/

    std::string m_ddhbinData;
    std::string m_imgbinData;

protected:
    static ResourceBuffer m_ddhbin;
    static ResourceBuffer m_imgbin;
};

ResourceBuffer EngineTest::m_ddhbin;
ResourceBuffer EngineTest::m_imgbin;

TEST(lsr, emptyDatabase)
{
    LSRDatabase db = { 0, 0, 0, 0 };
    LSRError err;
    LSREngine engine = lsrCreate(&db, &err);
    // Even if the database is garbage, there will be an engine instance to check for errors
    EXPECT_TRUE(engine == NULL);
    // EXPECT_EQ(LSR_DB_DDHBIN_EMPTY, lsrGetError(engine));
}

/*
Comment to erase mailbox from the lsr interface

TEST_F(EngineTest, noFUConnection)
{
    LSRDatabase db = { m_ddhbin.getData()
        , m_ddhbin.getSize()
        , m_imgbin.getData()
        , m_imgbin.getSize()
    };
    PILMailbox mailbox = 1;
    testing::internal::CaptureStdout();
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxInit(mailbox));
	LSRError err;
    LSREngine engine = lsrCreate(&db, mailbox, &err);
    ASSERT_TRUE(engine != NULL);
    ASSERT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    // in a real project this will be a loop
    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    EXPECT_EQ(LSR_FALSE, lsrVerify(engine)); // one icon is drawn - 2 are expected
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    // loop end

    // Airbag icon will get visible after 10 failures
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(LSR_FALSE, lsrRender(engine)); // no updates
        EXPECT_EQ(LSR_FALSE, lsrVerify(engine)); // one icon is drawn - 2 are expected
        EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    }
    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_TRUE, lsrVerify(engine)); // both icons are drawn

    EXPECT_EQ(LSR_NO_ERROR, lsrDelete(engine));

    std::string output = testing::internal::GetCapturedStdout();
    //std::cout << "###### Render dump begin ######" << std::endl;
    //std::cout << output;
    //std::cout << "####### Render dump end #######" << std::endl;
    // TODO : verify captured stdout
}

TEST_F(EngineTest, fuConnection)
{
    LSRDatabase db = { m_ddhbin.getData()
        , m_ddhbin.getSize()
        , m_imgbin.getData()
        , m_imgbin.getSize()
    };
    PILMailbox engineMailbox = 1;
    PILMailbox sender = 2;
    testing::internal::CaptureStdout();
    EXPECT_EQ(PIL_NO_ERROR, pilMailboxInit(engineMailbox));
	LSRError err;
    LSREngine engine = lsrCreate(&db, engineMailbox, &err);
    ASSERT_TRUE(engine != NULL);
    ASSERT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    sendBreakOn(engineMailbox, sender, false);
    sendBreakOff(engineMailbox, sender, true);
    sendAirbag(engineMailbox, sender, false);

    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_TRUE, lsrVerify(engine)); // no icon is visible
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    sendBreakOn(engineMailbox, sender, true);
    sendBreakOff(engineMailbox, sender, false);

    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_TRUE, lsrVerify(engine)); // one icon is visible and expected
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    sendAirbag(engineMailbox, sender, true);

    EXPECT_EQ(LSR_TRUE, lsrRender(engine)); // no rendering, since this engine is just the fallback for sth. else
    EXPECT_EQ(LSR_FALSE, lsrVerify(engine)); // one icon is visible, 2 are expected
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    // Airbag icon will get visible after 10 failures
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(LSR_FALSE, lsrRender(engine)); // no updates
        EXPECT_EQ(LSR_FALSE, lsrVerify(engine)); // one icon is drawn - 2 are expected
        EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    }

    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_TRUE, lsrVerify(engine)); // both icons are drawn

    EXPECT_EQ(LSR_NO_ERROR, lsrDelete(engine));
    std::string output = testing::internal::GetCapturedStdout();
}
*/
TEST_F(EngineTest, verificationErrorCount)
{
    testing::internal::CaptureStdout();
    lsr::Database db(m_ddhbin, m_imgbin);
    lsr::DataHandler dataHandler(db);
    lsr::DisplayManager dsp;
    lsr::FrameHandler frameHandler(db, dataHandler, dsp);
    EXPECT_TRUE(frameHandler.start());
    lsr::Number value1;
    lsr::Number value2;
    dataHandler.getNumber(255, 1, value1);
    dataHandler.getNumber(255, 2, value2);
    EXPECT_EQ(0U, value1.getU32());
    EXPECT_EQ(0U, value2.getU32());
    // both images are expected to fail, because there was no rendering before
    frameHandler.update(0);
    EXPECT_FALSE(frameHandler.verify());
    // error count is incremented for both bitmaps
    dataHandler.getNumber(255, 1, value1);
    dataHandler.getNumber(255, 2, value2);
    EXPECT_EQ(1U, value1.getU32());
    EXPECT_EQ(1U, value2.getU32());
    std::string output = testing::internal::GetCapturedStdout();
}

