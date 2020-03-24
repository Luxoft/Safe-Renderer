/******************************************************************************
**
**   File:        BitmapField.cpp
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

#include "BitmapField.h"

#include <Assertion.h>

#include <StaticBitmapFieldType.h>
#include <ExpressionTermType.h>
#include <Database.h>
#include <Canvas.h>

#include <new>

namespace lsr
{

BitmapField::BitmapField(const StaticBitmapFieldType* const pDdh)
    : Field()
    , m_pDdh(pDdh)
    , m_pDatabase(NULL)
    , m_bitmapId(0U)
{
    ASSERT(NULL != m_pDdh);
}

LSREngineError BitmapField::setup(const Database& db)
{
    m_pDatabase = &db;

    const bool inconsistent = ((!setArea(m_pDdh->GetArea())) || (!setVisible(m_pDdh->GetVisible())) || (!setupBitmapExpr()));
    return inconsistent ? LSR_DB_INCONSISTENT : LSR_NO_ENGINE_ERROR;
}

bool BitmapField::setupBitmapExpr()
{
    const ExpressionTermType* const pType = m_pDdh->GetBitmap();
    const bool typeIsBitmap = (NULL != pType);
    if (typeIsBitmap && (ExpressionTermType::BITMAPID_CHOICE == pType->GetExpressionTermTypeChoice()))
    {
        m_bitmapId = pType->GetBitmapId();
    }
    return typeIsBitmap;
}

void BitmapField::onDraw(Canvas& dst, const Area& rect) const
{
    const StaticBitmap bitmap = m_pDatabase->getBitmap(m_bitmapId);
    dst.drawBitmap(bitmap, rect);
}

bool BitmapField::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace lsr
