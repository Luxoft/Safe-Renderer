/******************************************************************************
**
**   File:        WidgetTest.cpp
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

#include "MockWidget.h"
#include "TestCanvas.h"

#include <ResourceBuffer.h>
#include <Database.h>
#include <DisplaySizeType.h>

#include <DisplayManager.h>
#include <WindowDefinition.h>

#include <LSRLimits.h>

#include <AreaType.h>
#include <ExpressionTermType.h>
#include <StaticBitmapFieldType.h>
#include <ReferenceBitmapFieldType.h>
#include <PanelType.h>
#include <Telltales.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <new>

using ::testing::Ref;
using ::testing::Return;
using ::testing::_;

using namespace lsr;

TEST(WidgetTest, AddChildrenReturnTrueTest)
{
    MockWidget widget;

    for (U8 i=0U; i < MAX_WIDGET_CHILDREN_COUNT; ++i)
    {
        MockWidget child;
        EXPECT_TRUE(widget.addChild(&child));
    }
}

TEST(WidgetTest, AddChildrenReturnFalseTest)
{
    MockWidget widget;

    MockWidget child;
    for (U8 i=0U; i < MAX_WIDGET_CHILDREN_COUNT; ++i)
    {
        EXPECT_TRUE(widget.addChild(&child));
    }

    EXPECT_FALSE(widget.addChild(&child));
}

TEST(WidgetTest, InvalidatedTest)
{
    MockWidget widget;

    EXPECT_TRUE(widget.isInvalidated());

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    widget.draw(canvas, area);

    EXPECT_FALSE(widget.isInvalidated());
}

TEST(WidgetTest, InvalidatedWithChildrenTest)
{
    MockWidget widget;
    MockWidget child1;
    MockWidget child2;

    widget.addChild(&child1);
    widget.addChild(&child2);

    EXPECT_TRUE(widget.isInvalidated());

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    widget.draw(canvas, area);
    EXPECT_FALSE(widget.isInvalidated());

    child1.invalidate();

    EXPECT_TRUE(widget.isInvalidated());

    widget.draw(canvas, area);
    EXPECT_FALSE(widget.isInvalidated());

    child2.invalidate();

    EXPECT_TRUE(widget.isInvalidated());
}

TEST(WidgetTest, GetErrorTest1)
{
    MockWidget widget;
    LSREngineError expectedError = LSR_ERR_DATASTATUS_NOT_AVAILABLE;
    widget.setError(expectedError);

    EXPECT_EQ(expectedError, widget.getError());
}

TEST(WidgetTest, GetErrorTest2)
{
    MockWidget widget;
    LSREngineError expectedError = LSR_POOL_IS_CORRUPTED;
    widget.setError(expectedError);
    EXPECT_EQ(expectedError, widget.getError());

    // Set some error state which is less worse that previous one.
    widget.setError(LSR_ERR_DATASTATUS_NOT_AVAILABLE);
    EXPECT_EQ(expectedError, widget.getError());
}

TEST(WidgetTest, GetChildErrorTest)
{
    MockWidget widget;
    widget.setError(LSR_ERR_DATASTATUS_NOT_AVAILABLE);

    MockWidget child;
    child.setError(LSR_POOL_IS_CORRUPTED);

    widget.addChild(&child);

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widget.getError());
}

TEST(WidgetTest, GetParentErrorTest)
{
    MockWidget widget;
    widget.setError(LSR_POOL_IS_CORRUPTED);

    MockWidget child;
    child.setError(LSR_ERR_DATASTATUS_NOT_AVAILABLE);

    widget.addChild(&child);

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widget.getError());
}

TEST(WidgetTest, IsVisibleReturnTrueTest)
{
    MockWidget widget;
    EXPECT_TRUE(widget.isVisible());
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    widget.setVisible(&visible);
    EXPECT_TRUE(widget.isVisible());
}

TEST(WidgetTest, IsVisibleReturnFalseTest)
{
    MockWidget widget;
    EXPECT_TRUE(widget.isVisible());
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };
    widget.setVisible(&visible);
    EXPECT_FALSE(widget.isVisible());
}

TEST(WidgetTest, IsVisibleWithoutExpressionTest)
{
    MockWidget widget;
    EXPECT_TRUE(widget.isVisible());
}

TEST(WidgetTest, IsVisibleWithWrongExprTest)
{
    MockWidget widget;
    ExpressionTermType visible = { ExpressionTermType::NONE, 5U, NULL };
    widget.setVisible(&visible);
    EXPECT_TRUE(widget.isVisible());
    EXPECT_EQ(LSR_DB_INCONSISTENT, widget.getError());
}

TEST(WidgetTest, OnDrawTest)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    EXPECT_CALL(child, onDraw2(Ref(canvas), _))
        .Times(1);
    EXPECT_CALL(widget, onDraw2(Ref(canvas), _))
        .Times(1);

    widget.draw(canvas, area);
}

TEST(WidgetTest, OnDrawWithNotVisibleObjectTest)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };
    widget.setVisible(&visible);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    EXPECT_CALL(child, onDraw2(Ref(canvas), _))
        .Times(0);
    EXPECT_CALL(widget, onDraw2(Ref(canvas), _))
        .Times(0);

    widget.draw(canvas, area);
}

TEST(WidgetTest, CalculationAreaTest)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area widgetArea(5, 15, 25, 30);
    lsr::Area childArea(2, 3, 4, 5);
    // We shift left-top point with safety width and height
    lsr::Area shiftedChildArea(7, 18, 9, 20);

    widget.setArea(widgetArea);
    child.setArea(childArea);

    EXPECT_CALL(child, onDraw2(Ref(canvas), shiftedChildArea))
        .Times(1);
    EXPECT_CALL(widget, onDraw2(Ref(canvas), widgetArea))
        .Times(1);

    widget.draw(canvas, widgetArea);
}

TEST(WidgetTest, VerifyTest)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    EXPECT_CALL(child, onVerify2(Ref(canvas), _))
        .WillOnce(Return(true));
    EXPECT_CALL(widget, onVerify2(Ref(canvas), _))
        .WillOnce(Return(true));

    EXPECT_TRUE(widget.verify(canvas, area));
}

TEST(WidgetTest, VerifyReturnFalseTest1)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    // shouldn't call
    EXPECT_CALL(child, onVerify2(Ref(canvas), _))
        .Times(0);
    EXPECT_CALL(widget, onVerify2(Ref(canvas), _))
        .WillOnce(Return(false));

    EXPECT_FALSE(widget.verify(canvas, area));
}

TEST(WidgetTest, VerifyReturnFalseTest2)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    EXPECT_CALL(child, onVerify2(Ref(canvas), _))
        .WillOnce(Return(false));
    EXPECT_CALL(widget, onVerify2(Ref(canvas), _))
        .WillOnce(Return(true));

    EXPECT_FALSE(widget.verify(canvas, area));
}
