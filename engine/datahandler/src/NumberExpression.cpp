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
    : Expression()
    , m_pTerm(NULL)
    , m_pContext(NULL)
    , m_status(DataStatus::NOT_AVAILABLE)
{
}

NumberExpression::~NumberExpression()
{
    dispose();
}

void NumberExpression::setup(const ExpressionTermType* const pTerm,
                             DataContext* const pContext)
{
    dispose();
    ASSERT(NULL != pTerm);
    m_pTerm = pTerm;
    m_pContext = pContext;
}

void NumberExpression::dispose()
{
    m_pTerm = NULL;
    m_pContext = NULL;
}

DataStatus NumberExpression::getValue(Number& value) const
{
    m_status = getNumber(m_pTerm, m_pContext, m_value);
    value = m_value;
    return m_status;
}

} // namespace lsr
