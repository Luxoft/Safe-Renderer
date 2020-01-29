/******************************************************************************
**
**   File:        TextureCache.cpp
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
