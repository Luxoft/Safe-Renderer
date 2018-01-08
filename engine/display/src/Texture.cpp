/******************************************************************************
**
**   File:        Texture.cpp
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

#include "Texture.h"
#include "ResourceBuffer.h"
#include "Assertion.h"
#include "PopulusImage.h"

namespace psc
{

Texture::Texture()
: m_texture(NULL)
, m_format(PGL_FORMAT_ARGB_8888)
, m_width(0)
, m_height(0)
{
}

void Texture::load(PGLContext ctx, const ResourceBuffer& buf, const bool needsCopy)
{
    ASSERT(buf.getSize() > 0);

    PopulusImage img(buf);
    m_height = img.getHeight();
    m_width = img.getWidth();
    const void* pixelData = img.getPixelData();
    switch (img.getPixelFormat())
    {
    case PopulusImage::PIXEL_FORMAT_RGB565:
        m_format = PGL_FORMAT_RGB_565;
        break;
    case PopulusImage::PIXEL_FORMAT_RGB888:
        ASSERT_MSG(0, "pgl format not supported");
        break;
    case PopulusImage::PIXEL_FORMAT_BGR888:
        ASSERT_MSG(0, "pgl format not supported");
        break;
    case PopulusImage::PIXEL_FORMAT_RGBA8888:
        m_format = PGL_FORMAT_RGBA_8888;
        break;
    case PopulusImage::PIXEL_FORMAT_BGRA8888:
        m_format = PGL_FORMAT_BGRA_8888;
        break;
    default:
        ASSERT_MSG(0, "unknown pixel format");
        pixelData = NULL;
        break;
    }
    if (NULL != pixelData)
    {
        m_texture = pglCreateTexture(ctx);
        pglLoadTexture(m_texture, m_width, m_height, m_format, needsCopy, pixelData);
    }
}

void Texture::bind(PGLContext context)
{
    ASSERT(isLoaded());
    pglBindTexture(context, m_texture);
}

}
