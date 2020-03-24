#ifndef LUXOFTSAFERENDERER_DISPLAYMANAGER_H
#define LUXOFTSAFERENDERER_DISPLAYMANAGER_H

/******************************************************************************
**
**   File:        DisplayManager.h
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
#include "TextureCache.h"

namespace lsr
{

class DisplayManager
{
public:
    DisplayManager();

    /**
     * Returns the error code from the gil
     * @see gilGetError() in gil.h
     * @return GIL error code
     */
    GILError getError() const;

    /**
     * Returns the GIL context associated with this DisplayManager
     * @return GIL context
     */
    GILContext getContext() const;

    /**
     * Loads the static bitmap into a texture unless it's already loaded
     * @param bmp static bitmap
     * @return loaded GIL texture
     */
    Texture* loadTexture(const StaticBitmap& bmp);

    /**
     * Loads all static bitmaps which are defined in the HMI configuration
     * @param db database component which contains the HMI definition
     * @return true on success, false if at least on texture could not be loaded
     */
    bool loadAllTextures(const Database& db);

private:
    TextureCache m_textureCache;
    GILContext m_context;
};

inline GILContext DisplayManager::getContext() const
{
    return m_context;
}

}

#endif // LUXOFTSAFERENDERER_DISPLAYMANAGER_H
