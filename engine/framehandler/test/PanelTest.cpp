/******************************************************************************
**
**   File:        PanelTest.cpp
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

#include "WidgetTestBase.h"

#include <Panel.h>

#include <LSRErrorCollector.h>
#include <Telltales.hpp>

#include <gtest/gtest.h>
using namespace lsr;

class PanelTest: public WidgetTestBase
{
protected:
    PanelTest()
        : m_db(Telltales::getDDH())
    {}

    lsr::Panel* createPanel(const PanelType* ddh)
    {
        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Panel* panel = lsr::Panel::create(m_widgetPool,
                                               m_db,
                                               ddh,
                                               &m_context,
                                               error);

        EXPECT_EQ(LSR_NO_ERROR, error.get());

        return panel;
    }

    lsr::Panel* createWrongPanel(const PanelType* ddh)
    {
        lsr::LSRErrorCollector error(LSR_NO_ERROR);
        lsr::Panel* panel = lsr::Panel::create(m_widgetPool,
                                               m_db,
                                               ddh,
                                               &m_context,
                                               error);

        EXPECT_EQ(LSR_DB_INCONSISTENT, error.get());

        return panel;
    }

    Database m_db;
};

TEST_F(PanelTest, CreatePanelTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };
    lsr::Panel* panel = createPanel(&panelType);
    EXPECT_TRUE(NULL != panel);
}

TEST_F(PanelTest, CreatePanelWithoutAreaTest)
{
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { NULL, &visible, NULL, 0 };
    lsr::Panel* panel = createWrongPanel(&panelType);
    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithoutVisibilityTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    PanelType panelType = { &area, NULL, NULL, 0 };
    lsr::Panel* panel = createWrongPanel(&panelType);
    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithoutFieldsTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };
    lsr::Panel* panel = createPanel(&panelType);
    EXPECT_TRUE(NULL != panel);
}

TEST_F(PanelTest, CreatePanelWithFieldWithWrongTypeTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType bitmap1 = {ExpressionTermType::BITMAPID_CHOICE, 1U, NULL};
    StaticBitmapFieldType p1_bitmapField1 = { &area, &visible, &bitmap1 };
    BaseFieldChoiceType p1_field1 = { BaseFieldChoiceType::NONE, &p1_bitmapField1 };
    const BaseFieldChoiceType* p1_fields[] = {&p1_field1, &p1_field1};
    PanelType panelType = { &area, &visible, p1_fields, 2 };

    lsr::Panel* panel = createWrongPanel(&panelType);
    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithWrongFieldTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType bitmap1 = {ExpressionTermType::BITMAPID_CHOICE, 1U, NULL};
    StaticBitmapFieldType p1_bitmapField1 = { &area, NULL, &bitmap1 }; // broken field
    BaseFieldChoiceType p1_field1 = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &p1_bitmapField1 };
    const BaseFieldChoiceType* p1_fields[] = {&p1_field1, &p1_field1};
    PanelType panelType = { &area, &visible, p1_fields, 2 };

    lsr::Panel* panel = createWrongPanel(&panelType);
    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, CreatePanelWithTooManyFieldsTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = {ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL};
    ExpressionTermType bitmap1 = {ExpressionTermType::BITMAPID_CHOICE, 1U, NULL};
    StaticBitmapFieldType p1_bitmapField1 = { &area, &visible, &bitmap1 };
    BaseFieldChoiceType p1_field1 = { BaseFieldChoiceType::STATICBITMAPFIELD_CHOICE, &p1_bitmapField1 };
    const BaseFieldChoiceType* p1_fields[] = {
        &p1_field1, &p1_field1, &p1_field1, &p1_field1, &p1_field1,
        &p1_field1, &p1_field1, &p1_field1, &p1_field1, &p1_field1,
        &p1_field1, &p1_field1, &p1_field1, &p1_field1, &p1_field1,
        &p1_field1, &p1_field1, &p1_field1, &p1_field1, &p1_field1,
        &p1_field1, 
    };
    PanelType panelType = { &area, &visible, p1_fields, 21 };
    /**
     * To make this test successful, statement should be true
     * MAX_BITMAPS_COUNT > MAX_WIDGET_CHILDREN_COUNT
     */
    lsr::LSRErrorCollector error(LSR_NO_ERROR);
    lsr::Panel* panel = lsr::Panel::create(m_widgetPool,
                                           m_db,
                                           &panelType,
                                           &m_context,
                                           error);

    EXPECT_EQ(LSR_POOL_IS_FULL, error.get());

    EXPECT_TRUE(NULL == panel);
}

TEST_F(PanelTest, VerifyTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType panelType = { &area, &visible, NULL, 0 };

    lsr::Panel* panel = createPanel(&panelType);
    EXPECT_TRUE(NULL != panel);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    EXPECT_TRUE(panel->verify(canvas, Area()));
}
