#ifndef LUXOFTSAFERENDERER_MOCK_WIDGET_H
#define LUXOFTSAFERENDERER_MOCK_WIDGET_H

/******************************************************************************
**
**   File:        MockWidget.h
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

#include <Widget.h>
#include <Canvas.h>
#include <Area.h>

#include <BoolExpression.h>

#include <gmock/gmock.h>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4373)
#endif

class MockWidget: public lsr::Widget
{
public:
    MockWidget()
    {}

    MOCK_METHOD1(onUpdate, void (const U32));

    MOCK_CONST_METHOD2(onDraw, void (lsr::Canvas&, const lsr::Area&));

    MOCK_METHOD2(onVerify, bool (lsr::Canvas&, const lsr::Area&));

    virtual Widget::WidgetType getType() const P_OVERRIDE
    {
        return Widget::WIDGET_TYPE_BITMAP_FIELD;
    }

    bool addChild(Widget* child)
    {
        return Widget::addChild(child);
    }

    void invalidate()
    {
        Widget::invalidate();
    }

    bool isInvalidated() const
    {
        return Widget::isInvalidated();
    }

    void setArea(const lsr::Area& area)
    {
        Widget::setArea(area);
    }

    void setError(LSREngineError error)
    {
        Widget::setError(error);
    }

    void setVisibilityExpr(const lsr::BoolExpression* expr)
    {
        Widget::setVisibilityExpression(expr);
    }

    bool isVisible() const
    {
        return Widget::isVisible();
    }
};

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#endif // LUXOFTSAFERENDERER_MOCK_WIDGET_H
