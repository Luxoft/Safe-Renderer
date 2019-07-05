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

ReferenceBitmapField* ReferenceBitmapField::create(WidgetPool& widgetPool,
                                 const Database& db,
                                 const ReferenceBitmapFieldType* pDdh,
                                 DataContext* pContext,
                                 LSRErrorCollector& error)
{
    LSRError tmpError = LSR_NO_ERROR;
    void* pRawMemory = widgetPool.referenceBitmapFieldPool().allocate(tmpError);
    error = tmpError;

    ReferenceBitmapField* pField = new (pRawMemory)ReferenceBitmapField(db, pDdh);
    if (NULL != pField && !pField->setup(pContext, error))
    {
        pField->~ReferenceBitmapField();
        error = widgetPool.referenceBitmapFieldPool().deallocate(pRawMemory);
        pField = NULL;
    }

    return pField;
}

ReferenceBitmapField::ReferenceBitmapField(const Database& db, const ReferenceBitmapFieldType* pDdh)
    : m_pDdh(pDdh)
    , m_db(db)
    , m_pContext(NULL)
{
    ASSERT(NULL != m_pDdh);
}

bool ReferenceBitmapField::setup(DataContext* pContext, LSRErrorCollector& error)
{
    ASSERT(NULL != pContext);
    ASSERT(NULL != m_pDdh);
    m_pContext = pContext;
    bool res = true;
    if (!setArea(m_pDdh->GetArea()) || !setupVisibilityExpr(pContext) || !setupBitmapExr(pContext))
    {
        error = LSR_DB_INCONSISTENT;
        res = false;
    }

    return res;
}

bool ReferenceBitmapField::setupVisibilityExpr(DataContext* pContext)
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

bool ReferenceBitmapField::setupBitmapExr(DataContext* pContext)
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

void ReferenceBitmapField::onUpdate(const U32 /* monotonicTimeMs */)
{
    BitmapId tmpValue;
    if (tryToUpdateValue(m_bitmapExpr, tmpValue))
    {
        if (m_bitmapId != tmpValue)
        {
            m_bitmapId = tmpValue;
        }
    }
}

void ReferenceBitmapField::onDraw(Canvas& /* canvas */, const Area& /* area */)
{
}

bool ReferenceBitmapField::onVerify(Canvas& canvas, const Area& area)
{
    bool verified = true;

    if (isVisible())
    {
        verified = false;
        StaticBitmap bitmap = m_db.getBitmap(m_bitmapId);
        verified = canvas.verify(bitmap, area);

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
    IDataHandler* pDataHandler = m_pContext->getDataHandler();
    ASSERT(pDataHandler);

    // TODO: move to some static variable
    const FUClassId internalFU = 255U;
    const DataId dataId = m_pDdh->GetErrorCounter();

    bool errorCounterIsCorrect = true;
    Number errorCounter;
    DataStatus status = pDataHandler->getNumber(internalFU, dataId, errorCounter);
    if (DataStatus::VALID != status)
    {
        setError(status.convertToLSRError());
        errorCounterIsCorrect = false;
    }

    if (DATATYPE_INTEGER != errorCounter.getType())
    {
        setError(LSR_DATASTATUS_INCONSISTENT);
        errorCounterIsCorrect = false;
    }

    if (errorCounterIsCorrect)
    {
        U32 counterValue = errorCounter.getU32();
        if (counterValue != U32_MAX)
        {
            errorCounter = Number(counterValue + 1U, DATATYPE_INTEGER);
        }

        bool result = pDataHandler->setData(internalFU, dataId, errorCounter, status);
        if (!result)
        {
            setError(LSR_DH_INVALID_DATA_ID);
        }
    }
}

void ReferenceBitmapField::resetErrorCounter()
{
    IDataHandler* pDataHandler = m_pContext->getDataHandler();
    ASSERT(pDataHandler);

    // TODO: move to some static variable
    const FUClassId internalFU = 255U;
    const DataId dataId = m_pDdh->GetErrorCounter();

    bool errorCounterIsCorrect = true;
    Number prevCounterValue;
    DataStatus status = pDataHandler->getNumber(internalFU, dataId, prevCounterValue);
    if (DataStatus::VALID != status)
    {
        setError(status.convertToLSRError());
        errorCounterIsCorrect = false;
    }

    if (DATATYPE_INTEGER != prevCounterValue.getType())
    {
        setError(LSR_DATASTATUS_INCONSISTENT);
        errorCounterIsCorrect = false;
    }

    if (errorCounterIsCorrect && prevCounterValue.getU32() > 0U)
    {
        const Number errorCounter = Number(0U, DATATYPE_INTEGER);
        bool result = pDataHandler->setData(internalFU, dataId, errorCounter, status);
        if (!result)
        {
            setError(LSR_DH_INVALID_DATA_ID);
        }
    }
}

} // namespace lsr
