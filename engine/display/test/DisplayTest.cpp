/******************************************************************************
**
**   File:        DisplayTest.cpp
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

#include <gtest/gtest.h>
#include "DisplayManager.h"
#include "WindowCanvas.h"
#include "Area.h"
#include "Color.h"
#include "StaticBitmap.h"
#include "Database.h"
#include "WindowDefinition.h"
#include <fstream>
#include <string>
#include <Telltales.hpp>
#include "TelltalesDisplayTest.h"
#include "MockGIL.h"

using namespace lsr;
using testing::_;
using testing::Return;

class DisplayManagerTest : public ::testing::Test
{
    void SetUp() P_OVERRIDE
    {
        m_db = new Database(Telltales::getDDH());
        gilMock = &gil;
    }

    void TearDown() P_OVERRIDE
    {
        delete m_db;
        m_db = NULL;
        gilMock = NULL;
    }

protected:
    ::testing::NiceMock<MockGIL> gil;
    Database* m_db;
};

TEST_F(DisplayManagerTest, empty)
{
    // gilInit() is not called by the DisplayManager,
    // because it shall only be called once and there may be several DisplayManager instances
    gilInit(NULL);

    // create the DisplayManager
    EXPECT_CALL(gil, gilCreateContext());
    DisplayManager dsp;

    // create a window
    WindowDefinition config = WindowDefinition(m_db->getDdh(), 0U);
    config.setSize(400, 320);
    WindowCanvas canvas(dsp, config);

    // draw on the window
    canvas.makeCurrent();
    canvas.clear(Color(0xff, 0, 0, 0xff));
    canvas.drawBitmap(m_db->getBitmap(1), Area(10, 15, 42, 52));

    EXPECT_CALL(gil, gilSwapBuffers(_));
    canvas.swapBuffers();

    const I32 x = 10;
    const I32 y = 15;
    const I32 texW = 102;
    const I32 texH = 68;
    EXPECT_CALL(gil, gilVerify(dsp.getContext(), (x << 4), (y << 4),
        0, 0, 
        (42 << 4), (52 << 4), 
        ((texW - 1) << 4), ((texH - 1) << 4))).WillOnce(Return(true));
    EXPECT_TRUE(canvas.verify(m_db->getBitmap(1), Area(x, y, 42, 52)));

    EXPECT_CALL(gil, gilHandleWindowEvents(dsp.getContext())).WillOnce(Return(false));
    EXPECT_FALSE(canvas.handleWindowEvents());
}

TEST_F(DisplayManagerTest, loadAllTextures)
{
    DisplayManager dsp;
    Database db(Telltales::getDDH());
    gil_texture_t tex;
    EXPECT_CALL(gil, gilCreateTexture(dsp.getContext())).Times(5).WillRepeatedly(Return(&tex));
    EXPECT_TRUE(dsp.loadAllTextures(db));
}

TEST_F(DisplayManagerTest, loadAllTexturesNoBmp)
{
    DisplayManager dsp;
    Database db(TelltalesDisplayNoBmp::getDDH());
    EXPECT_FALSE(dsp.loadAllTextures(db));
}

TEST_F(DisplayManagerTest, loadAllTexturesNoSkin)
{
    DisplayManager dsp;
    Database db(TelltalesDisplayNoSkin::getDDH());
    EXPECT_FALSE(dsp.loadAllTextures(db));
}

TEST_F(DisplayManagerTest, loadAllTexturesNoState)
{
    DisplayManager dsp;
    Database db(TelltalesDisplayNoState::getDDH());
    EXPECT_FALSE(dsp.loadAllTextures(db));
}
