/******************************************************************************
**
**   File:        TextureCache.cpp
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

#include "TextureCache.h"
#include "StaticBitmap.h"
#include "DisplayManager.h"
#include <algorithm>

namespace lsr
{

TextureCache::TextureCache(const DisplayManager& dsp)
: m_displayManager(dsp)
{
}

Texture* TextureCache::load(const StaticBitmap& bmp)
{
    Texture* pTexture = NULL;
    const U16 id = bmp.getId();
    if ((id > 0U) && (id <= MAX_TEXTURES))
    {
        static_cast<void>(pTexture);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        pTexture = &m_textures[id - 1U];
        if (!pTexture->isLoaded())
        {
            pTexture->load(m_displayManager.getContext(), bmp.getData());
        }
    }
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return pTexture;
}

} // namespace lsr
