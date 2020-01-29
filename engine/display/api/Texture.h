#ifndef LUXOFTSAFERENDERER_TEXTURE_H
#define LUXOFTSAFERENDERER_TEXTURE_H

/******************************************************************************
**
**   File:        Texture.h
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
#include "LsrTypes.h"
#include <DatabaseTypes.h>

namespace lsr
{

class Texture
{
public:
    Texture();

    bool isLoaded() const;

    /**
     * img contains an image in POI format (lsr image)
     */
    void load(const GILContext ctx, const LsrImage* const img);

    /**
     * Bind the texture to the context
     */
    void bind(const GILContext ctx);

    U16 getWidth() const;
    U16 getHeight() const;

private:
    /**
     * Converts the LsrImage format to the GILFormat
     */
    static GILFormat convertFormat(const LsrImage* const img);

    /**
     * Returns the size (in bytes) for a single color value in the palette
     */
    static U8 getPaletteColorSize(const LsrImage* const img);

    GILTexture m_texture;
    GILFormat m_format;
    U16 m_width;
    U16 m_height;
};

inline bool Texture::isLoaded() const
{
    return (m_texture != NULL);
}

inline U16 Texture::getWidth() const
{
    return m_width;
}

inline U16 Texture::getHeight() const
{
    return m_height;
}


}

#endif // LUXOFTSAFERENDERER_TEXTURE_H
