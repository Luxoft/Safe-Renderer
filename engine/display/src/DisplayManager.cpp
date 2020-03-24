/******************************************************************************
**
**   File:        DisplayManager.cpp
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

#include "DisplayManager.h"
#include "Database.h"
#include "DDHType.h"
#include "BitmapDatabaseType.h"
#include "BitmapType.h"
#include "SkinnedBitmapType.h"
#include <ReturnValue.h>

namespace lsr
{

DisplayManager::DisplayManager()
: m_textureCache(*this)
{
    m_context = gilCreateContext();
}

Texture* DisplayManager::loadTexture(const StaticBitmap& bmp)
{
    return m_textureCache.load(bmp);
}

GILError DisplayManager::getError() const
{
    return gilGetError(m_context);
}

bool DisplayManager::loadAllTextures(const Database& db)
{
    const DDHType* const pDdh = db.getDdh();
    const BitmapDatabaseType* const bitmapDB = pDdh->GetBitmapDatabase();
    ReturnValue<bool, true> ret;
    for (U16 i = 0U; i < bitmapDB->GetBitmapCount(); ++i)
    {
        const BitmapType* const pBmp = bitmapDB->GetBitmap(i);
        const SkinnedBitmapType* const pSkin = (pBmp != NULL) ? pBmp->GetSkinnedBitmap(0U) : NULL;
        const BitmapStateDefinitionType* const pState = (pSkin != NULL) ? pSkin->GetDefault() : NULL;
        const StaticBitmap bmp(pState);
        const Texture* const t = m_textureCache.load(bmp);
        if (t == NULL)
        {
            ret = false;
        }
    }
    return ret;
}

}
