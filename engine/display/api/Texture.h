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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "gil.h"
#include "LsrTypes.h"
#include <DatabaseTypes.h>

namespace unittest
{
    class TextureTest;
}

namespace lsr
{

class Texture
{
    friend class unittest::TextureTest;
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
