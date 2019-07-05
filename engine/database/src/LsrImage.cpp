/******************************************************************************
**
**   File:        LsrImage.cpp
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

#include "LsrImage.h"
#include "LsrImageTypes.h"
#include "Assertion.h"
#include "pil.h"
#include "LSRError.h"

namespace lsr
{

using namespace LsrImageTypes;
P_STATIC_ASSERT(sizeof(GUID) < sizeof(ImgHeader), "");

namespace
{
    const FrameHeader* verifyFrame(const FrameHeader* frame, const size_t size)
    {
        bool verified = true;
        switch (frame->pixelformat)
        {
        case LsrImage::PIXEL_FORMAT_RGB565:
        case LsrImage::PIXEL_FORMAT_RGB888:
        case LsrImage::PIXEL_FORMAT_BGR888:
        case LsrImage::PIXEL_FORMAT_RGBA8888:
        case LsrImage::PIXEL_FORMAT_BGRA8888:
            break;
        default:
            pilError(LSR_DB_ERROR, "LsrImage: unsupported pixel format");
            verified = false;
            break;
        }
        if (frame->atlasFrames)
        {
            pilError(LSR_DB_ERROR, "LsrImage: atlas frames are not supported");
            verified = false;
        }
        if (frame->encoding != ENCODING_RAW)
        {
            pilError(LSR_DB_ERROR, "LsrImage: raw encoding is required");
            verified = false;
        }
        if (frame->imageDataSize > size)
        {
            pilError(LSR_DB_ERROR, "LsrImage: size out of bounds");
            verified = false;
        }
        if (frame->paletteSize > 0)
        {
            pilError(LSR_DB_ERROR, "LsrImage: palette images are not supported");
            verified = false;
        }
        return verified ? frame : NULL;
    }
}

LsrImage::LsrImage(const ResourceBuffer& buf)
    : m_image(NULL)
    , m_frame(NULL)
{
    const void* data = buf.getData();
    const size_t minimumSize = sizeof(ImgHeader) + sizeof(FrameHeader);
    if ((NULL != data) && buf.getSize() >= minimumSize)
    {
        // detect image type by GUID in image header
        const GUID* guid = static_cast<const GUID*>(data);
        if (memcmp(guid, &simpleGuid, sizeof(GUID)) == 0)
        {
            m_image = static_cast<const ImgHeader*>(data);
            if (m_image->frames != 1U)
            {
                pilError(LSR_DB_ERROR, "LsrImage: multiframe images are not supported on this platform");
            }
            else
            {
                const void* frameData = static_cast<const U8*>(data) + sizeof(ImgHeader);
                m_frame = verifyFrame(static_cast<const FrameHeader*>(frameData), buf.getSize() - sizeof(ImgHeader));
                if (NULL == m_frame)
                {
                    m_image = NULL;
                }
            }
        }
        else if (memcmp(guid, &placeholderGuid, sizeof(GUID)) == 0)
        {
            pilError(LSR_DB_ERROR, "LsrImage: placeholder images are not supported on this platform");
        }
        else if (memcmp(guid, &atlasPlaceholderGuid, sizeof(GUID)) == 0)
        {
            pilError(LSR_DB_ERROR, "LsrImage: atlas images are not supported on this platform");
        }
        else
        {
            // not a populus image
        }
    }
    else
    {
        // not a populus image
    }
}

U32 LsrImage::getWidth() const
{
    return (NULL != m_image) ? m_image->width : 0U;
}

U32 LsrImage::getHeight() const
{
    return (NULL != m_image) ? m_image->height : 0U;
}

LsrImage::PixelFormat LsrImage::getPixelFormat() const
{
    return (NULL != m_frame) ? static_cast<PixelFormat>(m_frame->pixelformat) : PIXEL_FORMAT_UNKNOWN;
}

const void* LsrImage::getPixelData() const
{
    const void* buf = m_frame;
    if (NULL != buf)
    {
        buf = static_cast<const U8*>(buf)+sizeof(FrameHeader);
    }
    return buf;
}

}
