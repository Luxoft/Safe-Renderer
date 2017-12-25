/******************************************************************************
**
**   File:        TextureCache.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

namespace psc
{

TextureCache::TextureCache(const DisplayManager& dsp)
: m_displayManager(dsp)
{
}

Texture* TextureCache::load(const StaticBitmap& bmp)
{
    Texture* texture = NULL;
    const U16 id = bmp.getId();
    if (id > 0 && id <= MAX_TEXTURES)
    {
        texture = &m_textures[id - 1];
        if (!texture->isLoaded())
        {
            texture->load(m_displayManager.getContext(), bmp.getData(), false); // no copy for static bitmap
        }
    }
    return texture;
}

}
