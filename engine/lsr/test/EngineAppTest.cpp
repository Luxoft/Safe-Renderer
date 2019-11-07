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
#include "DataHandler.h"
#include "FrameHandler.h"
#include "DisplayManager.h"
#include <Telltales.h>
#include <Telltales.hpp>
#include "Engine.h"

using namespace lsr;

class EngineTest : public ::testing::Test
{
public:
    static void SetUpTestCase() {
    }

    static void TearDownTestCase() {
    }

    void SetUp() P_OVERRIDE
    {
        gilInit(NULL);
    }

    void TearDown() P_OVERRIDE
    {
    }
};


TEST_F(EngineTest, emptyDatabase)
{
    LSRDatabase db = NULL;
    LSREngine engine = lsrCreate(db);
    // Even if the database is garbage, there will be an engine instance to check for errors
    EXPECT_TRUE(engine != NULL);
    EXPECT_EQ(LSR_DB_DDHBIN_EMPTY, lsrGetError(engine));
    lsrDelete(engine);
}

/**
 * test out of memory
 */
TEST_F(EngineTest, invalidEngine)
{
    LSRDatabase db = NULL;
    LSREngine engine1 = lsrCreate(db);
    LSREngine engine2 = lsrCreate(db);
    LSREngine engine3 = lsrCreate(db);
    EXPECT_TRUE(engine1 != NULL);
    EXPECT_TRUE(engine2 != NULL);
    EXPECT_TRUE(engine3 == NULL);
    EXPECT_EQ(LSR_UNKNOWN_ERROR, lsrGetError(engine3));
    lsrDelete(engine3);
    lsrDelete(engine2);
    lsrDelete(engine1);
}

TEST_F(EngineTest, SetData)
{
    LSREngine engine = lsrCreate(getTelltalesDDH());
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    int32_t errCount;
    LSRBoolean breakOn;
    LSRBoolean breakOff;
    EXPECT_EQ(LSR_DATA_STATUS_INCONSISTENT, lsrGetBoolean(engine, TELLTALES_INTERNALFU_AIRBAGERRORCOUNT, &breakOn));
    EXPECT_EQ(LSR_DATA_STATUS_INCONSISTENT, lsrGetInteger(engine, TELLTALES_FUTELLTALES_BREAKON, &breakOn));

    EXPECT_EQ(LSR_DATA_STATUS_VALID, lsrGetInteger(engine, TELLTALES_INTERNALFU_AIRBAGERRORCOUNT, &errCount));
    EXPECT_EQ(LSR_DATA_STATUS_NOT_AVAILABLE, lsrGetBoolean(engine, TELLTALES_FUTELLTALES_BREAKOFF, &breakOff));
    EXPECT_EQ(LSR_DATA_STATUS_NOT_AVAILABLE, lsrGetBoolean(engine, TELLTALES_FUTELLTALES_BREAKON, &breakOn));
    EXPECT_EQ(0, errCount);
    EXPECT_EQ(LSR_FALSE, breakOff);
    EXPECT_EQ(LSR_FALSE, breakOn);

    EXPECT_EQ(LSR_TRUE, lsrSetInteger(engine, TELLTALES_INTERNALFU_AIRBAGERRORCOUNT, 42));
    EXPECT_EQ(LSR_TRUE, lsrSetBoolean(engine, TELLTALES_FUTELLTALES_BREAKOFF, LSR_TRUE));
    EXPECT_EQ(LSR_TRUE, lsrSetBoolean(engine, TELLTALES_FUTELLTALES_BREAKON, LSR_FALSE));
    EXPECT_EQ(LSR_DATA_STATUS_VALID, lsrGetInteger(engine, TELLTALES_INTERNALFU_AIRBAGERRORCOUNT, &errCount));
    EXPECT_EQ(LSR_DATA_STATUS_VALID, lsrGetBoolean(engine, TELLTALES_FUTELLTALES_BREAKOFF, &breakOff));
    EXPECT_EQ(LSR_DATA_STATUS_VALID, lsrGetBoolean(engine, TELLTALES_FUTELLTALES_BREAKON, &breakOn));
    EXPECT_EQ(42, errCount);
    EXPECT_EQ(LSR_TRUE, breakOff);
    EXPECT_EQ(LSR_FALSE, breakOn);

    EXPECT_EQ(LSR_FALSE, lsrSetBoolean(engine, TELLTALES_INTERNALFU_AIRBAGERRORCOUNT, LSR_TRUE));
    EXPECT_EQ(LSR_FALSE, lsrSetInteger(engine, TELLTALES_FUTELLTALES_BREAKOFF, 0));
    EXPECT_EQ(42, errCount);
    EXPECT_EQ(LSR_TRUE, breakOff);
    EXPECT_EQ(LSR_FALSE, breakOn);

    EXPECT_EQ(LSR_DATA_STATUS_VALID, lsrGetInteger(engine, TELLTALES_INTERNALFU_AIRBAGERRORCOUNT, NULL));
    EXPECT_EQ(LSR_DATA_STATUS_VALID, lsrGetBoolean(engine, TELLTALES_FUTELLTALES_BREAKOFF, NULL));

    lsrDelete(engine);
}

