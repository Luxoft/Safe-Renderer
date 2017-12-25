/******************************************************************************
**
**   File:        FonBinWriter.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include "FonBinReader.h"
#include <string>


namespace test
{

class FonBinWriter
{
    enum
    {
        FONBIN_VERSION = 2,
        OFFSET_IMG_DATA_TABLE = 256
    };

public:
    FonBinWriter(U8* buffer, U32 size)
        : buffer(buffer)
        , size(size)
        , header(reinterpret_cast<psc::impl::FonBinHeader_t*>(buffer))
        , binaryDataOffset(512)
        , imageDataTable(0)
        , imageDataIx(0)
        , fontIx(0)
        , sceneIx(0)
    {
        memset(buffer, 0, size);
        buffer[5] = FONBIN_VERSION;
    }

    void SetImageDataOffset(U32 offset)
    {
        ASSERT(imageDataTable != NULL);
        imageDataTable->imageIxOffset = offset;
    }

    U16 AddImage(const std::string& str, U16 width, U16 height)
    {
        if (0 == imageDataTable)
        {
            header->imageDataTableOffset = OFFSET_IMG_DATA_TABLE;
            imageDataTable = reinterpret_cast<psc::impl::ImageDataTable_t*>(buffer + header->imageDataTableOffset);
        }
        imageDataTable->data[imageDataIx].attribute.width = width;
        imageDataTable->data[imageDataIx].attribute.height = height;
        imageDataTable->data[imageDataIx].imageOffset = str.length() ? binaryDataOffset : 0;
        if (str.length() > 0)
        {
            imageDataTable->data[imageDataIx].imageSize = writeBinary(str.c_str(), str.length());
        }
        imageDataTable->size = ++imageDataIx;
        return imageDataIx;
    }

    void writeString(const std::string& str)
    {
        U16 len = static_cast<U16>(str.size());
        // write string length as U16
        memcpy(buffer + binaryDataOffset, &len, 2);
        binaryDataOffset += 2;
        // write string
        memcpy(buffer + binaryDataOffset, str.c_str(), str.length());
        binaryDataOffset += str.length();
    }

    U32 writeBinary(const void* src, U32 size)
    {
        memcpy(buffer + binaryDataOffset, src, size);
        binaryDataOffset += size;
        return size;
    }

    U8* buffer;
    U32 size;
    psc::impl::FonBinHeader_t* header;
    U32 binaryDataOffset;
    psc::impl::ImageDataTable_t* imageDataTable;
    U16 imageDataIx;
    U16 fontIx;
    U16 sceneIx;
};

} // namespace database

