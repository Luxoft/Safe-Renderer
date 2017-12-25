#ifndef POPULUSSC_FONBIN_READER_H
#define POPULUSSC_FONBIN_READER_H

/******************************************************************************
**
**   File:        FonBinReader.h
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

#include "PscTypes.h"
#include "ImageAttributes.h"
#include "ResourceBuffer.h"
#include "Assertion.h"

namespace psc
{

namespace impl
{
#pragma pack(push)
#pragma pack(1)

    struct ImageAttribute_t
    {
        U16 width;
        U16 height;
        U8 hasAlpha;
        U8 transparentPixelRatio;
        U16 reserved1;
    };
    P_STATIC_ASSERT(sizeof(ImageAttribute_t) == 8, "ImageAttribute_t size")

    struct FonBinHeader_t
    {
        U32 checkSum;
        U16 serializeVersion;
        U8 hasIntegratedImageData;
        U8 reserved1;
        U32 fontTableOffset;
        U32 sceneTableOffset;
        U32 skinBitmapTableOffset;
        U32 stateBitmapTableOffset;
        U32 imageDataTableOffset;
    };
    P_STATIC_ASSERT(sizeof(FonBinHeader_t) == 7*4, "FonBinHeader_t size")

    struct SkinBitmapTable_t
    {
        U32 size;
        U16 bitmapDefIx[1];
    };
    P_STATIC_ASSERT(sizeof(SkinBitmapTable_t) == 4 + sizeof(U16), "SkinBitmapTable_t size")

    struct StateBitmapTableEntry_t
    {
        U16 imageIx;
        U16 effectImageIx;
    };
    P_STATIC_ASSERT(sizeof(StateBitmapTableEntry_t) == 4, "StateBitmapTableEntry_t size")

    struct StateBitmapTable_t
    {
        U32 size;
        StateBitmapTableEntry_t data[1];
    };
    P_STATIC_ASSERT(sizeof(StateBitmapTable_t) == 4 + sizeof(StateBitmapTableEntry_t), "StateBitmapTable_t size")

    struct ImageDataTableEntry_t
    {
        ImageAttribute_t attribute;
        U32 imageOffset;
        U32 imageSize;
    };
    P_STATIC_ASSERT(sizeof(ImageDataTableEntry_t) == 16, "ImageDataTableEntry_t size")

    struct ImageDataTable_t
    {
        U32 size;
        U32 imageIxOffset;
        ImageDataTableEntry_t data[1];
    };
    P_STATIC_ASSERT(sizeof(ImageDataTable_t) == 8 + sizeof(ImageDataTableEntry_t), "ImageDataTable_t size")
#pragma pack(pop)
}


/**
 * Provides access to the Fonbin/Imgbin databases
 */
class FonBinReader
{
private:

public:
    /**
     * @brief Provides a mapping from (BitmapId + SkinId) to an index in DDH.SkinDatabase (BitmapDefinition)
     * (A bitmapId can be mapped to different resulting bitmaps by using different skins)
     */
    struct SkinBitmapTable
    {
        SkinBitmapTable(const FonBinReader& reader)
        : m_reader(reader)
        {}

        U32 GetSize() const
        {
            return (NULL != table()) ? table()->size : 0U;
        }

        /**
         * @brief GetSkinBitmapIndex
         * @param bitmapId bitmap id
         * @param skinIx skin id
         * @param bitmapCount total number of bitmaps
         * @return skinBitmapIndex for lookup in ddhbin
         */
        U16 GetSkinBitmapIndex(const U16 bitmapId, const U16 skinIx) const
        {
            const U32 tableSize = GetSize();
            const U32 bitmapCount = m_reader.m_numImageData;
            const U32 i = (bitmapId <= bitmapCount) ? ((skinIx * bitmapCount) + (static_cast<U32>(bitmapId) - 1U)) : 0xffffffffU;
            return (i < tableSize) ? table()->bitmapDefIx[i] : 0xffffU;
        }

