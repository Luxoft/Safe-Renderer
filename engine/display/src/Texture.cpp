/******************************************************************************
**
**   File:        Texture.cpp
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

#include "Texture.h"
#include "ResourceBuffer.h"
#include "Assertion.h"
#include "LsrImage.h"

namespace lsr
{

Texture::Texture()
: m_texture(NULL)
, m_format(GIL_FORMAT_ARGB_8888)
, m_width(0U)
, m_height(0U)
{
}

void Texture::load(const GILContext ctx, const LsrImage* const img)
{
    ASSERT(img != NULL);
    m_height = static_cast<U16>(img->getHeight());
    m_width = static_cast<U16>(img->getWidth());
    const void* const pixelData = img->getPixelData();
    const GILFormat format = convertFormat(img);
    const U8 colorSize = getPaletteColorSize(img);
    if ((NULL != pixelData) && (format != GIL_FORMAT_INVALID))
    {
        m_format = format;
        m_texture = gilCreateTexture(ctx);
        static_cast<void>(gilTexPixels(m_texture, static_cast<uint32_t>(m_width), static_cast<uint32_t>(m_height), m_format, pixelData)); // ignore return value
        switch (colorSize)
        {
        case 4U:
            static_cast<void>(gilTexPalette4(m_texture, img->palette, img->header.clutSize)); // ignore return value
            break;
        case 3U:
            static_cast<void>(gilTexPalette3(m_texture, img->palette, img->header.clutSize)); // ignore return value
            break;
        case 2U:
            static_cast<void>(gilTexPalette2(m_texture, img->palette, img->header.clutSize)); // ignore return value
            break;
        default:
            break;
        }
    }
}

void Texture::bind(GILContext ctx)
{
    ASSERT(isLoaded());
    gilBindTexture(ctx, m_texture);
}

U8 Texture::getPaletteColorSize(const LsrImage* const img)
{
    U8 retval = 0U;
    if (0U != img->header.clutSize)
    {
        switch (img->getPixelFormat())
        {
        case LsrImageTypes::PIXEL_FORMAT_RGB565:
            retval = 2U;
            break;
        case LsrImageTypes::PIXEL_FORMAT_RGB888:
        case LsrImageTypes::PIXEL_FORMAT_BGR888:
            retval = 3U;
            break;
        case LsrImageTypes::PIXEL_FORMAT_RGBA8888:
        case LsrImageTypes::PIXEL_FORMAT_BGRA8888:
            retval = 4U;
            break;
        default:
            break;
        }
    }
    return retval;
}

GILFormat Texture::convertFormat(const LsrImage* const img)
{
    GILFormat format = GIL_FORMAT_INVALID;
    if (img->palette != NULL)
    {
        ASSERT(img->header.clutSize > 0);
        if (2U == img->header.bitDepth)
        {
            switch (img->getPixelFormat())
            {
            case LsrImageTypes::PIXEL_FORMAT_RGB565:
                format = GIL_FORMAT_P_2_RGB_565;
                break;
            case LsrImageTypes::PIXEL_FORMAT_RGB888:
                format = GIL_FORMAT_P_2_RGB_888;
                break;
            case LsrImageTypes::PIXEL_FORMAT_RGBA8888:
                format = GIL_FORMAT_P_2_RGBA_8888;
                break;
            case LsrImageTypes::PIXEL_FORMAT_BGRA8888:
                format = GIL_FORMAT_P_2_BGRA_8888;
                break;
            default:
                break;
            }
        }
    }
    else
    {
        switch (img->getPixelFormat())
        {
        case LsrImageTypes::PIXEL_FORMAT_RGB565:
            format = GIL_FORMAT_RGB_565;
            break;
        case LsrImageTypes::PIXEL_FORMAT_RGB888:
            format = GIL_FORMAT_RGB_888;
            break;
        case LsrImageTypes::PIXEL_FORMAT_BGR888:
            format = GIL_FORMAT_BGR_888;
            break;
        case LsrImageTypes::PIXEL_FORMAT_RGBA8888:
            format = GIL_FORMAT_RGBA_8888;
            break;
        case LsrImageTypes::PIXEL_FORMAT_BGRA8888:
            format = GIL_FORMAT_BGRA_8888;
            break;
        default:
            break;
        }
    }
    return format;
}

} // namespace lsr
