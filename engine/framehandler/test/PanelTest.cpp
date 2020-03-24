/******************************************************************************
**
**   File:        PanelTest.cpp
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

#include <Panel.h>

#include <LSRErrorCollector.h>
#include <Telltales.hpp>
#include "MockWidget.h"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace lsr;
using testing::_;
using testing::Return;

class PanelTest: public WidgetTestBase
{
protected:
    PanelTest()
        : m_db(Telltales::getDDH())
    {}

    Database m_db;
};

TEST_F(PanelTest, CreatePanelTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };
    lsr::Panel panel(&panelType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, panel.setup(m_db));
}

TEST_F(PanelTest, CreatePanelWithoutAreaTest)
{
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { NULL, &visible, NULL, 0 };
    lsr::Panel panel(&panelType);
    EXPECT_EQ(LSR_DB_INCONSISTENT, panel.setup(m_db));
}

TEST_F(PanelTest, CreatePanelWithoutVisibilityTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    PanelType panelType = { &area, NULL, NULL, 0 };
    lsr::Panel panel(&panelType);
    EXPECT_EQ(LSR_DB_INCONSISTENT, panel.setup(m_db));
}

TEST_F(PanelTest, CreatePanelWithoutFieldsTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };
    lsr::Panel panel(&panelType);
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, panel.setup(m_db));
}

TEST_F(PanelTest, AddToManyFields)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };
    lsr::Panel panel(&panelType);
    lsr::MockField field;
    for (U32 i = 0U; i < MAX_WIDGET_CHILDREN_COUNT; ++i)
    {
        panel.addChild(field);
        EXPECT_EQ(LSR_NO_ENGINE_ERROR, panel.getError());
    }
    panel.addChild(field);
    EXPECT_EQ(LSR_DB_INCONSISTENT, panel.getError());
}

TEST_F(PanelTest, CreatePanelWithFieldWithWrongTypeTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    const PanelType panelType = { &area, &visible, NULL, 0U };

    lsr::Panel panel(&panelType);
    lsr::MockField field;
    panel.addChild(field);
    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_DB_INCONSISTENT));
    EXPECT_EQ(LSR_DB_INCONSISTENT, panel.setup(m_db));
}

TEST_F(PanelTest, VerifyTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };

    lsr::Panel panel(&panelType);
    lsr::MockField field;
    panel.addChild(field);
    EXPECT_CALL(field, setup(_)).WillOnce(Return(LSR_NO_ENGINE_ERROR));
    EXPECT_EQ(LSR_NO_ENGINE_ERROR, panel.setup(m_db));

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    EXPECT_CALL(field, onVerify(_,_)).WillOnce(Return(true));
    EXPECT_TRUE(panel.verify(canvas, Area()));

    EXPECT_CALL(field, onVerify(_,_)).WillOnce(Return(false));
    EXPECT_FALSE(panel.verify(canvas, Area()));
}
