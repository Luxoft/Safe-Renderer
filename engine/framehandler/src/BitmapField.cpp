/******************************************************************************
**
**   File:        BitmapField.cpp
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

#include "BitmapField.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <StaticBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <Database.h>

#include <new>

namespace psc
{

BitmapField* BitmapField::create(WidgetPool& widgetPool,
                                 const Database& db,
                                 const StaticBitmapFieldType* pDdh,
                                 DataContext* pContext,
                                 PSCErrorCollector& error)
{
    PSCError tmpError = PSC_NO_ERROR;
    void* pRawMemory = widgetPool.bitmapFieldPool().allocate(tmpError);
    error = tmpError;

    BitmapField* pField = new (pRawMemory)BitmapField(db, pDdh);
    if (NULL != pField && !pField->setup(pContext, error))
    {
        pField->~BitmapField();
        error = widgetPool.bitmapFieldPool().deallocate(pRawMemory);
        pField = NULL;
    }

    return pField;
}

BitmapField::BitmapField(const Database& db, const StaticBitmapFieldType* const pDdh)
    : m_pDdh(pDdh)
    , m_db(db)
{
    ASSERT(NULL != m_pDdh);
}

bool BitmapField::setup(DataContext* pContext, PSCErrorCollector& error)
{
    ASSERT(NULL != pContext);
    ASSERT(NULL != m_pDdh);

    bool res = true;
    if (!setArea(m_pDdh->GetArea()) || !setupVisibilityExpr(pContext) || !setupBitmapExr(pContext))
    {
        error = PSC_DB_INCONSISTENT;
        res = false;
    }

    return res;
}

bool BitmapField::setupVisibilityExpr(DataContext* pContext)
{
    bool res = false;
    const ExpressionTermType* pType = m_pDdh->GetVisible();
    if (NULL != pType)
    {
        m_visibilityExpr.setup(pType, pContext);
        setVisibilityExpression(&m_visibilityExpr);
        res = true;
    }
    return res;
}

bool BitmapField::setupBitmapExr(DataContext* pContext)
{
    bool res = false;
    const ExpressionTermType* pType = m_pDdh->GetBitmap();
    if (NULL != pType)
    {
        m_bitmapExpr.setup(pType, pContext, NULL);
        res = true;
    }
    return res;
}

void BitmapField::onUpdate(const U32 /* monotonicTimeMs */)
{
    BitmapId tmpValue;
    if (tryToUpdateValue(m_bitmapExpr, tmpValue))
    {
        if (m_bitmapId != tmpValue)
        {
            m_bitmapId = tmpValue;
            invalidate();
        }
    }
}

void BitmapField::onDraw(Canvas& canvas, const Area& area)
{
    StaticBitmap bitmap = m_db.getBitmap(m_bitmapId);

    canvas.drawBitmap(bitmap, area);
}

bool BitmapField::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace psc
