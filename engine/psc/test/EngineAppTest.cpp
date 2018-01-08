/******************************************************************************
**
**   File:        EngineAppTest.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
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
#include "psc.h"
#include "pgl.h"
#include "OutputStream.h"
#include "OdiTypes.h"
#include "OdiMsgHeader.h"
#include "MessageHeader.h"
#include "DataResponseMessage.h"

using namespace psc;

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
        pgwInit();
        pglInit();
    }

    void TearDown() P_OVERRIDE
    {
        pgwClose();
    }

    void sendValue(PGWMailbox engineMailbox, PGWMailbox sender, FUClassId fu, DataId dataId, U32 value, DynamicDataTypeEnumeration type)
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
        pgwMailboxWrite(engineMailbox, sender, static_cast<const U8*>(stream.getBuffer()), stream.bytesWritten());
    }

    void sendBreakOn(PGWMailbox engineMailbox, PGWMailbox sender, bool value)
    {
        sendValue(engineMailbox, sender, 42, 1, value ? 1 : 0, DATATYPE_BOOLEAN);
    }

    void sendBreakOff(PGWMailbox engineMailbox, PGWMailbox sender, bool value)
    {
        sendValue(engineMailbox, sender, 42, 2, value ? 1 : 0, DATATYPE_BOOLEAN);
    }

    void sendAirbag(PGWMailbox engineMailbox, PGWMailbox sender, bool value)
    {
        sendValue(engineMailbox, sender, 42, 3, value ? 1 : 0, DATATYPE_BOOLEAN);
    }

    std::string m_ddhbinData;
    std::string m_imgbinData;

protected:
    static ResourceBuffer m_ddhbin;
    static ResourceBuffer m_imgbin;
};

ResourceBuffer EngineTest::m_ddhbin;
ResourceBuffer EngineTest::m_imgbin;

TEST(psc, emptyDatabase)
{
    PSCDatabase db = { 0, 0, 0, 0 };
    PGWMailbox mailbox = 1;
    PSCEngine engine = pscCreate(&db, mailbox);
    // Even if the database is garbage, there will be an engine instance to check for errors
    EXPECT_TRUE(engine != NULL);
    EXPECT_EQ(PSC_DB_DDHBIN_VERSION_MISMATCH, pscGetError(engine));
    EXPECT_EQ(PSC_NO_ERROR, pscDelete(engine));
}

TEST_F(EngineTest, noFUConnection)
{
    PSCDatabase db = { m_ddhbin.getData()
        , m_ddhbin.getSize()
        , m_imgbin.getData()
        , m_imgbin.getSize()
    };
    PGWMailbox mailbox = 1;
    testing::internal::CaptureStdout();
    EXPECT_EQ(PGW_NO_ERROR, pgwMailboxInit(mailbox));
    PSCEngine engine = pscCreate(&db, mailbox);
    ASSERT_TRUE(engine != NULL);
    ASSERT_EQ(PSC_NO_ERROR, pscGetError(engine));

    // in a real project this will be a loop
    EXPECT_EQ(PSC_TRUE, pscRender(engine));
    EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));
    EXPECT_EQ(PSC_FALSE, pscVerify(engine)); // one icon is drawn - 2 are expected
    EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));
    // loop end

    // Airbag icon will get visible after 10 failures
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(PSC_FALSE, pscRender(engine)); // no updates
        EXPECT_EQ(PSC_FALSE, pscVerify(engine)); // one icon is drawn - 2 are expected
        EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));
    }
    EXPECT_EQ(PSC_TRUE, pscRender(engine));
    EXPECT_EQ(PSC_TRUE, pscVerify(engine)); // both icons are drawn

    EXPECT_EQ(PSC_NO_ERROR, pscDelete(engine));

    std::string output = testing::internal::GetCapturedStdout();
    //std::cout << "###### Render dump begin ######" << std::endl;
    //std::cout << output;
    //std::cout << "####### Render dump end #######" << std::endl;
    // TODO : verify captured stdout
}

TEST_F(EngineTest, fuConnection)
{
    PSCDatabase db = { m_ddhbin.getData()
        , m_ddhbin.getSize()
        , m_imgbin.getData()
        , m_imgbin.getSize()
    };
    PGWMailbox engineMailbox = 1;
    PGWMailbox sender = 2;
    testing::internal::CaptureStdout();
    EXPECT_EQ(PGW_NO_ERROR, pgwMailboxInit(engineMailbox));
    PSCEngine engine = pscCreate(&db, engineMailbox);
    ASSERT_TRUE(engine != NULL);
    ASSERT_EQ(PSC_NO_ERROR, pscGetError(engine));

    sendBreakOn(engineMailbox, sender, false);
    sendBreakOff(engineMailbox, sender, true);
    sendAirbag(engineMailbox, sender, false);

    EXPECT_EQ(PSC_TRUE, pscRender(engine));
    EXPECT_EQ(PSC_TRUE, pscVerify(engine)); // no icon is visible
    EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));

    sendBreakOn(engineMailbox, sender, true);
    sendBreakOff(engineMailbox, sender, false);

    EXPECT_EQ(PSC_TRUE, pscRender(engine));
    EXPECT_EQ(PSC_TRUE, pscVerify(engine)); // one icon is visible and expected
    EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));

    sendAirbag(engineMailbox, sender, true);

    EXPECT_EQ(PSC_TRUE, pscRender(engine)); // no rendering, since this engine is just the fallback for sth. else
    EXPECT_EQ(PSC_FALSE, pscVerify(engine)); // one icon is visible, 2 are expected
    EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));

    // Airbag icon will get visible after 10 failures
    for (int i = 0; i < 10; ++i)
    {
        EXPECT_EQ(PSC_FALSE, pscRender(engine)); // no updates
        EXPECT_EQ(PSC_FALSE, pscVerify(engine)); // one icon is drawn - 2 are expected
        EXPECT_EQ(PSC_NO_ERROR, pscGetError(engine));
    }

    EXPECT_EQ(PSC_TRUE, pscRender(engine));
    EXPECT_EQ(PSC_TRUE, pscVerify(engine)); // both icons are drawn

    EXPECT_EQ(PSC_NO_ERROR, pscDelete(engine));
}
