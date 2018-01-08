#ifndef POPULUSSC_DISPLAYMANAGER_H
#define POPULUSSC_DISPLAYMANAGER_H

/******************************************************************************
**
**   File:        DisplayManager.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "pgl.h"
#include "TextureCache.h"

namespace psc
{
class StaticBitmap;

class DisplayManager
{
public:
    DisplayManager();

public: // but internal to the component
    PGLContext getContext() const;

    /**
     * loads the static bitmap into a texture unless it's already loaded
     * loaded texture is returned
     */
    Texture* loadTexture(const StaticBitmap& bmp);

private:
    TextureCache m_textureCache;
    PGLContext m_context;
};

inline PGLContext DisplayManager::getContext() const
{
    return m_context;
}

}

#endif // POPULUSSC_DISPLAYMANAGER_H
