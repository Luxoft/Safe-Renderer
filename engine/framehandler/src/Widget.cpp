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

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
LSREngineError Widget::dispose(WidgetPool& factory, Widget* const pWidget)
{
    LSREngineError error = LSR_NO_ENGINE_ERROR;
    if (NULL != pWidget)
    {
        for (std::size_t idx = 0U; idx < pWidget->numChildren(); ++idx)
        {
            static_cast<void>(error);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            // coverity[stack_use_unknown]
            error = dispose(factory, pWidget->childAt(idx));
            if (error != LSR_NO_ENGINE_ERROR)
            {
                break;
            }
        }

        if (error == LSR_NO_ENGINE_ERROR)
        {
            const WidgetType type = pWidget->getType();

            switch (type)
            {
            case WIDGET_TYPE_FRAME:
                pWidget->~Widget();
                error = factory.framePool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_PANEL:
                pWidget->~Widget();
                error = factory.panelPool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_BITMAP_FIELD:
                pWidget->~Widget();
                error = factory.bitmapFieldPool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_REF_BITMAP_FIELD:
                pWidget->~Widget();
                error = factory.referenceBitmapFieldPool().deallocate(pWidget);
                break;
            case WIDGET_TYPE_WINDOW:
                pWidget->~Widget();
                error = factory.windowPool().deallocate(pWidget);
                break;
            default:
                error = LSR_POOL_INVALID_OBJECT;
                break;
            }
        }
    }
    else
    {
        static_cast<void>(error);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        error = LSR_POOL_INVALID_OBJECT;
    }

    return error;
}

// coverity[misra_cpp_2008_rule_0_1_10_violation : FALSE] Constructor is called by derived classes, e.g. Field
Widget::Widget()
    : NonCopyable()
    , m_childrenCount(0U)
    , m_isInvalidated(true)
    , m_error(LSR_NO_ENGINE_ERROR)
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
    return (index < m_childrenCount) ? m_children[index] : NULL;
}

void Widget::invalidate()
{
    m_isInvalidated = true;
}

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
bool Widget::isInvalidated() const
{
    bool res = m_isInvalidated;
    if (!res)
    {
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            // maybe replace recursion by iterative approach to control stack usage
            // coverity[stack_use_unknown]
            if (m_children[i]->isInvalidated())
            {
                res = true;
                break;
            }
        }
    }
    return res;
}

bool Widget::addChild(Widget* const pChild)
{
    const bool addable = (m_childrenCount < MAX_WIDGET_CHILDREN_COUNT);
    if (addable)
    {
        m_children[m_childrenCount] = pChild;
        ++m_childrenCount;
    }
    return addable;
}

void Widget::setArea(const Area& rect)
{
    m_area = rect;
}

bool Widget::setArea(const AreaType* const pDdhArea)
{
    const bool assignable = (NULL != pDdhArea);
    if (assignable)
    {
        m_area = Area(pDdhArea);
    }
    return assignable;
}

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
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

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
void Widget::draw(Canvas& dst, const Area& rect)
{
    m_isInvalidated = false;

    if (isVisible())
    {
        onDraw(dst, rect);

        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            Widget* pChild = m_children[i];
            ASSERT(pChild != NULL);

            Area childArea(pChild->getArea());
            childArea.moveByFP(rect.getLeftFP(), rect.getTopFP());

            // coverity[stack_use_unknown]
            pChild->draw(dst, childArea);
        }
    }
}

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
bool Widget::verify(Canvas& dst, const Area& rect)
{
    bool result = onVerify(dst, rect);

    if (result)
    {
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            Widget* pChild = m_children[i];
            ASSERT(pChild != NULL);

            Area childArea(pChild->getArea());
            childArea.moveByFP(rect.getLeftFP(), rect.getTopFP());

            // coverity[stack_use_unknown]
            if (!pChild->verify(dst, childArea))
            {
                result = false;
                static_cast<void>(result);  // suppress MISRA 0-1-6: Value is not used on this path
            }
        }
    }

    return result;
}

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
LSREngineError Widget::getError() const
{
    LSRErrorCollector error = m_error.get();

    for (std::size_t idx = 0U; idx < numChildren(); ++idx)
    {
        const Widget* pChild = childAt(idx);
        ASSERT(pChild != NULL);

        // coverity[stack_use_unknown]
        const LSREngineError childError = pChild->getError();
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
            static_cast<void>(visible);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            visible = tmpValue;
        }
    }
    else
    {
        static_cast<void>(visible);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        visible = true;
    }

    if (m_isVisible != visible)
    {
        m_isVisible = visible;
        invalidate();
    }
}

} // namespace lsr
