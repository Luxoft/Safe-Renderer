/******************************************************************************
**
**   File:        WidgetTest.cpp
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

#include "MockWidget.h"
#include "WrongWidget.h"
#include "WidgetPoolHelper.h"
#include "TestCanvas.h"

#include <ResourceBuffer.h>
#include <Database.h>
#include <DisplaySizeType.h>

#include <DataContext.h>
#include <MockDataHandler.h>

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

TEST(WidgetTest, ChildAtTest)
{
    MockWidget widget;

    MockWidget children[MAX_WIDGET_CHILDREN_COUNT];

    for (U8 i=0U; i < MAX_WIDGET_CHILDREN_COUNT; ++i)
    {
        EXPECT_TRUE(widget.addChild(&children[i]));
    }

    for (U8 i=0U; i < MAX_WIDGET_CHILDREN_COUNT; ++i)
    {
        EXPECT_EQ(&children[i], widget.childAt(i));
    }
}

TEST(WidgetTest, ChildAtReturnNullTest)
{
    MockWidget widget;

    EXPECT_EQ(NULL, widget.childAt(0));

    MockWidget child;
    EXPECT_TRUE(widget.addChild(&child));
    EXPECT_TRUE(widget.addChild(&child));

    EXPECT_EQ(NULL, widget.childAt(2));
}

TEST(WidgetTest, NumChildrenTest)
{
    MockWidget widget;
    std::size_t expectedNumber = MAX_WIDGET_CHILDREN_COUNT - 1;

    MockWidget child;
    for (U8 i=0U; i < expectedNumber; ++i)
    {
        EXPECT_TRUE(widget.addChild(&child));
    }

    EXPECT_EQ(expectedNumber, widget.numChildren());
}

TEST(WidgetTest, InvalidatedTest)
{
    MockWidget widget;

    EXPECT_TRUE(widget.isInvalidated());

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    widget.update(0U);
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

    widget.update(0U);
    widget.draw(canvas, area);
    EXPECT_FALSE(widget.isInvalidated());

    child1.invalidate();

    EXPECT_TRUE(widget.isInvalidated());

    widget.draw(canvas, area);
    EXPECT_FALSE(widget.isInvalidated());

    child2.invalidate();

    EXPECT_TRUE(widget.isInvalidated());
}

TEST(WidgetTest, UpdateTest)
{
    MockWidget widget;
    U32 expectedTime = 435U;

    EXPECT_CALL(widget, onUpdate(expectedTime))
        .Times(1);

    widget.update(expectedTime);
}

TEST(WidgetTest, DisposeBitmapFieldTest)
{
    const AreaType area = { 0U, 0U, 0U, 0U };
    const ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    const ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    const StaticBitmapFieldType bmpField = { &area, &visible, &bmp };

    lsr::Database db(Telltales::getDDH());

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);
    lsr::BitmapField* field = helper.fillUpWithBitmaps(&bmpField,
                                                       db,
                                                       &context);
    EXPECT_TRUE(helper.isBitMapPoolFilled());

    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), lsr::Widget::dispose(widgetPool, field));

    EXPECT_FALSE(helper.isBitMapPoolFilled());
}

TEST(WidgetTest, DisposeReferenceBitmapFieldTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    ExpressionTermType bmp = { ExpressionTermType::BITMAPID_CHOICE, 23U, NULL };
    ReferenceBitmapFieldType bmpField = { 43U, &area, &visible, &bmp };

    lsr::Database db(Telltales::getDDH());

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);
    lsr::ReferenceBitmapField* field = helper.fillUpWithReferenceBitmaps(&bmpField,
                                                                         db,
                                                                         &context);
    EXPECT_TRUE(helper.isReferenceBitMapPoolFilled());

    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), lsr::Widget::dispose(widgetPool, field));

    EXPECT_FALSE(helper.isReferenceBitMapPoolFilled());
}


TEST(WidgetTest, DisposePanelTest)
{
    AreaType area = { 0U, 0U, 0U, 0U };
    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };
    PanelType tpanel = { &area, &visible, NULL, 0 };

    lsr::Database db(Telltales::getDDH());

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);
    lsr::Panel* panel = helper.fillUpWithPanels(&tpanel,
                                                db,
                                                &context);
    EXPECT_TRUE(helper.isPanelPoolFilled());

    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), lsr::Widget::dispose(widgetPool, panel));

    EXPECT_FALSE(helper.isPanelPoolFilled());
}

TEST(WidgetTest, DisposeFrameTest)
{
    lsr::Database db(Telltales::getDDH());

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);
    lsr::Frame* frame = helper.fillUpWithFrames(db,
                                                1U,
                                                NULL,
                                                &context);

    EXPECT_TRUE(helper.isFramePoolFilled());

    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), lsr::Widget::dispose(widgetPool, frame));

    EXPECT_FALSE(helper.isFramePoolFilled());
}

TEST(WidgetTest, DisposeWindowTest)
{
    lsr::Database db(Telltales::getDDH());

    lsr::WindowDefinition winDef;
    lsr::DisplayManager dm;

    lsr::WidgetPool widgetPool;
    WidgetPoolHelper helper(widgetPool);
    MockDataHandler dataHandler;
    DataContext context(dataHandler);
    lsr::Window* window = helper.fillUpWithWindows(db,
                                                   dm,
                                                   winDef,
                                                   &context);

    EXPECT_TRUE(helper.isWindowPoolFilled());

    EXPECT_EQ(LSREngineError(LSR_NO_ENGINE_ERROR), lsr::Widget::dispose(widgetPool, window));

    EXPECT_FALSE(helper.isWindowPoolFilled());
}

TEST(WidgetTest, DisposeNullObjTest)
{
    lsr::WidgetPool widgetPool;

    EXPECT_EQ(LSREngineError(LSR_POOL_INVALID_OBJECT),
              lsr::Widget::dispose(widgetPool, NULL));
}

TEST(WidgetTest, DisposeObjWithWrongTypeTest)
{
    U8 buf[sizeof(WrongWidget)];
    WrongWidget* widget = new (buf) WrongWidget();
    lsr::WidgetPool widgetPool;
    EXPECT_EQ(LSREngineError(LSR_POOL_INVALID_OBJECT),
              lsr::Widget::dispose(widgetPool, widget));
}

TEST(WidgetTest, DisposeObjWithWrongChildrenTypeTest)
{
    U8 buf1[sizeof(WrongWidget)];
    U8 buf2[sizeof(WrongWidget)];
    WrongWidget* widget = new (buf1)WrongWidget();
    WrongWidget* child = new(buf2)WrongWidget();
    widget->addChild(child);

    lsr::WidgetPool widgetPool;
    EXPECT_EQ(LSREngineError(LSR_POOL_INVALID_OBJECT),
              lsr::Widget::dispose(widgetPool, widget));
}

TEST(WidgetTest, GetErrorTest1)
{
    WrongWidget widget;
    LSREngineError expectedError = LSR_ERR_DATASTATUS_NOT_AVAILABLE;
    widget.setError(expectedError);

    EXPECT_EQ(expectedError, widget.getError());
}

TEST(WidgetTest, GetErrorTest2)
{
    WrongWidget widget;
    LSREngineError expectedError = LSR_POOL_IS_CORRUPTED;
    widget.setError(expectedError);
    EXPECT_EQ(expectedError, widget.getError());

    // Set some error state which is less worse that previous one.
    widget.setError(LSR_ERR_DATASTATUS_NOT_AVAILABLE);
    EXPECT_EQ(expectedError, widget.getError());
}

TEST(WidgetTest, GetChildErrorTest)
{
    WrongWidget widget;
    widget.setError(LSR_ERR_DATASTATUS_NOT_AVAILABLE);

    WrongWidget child;
    child.setError(LSR_POOL_IS_CORRUPTED);

    widget.addChild(&child);

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widget.getError());
}

TEST(WidgetTest, GetParentErrorTest)
{
    WrongWidget widget;
    widget.setError(LSR_POOL_IS_CORRUPTED);

    WrongWidget child;
    child.setError(LSR_ERR_DATASTATUS_NOT_AVAILABLE);

    widget.addChild(&child);

    EXPECT_EQ(LSR_POOL_IS_CORRUPTED, widget.getError());
}

TEST(WidgetTest, IsVisibleReturnTrueTest)
{
    MockWidget widget;

    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 1U, NULL };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::BoolExpression expr;
    expr.setup(&visible, &context);

    widget.setVisibilityExpr(&expr);

    EXPECT_FALSE(widget.isVisible());

    widget.update(0U);

    EXPECT_TRUE(widget.isVisible());
}

TEST(WidgetTest, IsVisibleReturnFalseTest)
{
    MockWidget widget;

    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::BoolExpression expr;
    expr.setup(&visible, &context);

    widget.setVisibilityExpr(&expr);

    EXPECT_FALSE(widget.isVisible());

    widget.update(0U);

    EXPECT_FALSE(widget.isVisible());
}

TEST(WidgetTest, IsVisibleWithoutExpressionTest)
{
    MockWidget widget;

    EXPECT_FALSE(widget.isVisible());

    widget.update(0U);

    EXPECT_TRUE(widget.isVisible());
}

TEST(WidgetTest, IsVisibleWithWrongExprTest)
{
    MockWidget widget;

    ExpressionTermType visible = { ExpressionTermType::NONE, 5U, NULL };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::BoolExpression expr;
    expr.setup(&visible, &context);

    widget.setVisibilityExpr(&expr);

    EXPECT_FALSE(widget.isVisible());

    widget.update(0U);

    EXPECT_FALSE(widget.isVisible());
    EXPECT_EQ(LSR_ERR_DATASTATUS_INCONSISTENT, widget.getError());
}

TEST(WidgetTest, OnDrawTest)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    widget.update(0U);

    EXPECT_CALL(child, onDraw(Ref(canvas), _))
        .Times(1);
    EXPECT_CALL(widget, onDraw(Ref(canvas), _))
        .Times(1);

    widget.draw(canvas, area);
}

TEST(WidgetTest, OnDrawWithNotVisibleObjectTest)
{
    MockWidget widget;
    MockWidget child;
    widget.addChild(&child);

    ExpressionTermType visible = { ExpressionTermType::BOOLEAN_CHOICE, 0U, NULL };

    MockDataHandler dataHandler;
    DataContext context(dataHandler);

    lsr::BoolExpression expr;
    expr.setup(&visible, &context);

    widget.setVisibilityExpr(&expr);

    lsr::DisplayManager dsp;
    TestCanvas canvas(dsp, 640U, 480U);
    lsr::Area area;

    widget.update(0U);

    EXPECT_CALL(child, onDraw(Ref(canvas), _))
        .Times(0);
    EXPECT_CALL(widget, onDraw(Ref(canvas), _))
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

    widget.update(0U);

    EXPECT_CALL(child, onDraw(Ref(canvas), shiftedChildArea))
        .Times(1);
    EXPECT_CALL(widget, onDraw(Ref(canvas), widgetArea))
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

    widget.update(0U);

    EXPECT_CALL(child, onVerify(Ref(canvas), _))
        .WillOnce(Return(true));
    EXPECT_CALL(widget, onVerify(Ref(canvas), _))
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

    widget.update(0U);

    // shouldn't call
    EXPECT_CALL(child, onVerify(Ref(canvas), _))
        .Times(0);
    EXPECT_CALL(widget, onVerify(Ref(canvas), _))
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

    widget.update(0U);

    EXPECT_CALL(child, onVerify(Ref(canvas), _))
        .WillOnce(Return(false));
    EXPECT_CALL(widget, onVerify(Ref(canvas), _))
        .WillOnce(Return(true));

    EXPECT_FALSE(widget.verify(canvas, area));
}
