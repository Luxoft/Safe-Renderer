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
     */
    GILError getError() const;

public: // but internal to the component
    GILContext getContext() const;

    /**
     * loads the static bitmap into a texture unless it's already loaded
     * loaded texture is returned
     */
    Texture* loadTexture(const StaticBitmap& bmp);

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
