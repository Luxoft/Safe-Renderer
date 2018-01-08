#ifndef POPULUSSC_MOCK_WIDGET_H
#define POPULUSSC_MOCK_WIDGET_H

/******************************************************************************
**
**   File:        MockWidget.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
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

class MockWidget: public psc::Widget
{
public:
    MockWidget()
    {}

    MOCK_METHOD1(onUpdate, void (const U32));

    MOCK_METHOD2(onDraw, void (psc::Canvas&, const psc::Area&));

    MOCK_METHOD2(onVerify, bool (psc::Canvas&, const psc::Area&));

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

    void setArea(const psc::Area& area)
    {
        Widget::setArea(area);
    }

    void setError(PSCError error)
    {
        Widget::setError(error);
    }

    void setVisibilityExpr(const psc::BoolExpression* expr)
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

#endif // POPULUSSC_MOCK_WIDGET_H
