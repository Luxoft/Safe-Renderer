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

bool Panel::setup(WidgetPool& factory,
                  const Database& db,
                  DataContext* const pContext,
                  LSRErrorCollector& error)
{
    bool successful = setArea(m_pDdh->GetArea()) && setupVisibilityExpr(pContext);

    if (successful)
    {
        const U16 numFields = m_pDdh->GetFieldCount();
        for (U16 i = 0U; i < numFields; ++i)
        {
            const BaseFieldChoiceType* pFieldType = m_pDdh->GetField(i);
            Field* const pField = Field::create(factory, db, pFieldType, pContext, error);
            if ((NULL == pField) || (!addChild(pField)))
            {
                successful = false;
                break;
            }
        }
    }
    else
    {
        error = LSR_DB_INCONSISTENT;
    }

    return successful;
}

Panel* Panel::create(WidgetPool& factory,
                     const Database& db,
                     const PanelType* const pDdhPanel,
                     DataContext* const pContext,
                     LSRErrorCollector& error)
{

    ASSERT(NULL != pDdhPanel);

    LSREngineError tmpError = LSR_NO_ENGINE_ERROR;
    void* const pRawMemory = factory.panelPool().allocate(tmpError);
    error = tmpError;

    Panel* pPanel = new(pRawMemory)Panel(pDdhPanel);
    if (NULL != pPanel)
    {
        if (!pPanel->setup(factory, db, pContext, error))
        {
            pPanel->~Panel();
            error = factory.panelPool().deallocate(pRawMemory);
            pPanel = NULL;
        }
    }

    return pPanel;
}

bool Panel::setupVisibilityExpr(DataContext* const pContext)
{
    const ExpressionTermType* const pType = m_pDdh->GetVisible();
    const bool typeIsVisibility = (NULL != pType);
    if (typeIsVisibility)
    {
        m_visibilityExpr.setup(pType, pContext);
        setVisibilityExpression(&m_visibilityExpr);
    }
    return typeIsVisibility;
}

void Panel::onUpdate(const U32 monotonicTimeMs)
{
    static_cast<void>(monotonicTimeMs);  // ignore unused variable
}

void Panel::onDraw(Canvas& /* dst */, const Area& /* rect */) const
{}

bool Panel::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace lsr