TEST_F(EngineTest, normalRun)
{
    LSREngine engine = lsrCreate(getTelltalesDDH());
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    EXPECT_EQ(LSR_FALSE, lsrVerify(engine));
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));

    EXPECT_EQ(LSR_TRUE, lsrSetBoolean(engine, TELLTALES_FUTELLTALES_AIRBAG, LSR_FALSE));
    EXPECT_EQ(LSR_TRUE, lsrSetBoolean(engine, TELLTALES_FUTELLTALES_BREAKOFF, LSR_TRUE));
    EXPECT_EQ(LSR_TRUE, lsrSetBoolean(engine, TELLTALES_FUTELLTALES_BREAKON, LSR_FALSE));

    EXPECT_EQ(LSR_TRUE, lsrRender(engine));
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    EXPECT_EQ(LSR_TRUE, lsrVerify(engine));
    EXPECT_EQ(LSR_NO_ERROR, lsrGetError(engine));
    lsrDelete(engine);
}

TEST_F(EngineTest, normalRun_CppInterface)
{
    lsr::Engine engine(Telltales::getDDH());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());

    EXPECT_TRUE(engine.render());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());
    EXPECT_FALSE(engine.verify());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());
    EXPECT_FALSE(engine.handleWindowEvents());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());

    EXPECT_TRUE(engine.setData(lsr::DynamicData(Telltales::FUTELLTALES_AIRBAG), lsr::Number(false), lsr::DataStatus::VALID));
    EXPECT_TRUE(engine.setData(lsr::DynamicData(Telltales::FUTELLTALES_BREAKOFF), lsr::Number(true), lsr::DataStatus::VALID));
    EXPECT_TRUE(engine.setData(lsr::DynamicData(Telltales::FUTELLTALES_BREAKON), lsr::Number(false), lsr::DataStatus::VALID));

    EXPECT_TRUE(engine.render());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());
    EXPECT_TRUE(engine.verify());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());
    EXPECT_FALSE(engine.handleWindowEvents());
    EXPECT_EQ(LSR_NO_ERROR, engine.getError());
}

TEST_F(EngineTest, verificationErrorCount)
{
    testing::internal::CaptureStdout();
    lsr::Database db(Telltales::getDDH());
    lsr::DataHandler dataHandler(db);
    lsr::DisplayManager dsp;
    lsr::FrameHandler frameHandler(db, dataHandler, dsp);
    EXPECT_TRUE(frameHandler.start());
    lsr::Number value1;
    lsr::Number value2;
    dataHandler.getNumber(DynamicData(255, 1), value1);
    dataHandler.getNumber(DynamicData(255, 2), value2);
    EXPECT_EQ(0U, value1.getU32());
    EXPECT_EQ(0U, value2.getU32());
    // both images are expected to fail, because there was no rendering before
    frameHandler.update(0);
    EXPECT_FALSE(frameHandler.verify());
    // error count is incremented for both bitmaps
    dataHandler.getNumber(DynamicData(255, 1), value1);
    dataHandler.getNumber(DynamicData(255, 2), value2);
    EXPECT_EQ(1U, value1.getU32());
    EXPECT_EQ(1U, value2.getU32());
    std::string output = testing::internal::GetCapturedStdout();
}

