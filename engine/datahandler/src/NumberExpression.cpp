/******************************************************************************
**
**   File:        NumberExpression.cpp
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

#include <NumberExpression.h>

#include <Assertion.h>

namespace lsr
{

NumberExpression::NumberExpression()
    : m_pTerm(NULL)
    , m_pListener(NULL)
    , m_pContext(NULL)
    , m_status(DataStatus::NOT_AVAILABLE)
{
}

NumberExpression::~NumberExpression()
{
    dispose();
}

void NumberExpression::setup(const ExpressionTermType *pTerm,
                             DataContext* pContext,
                             Expression::IListener* pListener)
{
    dispose();

    ASSERT(NULL != pTerm);

    m_pTerm = pTerm;
    m_pListener = pListener;
    m_pContext = pContext;
    Expression::subscribe(pTerm, m_pContext, (pListener != NULL) ? this : NULL);
}

void NumberExpression::dispose()
{
    if (NULL != m_pTerm)
    {
        Expression::unsubscribe(m_pTerm, m_pContext, (m_pListener != NULL) ? this : NULL);
        m_pTerm = NULL;
    }
    m_pListener = NULL;
}

DataStatus NumberExpression::getValue(Number& value) const
{
    if (NULL == m_pListener)
    {
        m_status = getNumber(m_pTerm, m_pContext, m_value);
    }

    value = m_value;
    return m_status;
}

void NumberExpression::update()
{
    if (NULL != m_pListener)
    {
        m_status = getNumber(m_pTerm, m_pContext, m_value);

        m_pListener->notifyDataChange(*this);
    }
}

} // namespace lsr
