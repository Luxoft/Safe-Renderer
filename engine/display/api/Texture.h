#ifndef POPULUSSC_TEXTURE_H
#define POPULUSSC_TEXTURE_H

/******************************************************************************
**
**   File:        Texture.h
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
#include "PscTypes.h"

namespace psc
{
class ResourceBuffer;

class Texture
{
public:
    Texture();

    bool isLoaded() const;

    /**
     * data contains an image in POI format (populus image)
     */
    void load(PGLContext ctx, const ResourceBuffer& data, const bool needsCopy);

    /**
     * Bind the texture to the context
     */
    void bind(PGLContext ctx);

    U16 getWidth() const;
    U16 getHeight() const;

private:
    PGLTexture m_texture;
    PGLFormat m_format;
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

#endif // POPULUSSC_TEXTURE_H