    private:
        const impl::SkinBitmapTable_t* table() const
        {
            const void* p = m_reader.m_fonbin.getData();
            const impl::FonBinHeader_t* header = static_cast<const impl::FonBinHeader_t*>(p);
            return reinterpret_cast<const impl::SkinBitmapTable_t*>((header && header->skinBitmapTableOffset) ? (static_cast<const U8*>(p) + header->skinBitmapTableOffset) : NULL);
        }
        const FonBinReader& m_reader;
    };

    /**
     * @brief Provides a mapping from BitmapStateDefinition to an index in the ImageDataTable
     */
    struct StateBitmapTable
    {
        StateBitmapTable(const FonBinReader& reader)
        : m_reader(reader)
        {}

        /**
         * @brief Returns the number of available StateBitmaps
         * @return number of StateBitmaps
         */
        U32 GetSize() const
        {
            return (NULL != table()) ? table()->size : 0U;
        }

        /**
         * @brief Returns the image for the given table index
         * @param stateImageIx table index
         * @return imageIx for accessing ImageDataTable
         */
        U16 GetImageIndex(const U16 stateImageIx) const
        {
            ASSERT(stateImageIx < GetSize());
            return table()->data[stateImageIx].imageIx;
        }

        /**
         * @brief Returns the effect pattern image for the given table index
         * @param stateImageIx table index
         * @return imageIx for accessing ImageDataTable
         */
        U16 GetEffectImageIndex(U16 stateImageIx) const
        {
            ASSERT(stateImageIx < GetSize());
            return table()->data[stateImageIx].effectImageIx;
        }
    private:
        const impl::StateBitmapTable_t* table() const
        {
            const void* p = m_reader.m_fonbin.getData();
            const impl::FonBinHeader_t* header = reinterpret_cast<const impl::FonBinHeader_t*>(p);
            return reinterpret_cast<const impl::StateBitmapTable_t*>((header && header->stateBitmapTableOffset) ? (static_cast<const U8*>(p) + header->stateBitmapTableOffset) : NULL);
        }
        const FonBinReader& m_reader;
    };

    /**
     * @brief Provides access to the stored images in fonbin
     */
    struct ImageDataTable
    {
        ImageDataTable(const FonBinReader& reader)
        : m_reader(reader)
        {}

        U32 GetSize() const
        {
            return m_reader.m_numImageData;
        }

        /**
         * @brief Returns the image attributes for the given table index
         * @param imageIx table index
         * @return image attributes
         */
        ImageAttributes GetAttributes(U16 imageIx) const
        {
            ASSERT(imageIx < GetSize());
            ImageAttributes ret = ImageAttributes();
            {
                const U8* p = static_cast<const U8*>(m_reader.m_fonbin.getData());
                const impl::FonBinHeader_t* header = reinterpret_cast<const impl::FonBinHeader_t*>(p);
                if(header->imageDataTableOffset)
                {
                    const impl::ImageDataTable_t* table = reinterpret_cast<const impl::ImageDataTable_t*>(p + header->imageDataTableOffset);
                    if (imageIx >= table->imageIxOffset && imageIx < table->imageIxOffset + table->size)
                    {
                        const impl::ImageAttribute_t& attr = table->data[imageIx - table->imageIxOffset].attribute;
                        ret.width = attr.width;
                        ret.height = attr.height;
                        ret.hasAlpha = (attr.hasAlpha != 0);
                        ret.transparentPixelRatio = attr.transparentPixelRatio;
                    }
                }
            }
            return ret;
        }

        /**
         * @brief Reads an image from the fonbin
         * Returned buffer either points to a path in utf-8 format or to the image binary
         * This depends on the FonBinReader::HasEmbeddedImageData() flag
         * @param imageIx image table index
         * @param[out] size size of returned buffer
         * @return buffer containing the image or path - lifetime ends with ~FonBinReader()
         */
        const U8* ReadImage(const U32 imageIx, U32& size) const
        {
            ASSERT(imageIx < GetSize());
            const U8* pRet = NULL;
            size = 0U;
            {
                const U8* p = static_cast<const U8*>(m_reader.m_fonbin.getData());
                const impl::FonBinHeader_t* header = reinterpret_cast<const impl::FonBinHeader_t*>(p);
                if(header->imageDataTableOffset)
                {
                    const impl::ImageDataTable_t* table = reinterpret_cast<const impl::ImageDataTable_t*>(p + header->imageDataTableOffset);
                    if (imageIx >= table->imageIxOffset && imageIx < table->imageIxOffset + table->size)
                    {
                        const impl::ImageDataTableEntry_t& tEntry = table->data[imageIx - table->imageIxOffset];
                        const U32 imageOffset = tEntry.imageOffset;
                        if (0U != imageOffset)
                        {
                            size = tEntry.imageSize;
                            pRet = p + imageOffset;
                            ASSERT(imageOffset + size <= m_reader.m_fonbin.getSize());
                        }
                    }
                }
            }
            return pRet;
        }

