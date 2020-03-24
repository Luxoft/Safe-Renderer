/******************************************************************************
**
**   File:        Database.cpp
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

#include "Database.h"
#include "ResourceBuffer.h"
#include "DDHType.h"
#include "Assertion.h"
#include "BitmapDatabaseType.h"
#include "BitmapType.h"
#include "SkinnedBitmapType.h"

namespace lsr
{
Database::Database(const DDHType* const ddh)
: m_ddh(ddh)
, m_error(LSR_NO_ENGINE_ERROR)
{
    if (m_ddh == NULL)
    {
        m_error = LSR_DB_DDHBIN_EMPTY;
    }
    else if(!m_ddh->IsVersionOK())
    {
        m_error = LSR_DB_DDHBIN_VERSION_MISMATCH;
    }
    else
    {
        // no error
    }
}

StaticBitmap Database::getBitmap(const BitmapId id) const
{
    const BitmapStateDefinitionType* pState = NULL;
    if (id != 0U)
    {
        const BitmapDatabaseType* const bitmapDB = m_ddh->GetBitmapDatabase();
        const BitmapType* const pBmp = bitmapDB->GetBitmap(id - 1U);
        const U16 skinIx = 0U;
        const SkinnedBitmapType* const pSkin = (pBmp != NULL) ? pBmp->GetSkinnedBitmap(skinIx) : NULL;
        static_cast<void>(pState);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        pState = (pSkin != NULL) ? pSkin->GetDefault() : NULL;
    }
    return StaticBitmap(pState);
}

} // namespace lsr
