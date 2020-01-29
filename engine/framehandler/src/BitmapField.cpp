/******************************************************************************
**
**   File:        BitmapField.cpp
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

#include "BitmapField.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <StaticBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <Database.h>

#include <new>

namespace lsr
{

BitmapField* BitmapField::create(WidgetPool& factory,
                                 const Database& db,
                                 const StaticBitmapFieldType* const pDdh,
                                 DataContext* const pContext,
                                 LSRErrorCollector& error)
{
    LSREngineError tmpError = LSR_NO_ENGINE_ERROR;
    void* const pRawMemory = factory.bitmapFieldPool().allocate(tmpError);
    error = tmpError;

    BitmapField* pField = new (pRawMemory)BitmapField(db, pDdh);
    if ((NULL != pField) && (!pField->setup(pContext, error)))
    {
        pField->~BitmapField();
        error = factory.bitmapFieldPool().deallocate(pRawMemory);
        pField = NULL;
    }

    return pField;
}

BitmapField::BitmapField(const Database& db, const StaticBitmapFieldType* const pDdh)
    : Field()
    , m_pDdh(pDdh)
    , m_db(db)
    , m_bitmapExpr()
    , m_bitmapId(0U)
{
    ASSERT(NULL != m_pDdh);
}

bool BitmapField::setup(DataContext* const pContext, LSRErrorCollector& error)
{
    ASSERT(NULL != pContext);
    ASSERT(NULL != m_pDdh);

    const bool inconsistent = ((!setArea(m_pDdh->GetArea())) || (!setupVisibilityExpr(pContext)) || (!setupBitmapExr(pContext)));
    if (inconsistent)
    {
        error = LSR_DB_INCONSISTENT;
    }

    return (!inconsistent);
}

bool BitmapField::setupVisibilityExpr(DataContext* const pContext)
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

bool BitmapField::setupBitmapExr(DataContext* const pContext)
{
    const ExpressionTermType* const pType = m_pDdh->GetBitmap();
    const bool typeIsBitmap = (NULL != pType);
    if (typeIsBitmap)
    {
        m_bitmapExpr.setup(pType, pContext);
    }
    return typeIsBitmap;
}

void BitmapField::onUpdate(const U32 monotonicTimeMs)
{
    static_cast<void>(monotonicTimeMs);  // ignore unused variable

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

void BitmapField::onDraw(Canvas& dst, const Area& rect) const
{
    const StaticBitmap bitmap = m_db.getBitmap(m_bitmapId);
    dst.drawBitmap(bitmap, rect);
}

bool BitmapField::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace lsr