    private:
        const FonBinReader& m_reader;
    };

public:
    FonBinReader();

    enum EFonBinReaderStatus
    {
        OK = 0,
        FILE_OPEN_ERROR = 1,
        FILE_READ_ERROR = 2,
        FILE_TOO_SMALL_TO_FIT_HEADER = 3,
        CHECKSUM_ERROR = 4,
        VERSION_ERROR = 5,
        MEMORY_ALLOC_ERROR = 6
    };

    /**
     * @brief Adds a fonbin database to the reader
     *
     * FonBinReader can read from several fonbin databases
     * Resources will be searched in registration order
     *
     * @param pDatabaseData buffer to the fonbin database
     * @param checksum checksum for checking integrity with ddhbin
     * @return error code
     */
    EFonBinReaderStatus setFonBin(const ResourceBuffer& db, const U32 checksum);

    /**
     * @brief Indicates if Font/Image tables contain binaries instead of path names
     * @return true if fonbin contains binaries, false otherwise
     */
    bool hasEmbeddedImageData() const
    {
        const impl::FonBinHeader_t* header = static_cast<const impl::FonBinHeader_t*>(m_fonbin.getData());
        return (header ? (header->hasIntegratedImageData != 0) : false);
    }

    /**
     * @brief Returns the skin mapping
     * @return SkinBitmapTable
     */
    SkinBitmapTable getSkinBitmapTable() const
    {
        return SkinBitmapTable(*this);
    }

    /**
     * @brief Returns the state bitmap mapping
     * @return StateBitmapTable
     */
    StateBitmapTable getStateBitmapTable() const
    {
        return StateBitmapTable(*this);
    }

    /**
     * @brief Returns the image table
     * @return ImageDataTable
     */
    ImageDataTable getImageDataTable() const
    {
        return ImageDataTable(*this);
    }

private:
    enum EFonBin
    {
        FONBIN_VERSION = 2,
    };

    static void readU16( U16& value, const U8* pData, U32& pos);
    static void readU32( U32& value, const U8* pData, U32& pos);

    /**
     * Returns the number of images the provided fonbin is aware of.
     * Not all images are necessarily contained in the fonbin, but each fonbin contains a consecutive chunk:
     * first contained image index is table->imageIxOffset
     * @param fonbin database to look in
     * @return number of images
     */
    static U32 getImageDataCount(const U8* const fonbin);

private:
    ResourceBuffer m_fonbin;
    U32 m_numImageData;
};

inline void FonBinReader::readU16( U16& value, const U8* pData, U32& pos)
{
    const U16* pVal = reinterpret_cast<const U16*>(pData + pos);
    value = *pVal;
    pos += sizeof(U16);
}

inline void FonBinReader::readU32( U32& value, const U8* pData, U32& pos)
{
    const U32* pVal = reinterpret_cast<const U32*>(pData + pos);
    value = *pVal;
    pos += sizeof(U32);
}

inline U32 FonBinReader::getImageDataCount(const U8* const fonbin)
{
    const impl::FonBinHeader_t* header = reinterpret_cast<const impl::FonBinHeader_t*>(fonbin);
    const impl::ImageDataTable_t* table = reinterpret_cast<const impl::ImageDataTable_t*>(header && header->imageDataTableOffset ? fonbin + header->imageDataTableOffset : NULL);
    return (NULL != table) ? (table->imageIxOffset + table->size) : 0U;
}

} // namespace psc

#endif // #ifndef POPULUSSC_FONBIN_READER_H
