/******************************************************************************
**
**   File:        DataHandlerTest.cpp
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

#include <DataHandler.h>
#include "Database.h"
#include "ResourceBuffer.h"
#include "OdiTypes.h"
#include "OutputStream.h"
#include "IMsgTransmitter.h"
#include "DataResponseMessage.h"

#include <gtest/gtest.h>
#include <fstream>

using namespace psc;

const char* ddhbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.ddhbin";
const char* imgbin = ROOT_PATH "/test/database/Telltales/Output/Telltales.imgbin";

class DataHandlerTest : public ::testing::Test
{
public:
    static void SetUpTestCase() {
        static std::string m_ddhbinData;
        static std::string m_imgbinData;
        std::ifstream ifs1(ddhbin, std::ios::binary);
        m_ddhbinData.assign ((std::istreambuf_iterator<char>(ifs1)), (std::istreambuf_iterator<char>()));
        m_ddhbin = ResourceBuffer(m_ddhbinData.c_str(), m_ddhbinData.size());
        std::ifstream ifs2(imgbin, std::ios::binary);
        m_imgbinData.assign ((std::istreambuf_iterator<char>(ifs2)), (std::istreambuf_iterator<char>()));
        m_imgbin = ResourceBuffer(m_imgbinData.c_str(), m_imgbinData.size());
    }

    static void TearDownTestCase() {
    }

    DataHandlerTest()
        : m_db(m_ddhbin, m_imgbin)
    {
        EXPECT_EQ(PSC_NO_ERROR, m_db.getError());
    }

    void SetUp() P_OVERRIDE
    {
    }


protected:
    static ResourceBuffer m_ddhbin;
    static ResourceBuffer m_imgbin;
    Database m_db;
};

ResourceBuffer DataHandlerTest::m_ddhbin;
ResourceBuffer DataHandlerTest::m_imgbin;

// TODO: Mock?
class Transmitter : public IMsgTransmitter
{
    PSCError transmitMessage(const U8* data, U32 dataLen) P_OVERRIDE {
        return PSC_NO_ERROR;
    }
};

TEST_F(DataHandlerTest, GetNumber)
{
    DataHandler dataHandler(m_db);

    Number value;
    // Internal FU data is valid and has default value
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(255, 1, value));
    EXPECT_EQ(Number(0, DATATYPE_INTEGER), value);
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(255, 2, value));
    EXPECT_EQ(Number(0, DATATYPE_INTEGER), value);
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(255, 3, value)); // not part of FU
    // External FU data is not received by default
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(42, 1, value));
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(42, 2, value));
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(42, 3, value));
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(42, 4, value));

    U8 buf[] = {
        DataMessageTypes::DYN_DATA_RESP,
        0, 42, // fu
        0, 1, //dataId
        DATATYPE_BOOLEAN,
        0, // invalid
        0, 0, 0, 1 //value
    };

    InputStream stream(buf, sizeof(buf));
    Transmitter transmitter;

    EXPECT_EQ(PSC_NO_ERROR, dataHandler.onMessage(&transmitter, MessageTypes::ODI, stream));
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(42, 1, value));
    EXPECT_EQ(Number(1, DATATYPE_BOOLEAN), value);
}

TEST_F(DataHandlerTest, setData)
{
    DataHandler dataHandler(m_db);
    Number value;
    EXPECT_TRUE(dataHandler.setData(255, 1, Number(42, DATATYPE_INTEGER), DataStatus::VALID));
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(255, 1, value));
    EXPECT_EQ(Number(42, DATATYPE_INTEGER), value);

    EXPECT_TRUE(dataHandler.setData(255, 1, Number(44, DATATYPE_INTEGER), DataStatus::INVALID));
    EXPECT_EQ(DataStatus::INVALID, dataHandler.getNumber(255, 1, value));
    EXPECT_EQ(Number(44, DATATYPE_INTEGER), value);

    EXPECT_FALSE(dataHandler.setData(255, 1, Number(true), DataStatus::VALID));
    EXPECT_FALSE(dataHandler.setData(255, 1, Number(44, DATATYPE_BITMAP_ID), DataStatus::INVALID));
    EXPECT_FALSE(dataHandler.setData(255, 12, Number(true), DataStatus::VALID));
}

TEST_F(DataHandlerTest, onMessage)
{
    Transmitter transmitter;
    DataHandler dataHandler(m_db);
    U8 buf[11] = { DataMessageTypes::DYN_DATA_RESP };
    DataResponseMessage msg;
    msg.setDataId(2);
    msg.setFuId(42);
    msg.setDataType(DATATYPE_BOOLEAN);
    msg.setInvalidFlag(false);
    msg.setDataValue(1);
    {
        OutputStream out(buf + 1, sizeof(buf)-1);
        out << msg;
        InputStream stream(buf, sizeof(buf));
        Number value;
        EXPECT_EQ(PSC_NO_ERROR, dataHandler.onMessage(&transmitter, MessageTypes::ODI, stream));
        EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(42, 2, value));
        EXPECT_EQ(Number(1, DATATYPE_BOOLEAN), value);
    }
    {
        msg.setInvalidFlag(true);
        OutputStream out(buf + 1, sizeof(buf)-1);
        out << msg;
        InputStream stream(buf, sizeof(buf));
        Number value;
        EXPECT_EQ(PSC_NO_ERROR, dataHandler.onMessage(&transmitter, MessageTypes::ODI, stream));
        EXPECT_EQ(DataStatus::INVALID, dataHandler.getNumber(42, 2, value));
        EXPECT_EQ(Number(1, DATATYPE_BOOLEAN), value);
    }
    {
        msg.setInvalidFlag(false);
        msg.setDataType(DATATYPE_INTEGER); // wrong type
        OutputStream out(buf + 1, sizeof(buf)-1);
        out << msg;
        InputStream stream(buf, sizeof(buf));
        Number value;
        EXPECT_EQ(PSC_DH_INVALID_MESSAGE_TYPE, dataHandler.onMessage(&transmitter, MessageTypes::ODI, stream));
    }
    {
        msg.setFuId(53);
        msg.setInvalidFlag(false);
        msg.setDataType(DATATYPE_BOOLEAN); // wrong type
        OutputStream out(buf + 1, sizeof(buf)-1);
        out << msg;
        InputStream stream(buf, sizeof(buf));
        Number value;
        EXPECT_EQ(PSC_DH_INVALID_MESSAGE_TYPE, dataHandler.onMessage(&transmitter, MessageTypes::ODI, stream));
    }
}

TEST_F(DataHandlerTest, TestFind)
{
    // TODO: Check find() functionality
}
