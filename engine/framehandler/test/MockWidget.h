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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include <Widget.h>
#include <Field.h>
#include <WidgetChildren.h>
#include <Canvas.h>
#include <Area.h>

#include <gmock/gmock.h>

#ifdef _MSC_VER
#pragma warning (push)
#pragma warning (disable : 4373)
#endif

namespace lsr
{
    class MockField : public Field
    {
    public:
        MOCK_METHOD1(setup, LSREngineError(const Database&));
        MOCK_CONST_METHOD2(onDraw, void(Canvas&, const Area&));
        MOCK_METHOD2(onVerify, bool(Canvas&, const Area&));

        virtual bool isChildInvalidated() const P_OVERRIDE
        {
            return false;
        }

        virtual LSREngineError getChildError() const P_OVERRIDE
        {
            return LSR_NO_ENGINE_ERROR;
        }
    };
}

class WidgetWithChildren : public lsr::Widget
{
protected:
    virtual void onDraw2(lsr::Canvas& dest, const lsr::Area& rect) const = 0;
    virtual bool onVerify2(lsr::Canvas& dest, const lsr::Area& rect) = 0;
public:
    void onDraw(lsr::Canvas& dest, const lsr::Area& rect) const P_OVERRIDE P_FINAL
    {
        onDraw2(dest, rect);
        m_children.draw(dest, rect);
    }

    bool onVerify(lsr::Canvas& dest, const lsr::Area& rect) P_OVERRIDE P_FINAL
    {
        bool res = onVerify2(dest, rect);
        if (res)
        {
            res = m_children.verify(dest, rect);
        }
        return res;
    }

    LSREngineError getChildError() const P_OVERRIDE P_FINAL
    {
        return m_children.getError();
    }

    bool isChildInvalidated() const P_OVERRIDE P_FINAL
    {
        return m_children.isInvalidated();
    }

    bool addChild(WidgetWithChildren* child)
    {
        return m_children.addChild(child);
    }
private:
    lsr::WidgetChildren<WidgetWithChildren, lsr::MAX_WIDGET_CHILDREN_COUNT> m_children;
};

class MockWidget: public WidgetWithChildren
{
public:
    MockWidget()
    {}

    MOCK_CONST_METHOD2(onDraw2, void (lsr::Canvas&, const lsr::Area&));

    MOCK_METHOD2(onVerify2, bool (lsr::Canvas&, const lsr::Area&));

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

    bool isVisible() const
    {
        return Widget::isVisible();
    }
};

#ifdef _MSC_VER
#pragma warning (pop)
#endif

#endif // LUXOFTSAFERENDERER_MOCK_WIDGET_H
