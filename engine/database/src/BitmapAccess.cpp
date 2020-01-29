/******************************************************************************
**
**   File:        BitmapAccess.cpp
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

#include "BitmapAccess.h"
#include "DDHType.h"
#include "SkinDatabaseType.h"
#include "BitmapDefinitionType.h"
#include "SkinType.h"
#include "Assertion.h"

namespace lsr
{



BitmapAccess::BitmapAccess(const DDHType* const ddh)
: m_ddh(ddh)
, m_error(LSR_NO_ENGINE_ERROR)
{
    if (NULL == ddh)
    {
        m_error = LSR_DB_DDHBIN_EMPTY;
    }
}

StaticBitmap BitmapAccess::getBitmap(const BitmapId id, const U16 skin) const
{
    const BitmapStateDefinitionType* pState = NULL;
    if (id != 0U)
    {
        const BitmapDefinitionType* const pBitmapDef = getBitmapDefinition(id, skin);
        if (pBitmapDef != NULL)
        {
            static_cast<void>(pState);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            pState = pBitmapDef->GetDefault();
        }
    }
    return StaticBitmap(*this, pState);
}

const BitmapDefinitionType* BitmapAccess::getBitmapDefinition(const BitmapId id, const U16 skinIx) const
{
    /**
     * There are several ways to find the BitmapDefinitionType.
     * The skinBitmapTable ensures O(1) access
     * Alternatively the SkinType could be searched (binary search: O(log)) or guessed (O(1) for default skin)
     */
    const SkinDatabaseType* const skinDB = m_ddh->GetSkinDatabase();

    // Try with assigned/specified skin
    const SkinType* const pSkin = skinDB->GetSkin(skinIx);
    const BitmapDefinitionType* const result = (pSkin != NULL) ? pSkin->GetBitmap(id - 1U) : NULL;
    if (result != NULL)
    {
        ASSERT(result->GetBitmapId() == id);
    }
    return result;
}

const LsrImage* BitmapAccess::getBitmapBuffer(const StaticBitmap& bitmap) const
{
    const BitmapStateDefinitionType* const pStateBitmap = bitmap.m_bmp;
    return (pStateBitmap != NULL) ? pStateBitmap->GetFile() : NULL;
}

LSREngineError BitmapAccess::getError() const
{
    return m_error;
}

} // namespace lsr
