/******************************************************************************
**
**   File:        ReferenceBitmapField.cpp
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

#include "ReferenceBitmapField.h"

#include <Assertion.h>

#include <ReferenceBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <Database.h>
#include <Canvas.h>

#include <new>

namespace lsr
{

ReferenceBitmapField::ReferenceBitmapField(const ReferenceBitmapFieldType* const pDdh)
    : Field()
    , m_pDdh(pDdh)
    , m_pDatabase(NULL)
    , m_bitmapId(0U)
    , m_verificationErrors(0U)
    , m_verified(false)
{
    ASSERT(NULL != m_pDdh);
}

LSREngineError ReferenceBitmapField::setup(const Database& db)
{
    m_pDatabase = &db;
    const bool inconsistent = ((!setArea(m_pDdh->GetArea())) || (!setVisible(m_pDdh->GetVisible())) || (!setupBitmapExpr()));
    return inconsistent ? LSR_DB_INCONSISTENT : LSR_NO_ENGINE_ERROR;
}

bool ReferenceBitmapField::setupBitmapExpr()
{
    const ExpressionTermType* const pType = m_pDdh->GetBitmap();
    m_bitmapId = (NULL != pType) ? pType->GetBitmapId() : 0U;
    return (m_bitmapId != 0U);
}

void ReferenceBitmapField::onDraw(Canvas& /* dst */, const Area& /* rect */) const
{
}

bool ReferenceBitmapField::onVerify(Canvas& dst, const Area& rect)
{
    // invisible bitmaps are always valid
    m_verified = !isVisible();

    if (m_verified)
    {
        clearVerificationErrors();
    }
    else
    {
        const StaticBitmap bitmap = m_pDatabase->getBitmap(m_bitmapId);
        m_verified = dst.verify(bitmap, rect);
        if (!m_verified)
        {
            if (m_verificationErrors < U32_MAX)
            {
                ++m_verificationErrors;
            }
        }
    }

    return m_verified;
}

void ReferenceBitmapField::clearVerificationErrors()
{
    m_verificationErrors = 0U;
}

} // namespace lsr
