/******************************************************************************
**
**   File:        BitmapAccess.cpp
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

#include "BitmapAccess.h"
#include "DDHType.h"
#include "SkinDatabaseType.h"
#include "BitmapDefinitionType.h"
#include "BitmapStateDefinitionType.h"
#include "SkinType.h"

namespace psc
{

const U16 NO_IMAGE = 0xffff;

BitmapAccess::BitmapAccess(const DDHType* ddh, const ResourceBuffer& imgbin)
: m_ddh(ddh)
, m_fonbin()
, m_error(PSC_NO_ERROR)
{
    if (ddh)
    {
        FonBinReader::EFonBinReaderStatus status = m_fonbin.setFonBin(imgbin, ddh->GetImagesChecksum());
        if (status != FonBinReader::OK)
        {
            m_error = PSC_DB_IMGBIN_VERSION_MISMATCH;
        }
    }
    else
    {
        m_error = PSC_DB_IMGBIN_VERSION_MISMATCH;
    }
}

StaticBitmap BitmapAccess::getBitmap(BitmapId bitmapId, const U16 skin) const
{
    const BitmapStateDefinitionType* pState = NULL;
    if (bitmapId != 0)
    {
        const BitmapDefinitionType * pBitmapDef = getBitmapDefinition(bitmapId, skin);
        if (pBitmapDef != NULL)
        {
            pState = pBitmapDef->GetDefault();
        }
    }
    return StaticBitmap(*this, pState);
}

const BitmapDefinitionType *BitmapAccess::getBitmapDefinition(BitmapId bitmapId, const U16 skinIx) const
{
    /**
     * There are several ways to find the BitmapDefinitionType.
     * The skinBitmapTable ensures O(1) access
     * Alternatively the SkinType could be searched (binary search: O(log)) or guessed (O(1) for default skin)
     */
    const BitmapDefinitionType* result = NULL;
    const SkinDatabaseType* skinDB = m_ddh->GetSkinDatabase();
    const FonBinReader::SkinBitmapTable table = m_fonbin.getSkinBitmapTable();

    // Try with assigned/specified skin
    U16 skinBitmapIx = table.GetSkinBitmapIndex(bitmapId, skinIx);
    const SkinType* pSkin = skinDB->GetSkin(skinIx);
    if (NO_IMAGE == skinBitmapIx)
    {
        const U16 defaultSkinIx = 0U; // TODO: check if Editor can change this
        skinBitmapIx = table.GetSkinBitmapIndex(bitmapId, defaultSkinIx);
        pSkin = skinDB->GetSkin(defaultSkinIx);
    }
    if (NO_IMAGE != skinBitmapIx)
    {
        result = pSkin->GetBitmap(skinBitmapIx);
        ASSERT(result->GetBitmapId() == bitmapId);
    }
    return result;
}

ResourceBuffer BitmapAccess::getBitmapBuffer(const StaticBitmap& bmp) const
{
    ResourceBuffer image;
    const BitmapStateDefinitionType* pStateBitmap = bmp.m_bmp;
    if (pStateBitmap)
    {
        const FonBinReader::StateBitmapTable stateTable = m_fonbin.getStateBitmapTable();
        const FonBinReader::ImageDataTable imageDataTable = m_fonbin.getImageDataTable();
        const U16 stateBitmapIx = pStateBitmap->GetStateBitmapId() - 1;
        ASSERT(stateBitmapIx < stateTable.GetSize());
        const U16 bitmapIx = stateTable.GetImageIndex(stateBitmapIx);
        ASSERT(bitmapIx < imageDataTable.GetSize());
        U32 imageBufSize = 0U;
        const U8* imageBuf = imageDataTable.ReadImage(static_cast<U32>(bitmapIx), imageBufSize);
        image = ResourceBuffer(imageBuf, imageBufSize);
    }
    return image;
}

PSCError BitmapAccess::getError() const
{
    PSCError ret = m_error;
    // m_error = PSC_NO_ERROR; // TODO?
    return ret;
}

}
