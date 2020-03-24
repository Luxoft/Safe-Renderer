#ifndef LUXOFTSAFERENDERER_TEXTURE_CACHE_H
#define LUXOFTSAFERENDERER_TEXTURE_CACHE_H

/******************************************************************************
**
**   File:        TextureCache.h
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

#include "gil.h"
#include "Texture.h"
#include <LSRLimits.h>

namespace lsr
{

class TextureCache
{
public:
    explicit TextureCache(const DisplayManager&);

    /**
     * Loads a texture from the given StaticBitmap
     * If the StaticBitmap is already loaded as a texture the loaded texture is returned instead
     * returns NULL on error
     */
    Texture* load(const StaticBitmap& bmp);

private:
    const DisplayManager& m_displayManager;
    Texture m_textures[MAX_TEXTURES];
};

}

#endif // LUXOFTSAFERENDERER_TEXTURE_CACHE_H
