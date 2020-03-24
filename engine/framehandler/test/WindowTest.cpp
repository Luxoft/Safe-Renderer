/******************************************************************************
**
**   File:        WindowTest.cpp
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
#include "MockWidget.h"

#include <Window.h>
#include <WindowDefinition.h>

#include <LSRErrorCollector.h>
#include <Telltales.hpp>
#include <TelltalesHMI.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using testing::_;
using testing::Return;

using namespace lsr;

class WindowTest: public WidgetTestBase
{
protected:
    WindowTest()
        : m_db(Telltales::getDDH())
        , m_windef(Telltales::getDDH(), 0U)
    {}

    lsr::Database m_db;
    lsr::WindowDefinition m_windef;
    Telltales::HMI m_hmi;
};

class CustomHMI : public IHMI
{
public:
    explicit CustomHMI()
        : m_frame()
    {
    }

    virtual Frame* getFrame() P_OVERRIDE
    {
        return &m_frame;
    }

private:
    lsr::Frame m_frame;
};

TEST_F(WindowTest, CreateWindowTest)
{
    lsr::Window window(m_dsp, m_windef);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, window.setup(m_hmi, m_db));
}

TEST_F(WindowTest, CreateWindowWithWrongPanelsTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const PanelType p1 = {&area, NULL, NULL, 0U}; // broken panel (without visibility set)
    CustomHMI badHMI;
    lsr::Panel panel(&p1);
    badHMI.getFrame()->addChild(panel);
    lsr::LSRErrorCollector error(LSR_NO_ENGINE_ERROR);
    lsr::Window window(m_dsp, m_windef);
    EXPECT_EQ(LSR_DB_INCONSISTENT, window.setup(badHMI, m_db));
}

TEST_F(WindowTest, VerifyTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const PanelType p1 = {&area, &visible, NULL, 0U};
    lsr::Window window(m_dsp, m_windef);
    CustomHMI hmi;
    lsr::Panel panel(&p1);
    lsr::MockField field;
    hmi.getFrame()->addChild(panel);
    panel.addChild(field);

    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_NO_ENGINE_ERROR));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, window.setup(hmi, m_db));

    EXPECT_CALL(field, onVerify(_, _)).WillOnce(Return(true));
    EXPECT_TRUE(window.verify());

    EXPECT_CALL(field, onVerify(_, _)).WillOnce(Return(false));
    EXPECT_FALSE(window.verify());
}

TEST_F(WindowTest, DrawTest)
{
    MockField field;
    m_hmi.getContentPanel().addChild(field);
    lsr::Window window(m_dsp, m_windef);

    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_NO_ENGINE_ERROR));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, window.setup(m_hmi, m_db));

    const lsr::Area area;
    EXPECT_CALL(field, onDraw(_, _)).Times(1);
    window.draw(m_canvas, area);
}

TEST_F(WindowTest, RenderTest)
{
    MockField field;
    m_hmi.getContentPanel().addChild(field);
    lsr::Window window(m_dsp, m_windef);

    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_NO_ENGINE_ERROR));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, window.setup(m_hmi, m_db));

    lsr::Area area;
    EXPECT_CALL(field, onDraw(_, _)).Times(1);
    EXPECT_TRUE(window.render());
}

TEST_F(WindowTest, RenderWithNotInvalidatedStateTest)
{
    MockField field;
    m_hmi.getContentPanel().addChild(field);
    lsr::Window window(m_dsp, m_windef);

    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_NO_ENGINE_ERROR));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, window.setup(m_hmi, m_db));

    lsr::Area area;
    EXPECT_CALL(field, onDraw(_, _)).Times(1);
    EXPECT_TRUE(window.render());

    // now we are in validated state
    EXPECT_FALSE(window.render());

    // invalidate
    field.setVisible(false);
    field.setVisible(true);
    EXPECT_CALL(field, onDraw(_, _)).Times(1);
    EXPECT_TRUE(window.render());
}

// test to fulfill coverage
TEST_F(WindowTest, HandleWindowEventsTest)
{
    lsr::Window window(m_dsp, m_windef);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, window.setup(m_hmi, m_db));

    window.handleWindowEvents();
}
