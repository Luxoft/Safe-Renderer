/******************************************************************************
**
**   File:        Widget.cpp
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

#include "Widget.h"
#include "Assertion.h"
#include "ExpressionTermType.h"

namespace lsr
{

Widget::Widget()
    : NonCopyable()
    , m_isInvalidated(true)
    , m_error(LSR_NO_ENGINE_ERROR)
    , m_isVisible(true)
{
}

Widget::~Widget()
{
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
        res = isChildInvalidated();
    }
    return res;
}

void Widget::setArea(const Area& rect)
{
    m_area = rect;
    invalidate();
}

void Widget::setVisible(const bool visible)
{
    if (m_isVisible != visible)
    {
        m_isVisible = visible;
        invalidate();
    }
}

bool Widget::setVisible(const ExpressionTermType* const visible)
{
    const bool isValid = (visible != NULL) && (visible->GetExpressionTermTypeChoice() == ExpressionTermType::BOOLEAN_CHOICE);
    if (isValid)
    {
        m_isVisible = visible->GetBoolean();
    }
    else
    {
        setError(LSR_DB_INCONSISTENT);
        m_isVisible = true;
    }
    return isValid;
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

void Widget::draw(Canvas& dst, const Area& rect)
{
    m_isInvalidated = false;

    if (isVisible())
    {
        onDraw(dst, rect);
    }
}

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
bool Widget::verify(Canvas& dst, const Area& rect)
{
    return onVerify(dst, rect);

}

// coverity[misra_cpp_2008_rule_7_5_4_violation] Recursion is required by design and limited by database structure (panels cannot be nested)
LSREngineError Widget::getError() const
{
    LSRErrorCollector error = m_error.get();
    error = getChildError();
    return error.get();
}

} // namespace lsr
