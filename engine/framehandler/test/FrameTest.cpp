/******************************************************************************
**
**   File:        FrameTest.cpp
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

#include "WidgetTestBase.h"

#include <Frame.h>

#include <LSRErrorCollector.h>
#include <PanelDatabaseType.h>
#include <HMIGlobalSettingsType.h>
#include <DisplaySizeType.h>
#include <DDHType.h>
#include <Telltales.hpp>
#include "MockWidget.h"

#include <gtest/gtest.h>

using namespace lsr;
using testing::_;
using testing::Return;

class FrameTest: public WidgetTestBase
{
protected:
    FrameTest()
        : m_db(Telltales::getDDH())
    {}

    lsr::Database m_db;
};

TEST_F(FrameTest, CreateFrameTest)
{
    lsr::Frame frame;
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, frame.setup(m_db));
}

TEST_F(FrameTest, CreateFrameWithWrongPanelTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    PanelType p1 = {&area, NULL, NULL, 0U}; // broken panel (without visibility set)
    Database db(Telltales::getDDH());
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::Frame frame;
    lsr::Panel panel(&p1);
    frame.addChild(panel);
    EXPECT_EQ(LSR_DB_INCONSISTENT, frame.setup(m_db));
}

TEST_F(FrameTest, AddToManyPanels)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType p1 = {&area, &visible, NULL, 0U}; // broken panel (without visibility set)
    lsr::Frame frame;
    lsr::Panel panel(&p1);
    for (U32 i = 0U; i < MAX_PANELS_COUNT; ++i)
    {
        frame.addChild(panel);
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, frame.getError());
    }
    frame.addChild(panel);
    EXPECT_EQ(LSR_DB_INCONSISTENT, frame.getError());
}

TEST_F(FrameTest, VerifyTest)
{
    lsr::Area area;
    lsr::Frame frame;
    frame.setup(m_db);
    EXPECT_TRUE(frame.verify(m_canvas, area));
}

TEST_F(FrameTest, DrawTest)
{
    const AreaType areaType = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const PanelType panelType = {&areaType, &visible, NULL, 0U};
    const lsr::Area area;
    lsr::Frame frame;
    Panel panel(&panelType);
    MockField field;
    frame.addChild(panel);
    panel.addChild(field);

    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_NO_ENGINE_ERROR));
    EXPECT_CALL(field, onDraw(_,_));

    EXPECT_EQ(LSR_NO_ENGINE_ERROR, frame.setup(m_db));
    frame.draw(m_canvas, area);
}
