/******************************************************************************
**
**   File:        Widget.cpp
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

#include "Widget.h"
#include "WidgetPool.h"
#include "Assertion.h"

namespace lsr
{

LSRError Widget::dispose(WidgetPool& widgetPool, Widget* const pWidget)
{
    LSRError error = LSR_NO_ERROR;
    if (NULL != pWidget)
    {
        for (std::size_t idx = 0U; idx < pWidget->numChildren(); ++idx)
        {
            // coverity[stack_use_unknown]
            error = dispose(widgetPool, pWidget->childAt(idx));
            if (error != LSR_NO_ERROR)
            {
                break;
            }
        }

        if (error == LSR_NO_ERROR)
        {
            const WidgetType widgetType = pWidget->getType();

            switch (widgetType)
            {
            case WIDGET_TYPE_FRAME:
                pWidget->~Widget();
                error = widgetPool.framePool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_PANEL:
                pWidget->~Widget();
                error = widgetPool.panelPool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_BITMAP_FIELD:
                pWidget->~Widget();
                error = widgetPool.bitmapFieldPool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_REF_BITMAP_FIELD:
                pWidget->~Widget();
                error = widgetPool.referenceBitmapFieldPool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_WINDOW:
                pWidget->~Widget();
                error = widgetPool.windowPool().deallocate(pWidget);
                break;
            default:
                error = LSR_POOL_INVALID_OBJECT;
                break;
            }
        }
    }
    else
    {
        error = LSR_POOL_INVALID_OBJECT;
    }

    return error;
}

Widget::Widget()
    : NonCopyable<Widget>()
    , m_childrenCount(0U)
    , m_isInvalidated(true)
    , m_error(LSR_NO_ERROR)
    , m_pVisibilityExpr(NULL)
    , m_isVisible(false)
{
    for (size_t pos = 0U; pos < MAX_WIDGET_CHILDREN_COUNT; ++pos)
    {
        m_children[pos] = NULL;
    }
}

Widget::~Widget()
{
}

Widget* Widget::childAt(const std::size_t index) const
{
    Widget* pRes = NULL;
    if (index < m_childrenCount)
    {
        pRes = m_children[index];
    }

    return pRes;
}

void Widget::invalidate()
{
    m_isInvalidated = true;
}

bool Widget::isInvalidated() const
{
    bool ret = m_isInvalidated;
    if (!ret)
    {
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            // maybe replace recursion by iterative approach to control stack usage
            // coverity[stack_use_unknown]
            if (m_children[i]->isInvalidated())
            {
                ret = true;
                break;
            }
        }
    }
    return ret;
}

bool Widget::addChild(Widget* const pChild)
{
    bool res = false;
    if (m_childrenCount < MAX_WIDGET_CHILDREN_COUNT)
    {
        m_children[m_childrenCount] = pChild;
        m_childrenCount++;
        res = true;
    }

    return res;
}

void Widget::setArea(const Area& area)
{
    m_area = area;
}

bool Widget::setArea(const AreaType* const pDdhArea)
{
    bool res = false;
    if (NULL != pDdhArea)
    {
        m_area = Area(pDdhArea);
        res = true;
    }
    return res;
}

void Widget::update(const U32 monotonicTimeMs)
{
    updateVisibility(/* monotonicTimeMs */);

    onUpdate(monotonicTimeMs);
    for (std::size_t i = 0U; i < m_childrenCount; ++i)
    {
        // coverity[stack_use_unknown]
        m_children[i]->update(monotonicTimeMs);
    }
}

void Widget::draw(Canvas& canvas, const Area& area)
{
    m_isInvalidated = false;

    if (isVisible())
    {
        onDraw(canvas, area);

        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            Widget* pChild = m_children[i];
            ASSERT(pChild != NULL);

            Area childArea(pChild->getArea());
            childArea.moveByFP(area.getLeftFP(), area.getTopFP());

            // coverity[stack_use_unknown]
            pChild->draw(canvas, childArea);
        }
    }
}

bool Widget::verify(Canvas& canvas, const Area& area)
{
    bool result = onVerify(canvas, area);

    if (result)
    {
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            Widget* pChild = m_children[i];
            ASSERT(pChild != NULL);

            Area childArea(pChild->getArea());
            childArea.moveByFP(area.getLeftFP(), area.getTopFP());

            // coverity[stack_use_unknown]
            if (!pChild->verify(canvas, childArea))
            {
                result = false;
            }
        }
    }

    return result;
}

LSRError Widget::getError() const
{
    LSRErrorCollector error = m_error.get();

    for (std::size_t idx = 0U; idx < numChildren(); ++idx)
    {
        const Widget* pChild = childAt(idx);
        ASSERT(pChild != NULL);

        // coverity[stack_use_unknown]
        const LSRError childError = pChild->getError();
        error = childError;
    }

    return error.get();
}

void Widget::updateVisibility(/* const U32 monotonicTimeMs */)
{
    bool visible = m_isVisible;
    if (NULL != m_pVisibilityExpr)
    {
        bool tmpValue = false;
        if (tryToUpdateValue(*m_pVisibilityExpr, tmpValue))
        {
            visible = tmpValue;
        }
    }
    else
    {
        visible = true;
    }

    if (m_isVisible != visible)
    {
        m_isVisible = visible;
        invalidate();
    }
}

} // namespace lsr
