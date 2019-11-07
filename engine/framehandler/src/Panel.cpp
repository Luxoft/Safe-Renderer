/******************************************************************************
**
**   File:        Panel.cpp
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

#include "Panel.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <DDHType.h>
#include <PanelType.h>

#include <new>

namespace lsr
{

Panel::Panel(const PanelType* const pDdh)
    : Widget()
    , m_pDdh(pDdh)
{
}

bool Panel::setup(WidgetPool& widgetPool,
                  const Database& db,
                  DataContext* const pContext,
                  LSRErrorCollector& error)
{
    bool success = setArea(m_pDdh->GetArea()) && setupVisibilityExpr(pContext);

    if (success)
    {
        const U16 numFields = m_pDdh->GetFieldCount();
        for (U16 i = 0U; i < numFields; ++i)
        {
            const BaseFieldChoiceType* pFieldType = m_pDdh->GetField(i);
            Field* const pField = Field::create(widgetPool, db, pFieldType, pContext, error);
            if ((NULL == pField) || (!addChild(pField)))
            {
                success = false;
                break;
            }
        }
    }
    else
    {
        error = LSR_DB_INCONSISTENT;
    }

    return success;
}

Panel* Panel::create(WidgetPool& widgetPool,
                     const Database& db,
                     const PanelType* const pDdhPanel,
                     DataContext* const pContext,
                     LSRErrorCollector& error)
{

    ASSERT(NULL != pDdhPanel);

    LSRError tmpError = LSR_NO_ERROR;
    void* const pRawMemory = widgetPool.panelPool().allocate(tmpError);
    error = tmpError;

    Panel* pPanel = new(pRawMemory)Panel(pDdhPanel);
    if (NULL != pPanel)
    {
        if (!pPanel->setup(widgetPool, db, pContext, error))
        {
            pPanel->~Panel();
            error = widgetPool.panelPool().deallocate(pRawMemory);
            pPanel = NULL;
        }
    }

    return pPanel;
}

bool Panel::setupVisibilityExpr(DataContext* const pContext)
{
    bool res = false;
    const ExpressionTermType* const pType = m_pDdh->GetVisible();
    if (NULL != pType)
    {
        m_visibilityExpr.setup(pType, pContext);
        setVisibilityExpression(&m_visibilityExpr);
        res = true;
    }
    return res;
}

void Panel::onUpdate(const U32 monotonicTimeMs)
{
    static_cast<void>(monotonicTimeMs);  // ignore unused variable
}

void Panel::onDraw(Canvas& /* canvas */, const Area& /* area */)
{}

bool Panel::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace lsr
