#ifndef LUXOFTSAFERENDERER_LSR_IMAGE_H
#define LUXOFTSAFERENDERER_LSR_IMAGE_H

/******************************************************************************
**
**   File:        LsrImage.h
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

#include "LsrTypes.h"
#include "ResourceBuffer.h"

namespace lsr
{

namespace LsrImageTypes
{
    struct ImgHeader;
    struct FrameHeader;
}

class LsrImage
{
    enum PixelSize
    {
        PIXEL_SIZE_1BYTE=1,
        PIXEL_SIZE_2BYTE=4,
        PIXEL_SIZE_3BYTE=16,
        PIXEL_SIZE_4BYTE=64
    };

public:
    enum PixelFormat
    {
        PIXEL_FORMAT_UNKNOWN = 0,
        PIXEL_FORMAT_RGB565 = PIXEL_SIZE_2BYTE,
        PIXEL_FORMAT_RGB888 = PIXEL_SIZE_3BYTE,
        PIXEL_FORMAT_BGR888 = PIXEL_SIZE_3BYTE + 1,
        PIXEL_FORMAT_RGBA8888 = PIXEL_SIZE_4BYTE,
        PIXEL_FORMAT_BGRA8888 = PIXEL_SIZE_4BYTE + 1
    };

    explicit LsrImage(const ResourceBuffer& buf);

    U32 getWidth() const;
    U32 getHeight() const;
    PixelFormat getPixelFormat() const;
    const void* getPixelData() const;

private:
    const LsrImageTypes::ImgHeader* m_image;
    const LsrImageTypes::FrameHeader* m_frame;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_LSR_IMAGE_H
