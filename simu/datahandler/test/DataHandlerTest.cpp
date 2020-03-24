/******************************************************************************
**
**   File:        DataHandlerTest.cpp
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

#include <DataHandler.h>
#include "Database.h"
#include "ResourceBuffer.h"
#include "Telltales.hpp"

#include <gtest/gtest.h>
#include <fstream>

using namespace lsr;

namespace
{
    const U32 dbSize = 5U;
    DataHandler::DataEntryType db[dbSize] = {
        { 0x002a0001U, DATATYPE_BOOLEAN, 0U },
        { 0x002a0002U, DATATYPE_BOOLEAN, 0U },
        { 0x002a0003U, DATATYPE_BOOLEAN, 0U },
        { 0x00ff0001U, DATATYPE_INTEGER, 0U },
        { 0x00ff0002U, DATATYPE_INTEGER, 0U },
    };
};

class DataHandlerTest : public ::testing::Test
{
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    DataHandlerTest()
    {
    }

    void SetUp() P_OVERRIDE
    {
    }
};

TEST_F(DataHandlerTest, GetNumber)
{
    DataHandler dataHandler(db, dbSize);
    dataHandler.setData(DynamicData(255, 1), Number(0U, DATATYPE_INTEGER), DataStatus::VALID);
    dataHandler.setData(DynamicData(255, 2), Number(0U, DATATYPE_INTEGER), DataStatus::VALID);

    Number value;
    // Internal FU data is valid and has default value
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(DynamicData(255, 1), value));
    EXPECT_EQ(Number(0, DATATYPE_INTEGER), value);
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(DynamicData(255, 2), value));
    EXPECT_EQ(Number(0, DATATYPE_INTEGER), value);
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(DynamicData(255, 3), value)); // not part of FU
    // External FU data is not received by default
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(DynamicData(42, 1), value));
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(DynamicData(42, 2), value));
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(DynamicData(42, 3), value));
    EXPECT_EQ(DataStatus::NOT_AVAILABLE, dataHandler.getNumber(DynamicData(42, 4), value));

    EXPECT_TRUE(dataHandler.setData(DynamicData(42, 1), Number(1, DATATYPE_BOOLEAN), DataStatus::VALID));
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(DynamicData(42, 1), value));
    EXPECT_EQ(Number(1, DATATYPE_BOOLEAN), value);
}

TEST_F(DataHandlerTest, setData)
{
    DataHandler dataHandler(db, dbSize);
    Number value;
    EXPECT_TRUE(dataHandler.setData(DynamicData(255, 1), Number(42, DATATYPE_INTEGER), DataStatus::VALID));
    EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(DynamicData(255, 1), value));
    EXPECT_EQ(Number(42, DATATYPE_INTEGER), value);

    EXPECT_TRUE(dataHandler.setData(DynamicData(255, 1), Number(44, DATATYPE_INTEGER), DataStatus::INVALID));
    EXPECT_EQ(DataStatus::INVALID, dataHandler.getNumber(DynamicData(255, 1), value));
    EXPECT_EQ(Number(44, DATATYPE_INTEGER), value);

    EXPECT_FALSE(dataHandler.setData(DynamicData(255, 1), Number(true), DataStatus::VALID));
    EXPECT_FALSE(dataHandler.setData(DynamicData(255, 1), Number(44, DATATYPE_BITMAP_ID), DataStatus::INVALID));
    EXPECT_FALSE(dataHandler.setData(DynamicData(255, 12), Number(true), DataStatus::VALID));
}

TEST_F(DataHandlerTest, onMessage)
{
    DataHandler dataHandler(db, dbSize);
    {
        Number value;
        EXPECT_TRUE(dataHandler.setData(DynamicData(42, 2), Number(1, DATATYPE_BOOLEAN), DataStatus::VALID));
        EXPECT_EQ(DataStatus::VALID, dataHandler.getNumber(DynamicData(42, 2), value));
        EXPECT_EQ(Number(1, DATATYPE_BOOLEAN), value);
    }
    {
        Number value;
        EXPECT_TRUE(dataHandler.setData(DynamicData(42, 2), Number(1, DATATYPE_BOOLEAN), DataStatus::INVALID));
        EXPECT_EQ(DataStatus::INVALID, dataHandler.getNumber(DynamicData(42, 2), value));
        EXPECT_EQ(Number(1, DATATYPE_BOOLEAN), value);
    }
    {
        // wrong type
        Number value;
        EXPECT_FALSE(dataHandler.setData(DynamicData(42, 2), Number(1, DATATYPE_INTEGER), DataStatus::VALID));
    }
    {
        // unknown FU id
        Number value;
        EXPECT_FALSE(dataHandler.setData(DynamicData(53, 2), Number(1, DATATYPE_BOOLEAN), DataStatus::VALID));
    }
}

TEST_F(DataHandlerTest, TestFind)
{
    // TODO: Check find() functionality
}
