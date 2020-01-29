/******************************************************************************
**
**   File:        DataHandlerTest.cpp
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

#include <DataHandler.h>
#include "Database.h"
#include "ResourceBuffer.h"
#include "Telltales.hpp"

#include <gtest/gtest.h>
#include <fstream>

using namespace lsr;

class DataHandlerTest : public ::testing::Test
{
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    DataHandlerTest()
        : m_db(Telltales::getDDH())
    {
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, m_db.getError());
    }

    void SetUp() P_OVERRIDE
    {
    }


protected:
    Database m_db;
};

TEST_F(DataHandlerTest, GetNumber)
{
    DataHandler dataHandler(m_db);

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
    DataHandler dataHandler(m_db);
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
    DataHandler dataHandler(m_db);
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
