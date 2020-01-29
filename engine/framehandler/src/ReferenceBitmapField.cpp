/******************************************************************************
**
**   File:        ReferenceBitmapField.cpp
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

#include "ReferenceBitmapField.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <ReferenceBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <Database.h>

#include <new>

namespace lsr
{

ReferenceBitmapField* ReferenceBitmapField::create(WidgetPool& factory,
                                 const Database& db,
                                 const ReferenceBitmapFieldType* const pDdh,
                                 DataContext* const pContext,
                                 LSRErrorCollector& error)
{
    LSREngineError tmpError = LSR_NO_ENGINE_ERROR;
    void* const pRawMemory = factory.referenceBitmapFieldPool().allocate(tmpError);
    error = tmpError;

    ReferenceBitmapField* pField = new (pRawMemory)ReferenceBitmapField(db, pDdh);
    if ((NULL != pField) && (!pField->setup(pContext, error)))
    {
        pField->~ReferenceBitmapField();
        error = factory.referenceBitmapFieldPool().deallocate(pRawMemory);
        pField = NULL;
    }

    return pField;
}

ReferenceBitmapField::ReferenceBitmapField(const Database& db, const ReferenceBitmapFieldType* const pDdh)
    : Field()
    , m_pDdh(pDdh)
    , m_db(db)
    , m_pContext(NULL)
    , m_bitmapId(0U)
{
    ASSERT(NULL != m_pDdh);
}

bool ReferenceBitmapField::setup(DataContext* const pContext, LSRErrorCollector& error)
{
    ASSERT(NULL != pContext);
    ASSERT(NULL != m_pDdh);
    m_pContext = pContext;
    const bool inconsistent = ((!setArea(m_pDdh->GetArea())) || (!setupVisibilityExpr(pContext)) || (!setupBitmapExr(pContext)));
    if (inconsistent)
    {
        error = LSR_DB_INCONSISTENT;
    }

    return (!inconsistent);
}

bool ReferenceBitmapField::setupVisibilityExpr(DataContext* const pContext)
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

bool ReferenceBitmapField::setupBitmapExr(DataContext* const pContext)
{
    const ExpressionTermType* const pType = m_pDdh->GetBitmap();
    const bool typeIsBitmap = (NULL != pType);
    if (typeIsBitmap)
    {
        m_bitmapExpr.setup(pType, pContext);
    }
    return typeIsBitmap;
}

void ReferenceBitmapField::onUpdate(const U32 monotonicTimeMs)
{
    static_cast<void>(monotonicTimeMs);  // ignore unused variable

    BitmapId tmpValue;
    if (tryToUpdateValue(m_bitmapExpr, tmpValue))
    {
        if (m_bitmapId != tmpValue)
        {
            m_bitmapId = tmpValue;
        }
    }
}

void ReferenceBitmapField::onDraw(Canvas& /* dst */, const Area& /* rect */) const
{
}

bool ReferenceBitmapField::onVerify(Canvas& dst, const Area& rect)
{
    bool verified = !isVisible();  // invisible bitmaps: true (visible bitmaps have to be checked)

    if (!verified)
    {
        const StaticBitmap bitmap = m_db.getBitmap(m_bitmapId);
        verified = dst.verify(bitmap, rect);

        if (!verified)
        {
            incrementErrorCounter();
        }
        else
        {
            resetErrorCounter();
        }
    }

    return verified;
}

void ReferenceBitmapField::incrementErrorCounter()
{
    IDataHandler& dh = m_pContext->getDataHandler();

    const DynamicData id = DynamicData(m_pDdh->GetErrorCounterFUDataId());

    Number errorCounter;
    const DataStatus status = dh.getNumber(id, errorCounter);
    const bool invalidData = (DataStatus::VALID != status);
    if (invalidData)
    {
        setError(status.convertToLSRError());
    }

    const bool invalidType = (DATATYPE_INTEGER != errorCounter.getType());
    if (invalidType)
    {
        setError(LSR_ERR_DATASTATUS_INCONSISTENT);
    }

    const bool errorCounterIsIncorrect = (invalidData || invalidType);
    if (!errorCounterIsIncorrect)
    {
        const U32 counterValue = errorCounter.getU32();
        if (counterValue != U32_MAX)
        {
            errorCounter = Number(counterValue + 1U, DATATYPE_INTEGER);
        }

        const bool result = dh.setData(id, errorCounter, status);
        if (!result)
        {
            setError(LSR_DH_INVALID_DATA_ID);
        }
    }
}

void ReferenceBitmapField::resetErrorCounter()
{
    IDataHandler& dh = m_pContext->getDataHandler();

    const DynamicData id = DynamicData(m_pDdh->GetErrorCounterFUDataId());

    Number prevCounterValue;
    const DataStatus status = dh.getNumber(id, prevCounterValue);
    const bool invalidData = (DataStatus::VALID != status);
    if (invalidData)
    {
        setError(status.convertToLSRError());
    }

    const bool invalidType = (DATATYPE_INTEGER != prevCounterValue.getType());
    if (invalidType)
    {
        setError(LSR_ERR_DATASTATUS_INCONSISTENT);
    }

    const bool errorCounterIsIncorrect = (invalidData || invalidType);
    if ((!errorCounterIsIncorrect) && (prevCounterValue.getU32() > 0U))
    {
        const Number errorCounter = Number(0U, DATATYPE_INTEGER);
        const bool result = dh.setData(id, errorCounter, status);
        if (!result)
        {
            setError(LSR_DH_INVALID_DATA_ID);
        }
    }
}

} // namespace lsr
