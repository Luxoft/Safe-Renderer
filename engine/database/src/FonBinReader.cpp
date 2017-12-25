/******************************************************************************
**
**   File:        FonBinReader.cpp
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
#include <algorithm>


namespace psc
{

FonBinReader::FonBinReader()
    : m_fonbin()
    , m_numImageData(0U)
{
}

FonBinReader::EFonBinReaderStatus FonBinReader::setFonBin(const ResourceBuffer& db, const U32 checksum)
{
    EFonBinReaderStatus result = OK;
    const U8* const pBuffer = static_cast<const U8*>(db.getData());

    if (NULL == pBuffer)
    {
        result = FILE_OPEN_ERROR;
    }
    else if (db.getSize() < sizeof(impl::FonBinHeader_t))
    {
        result = FILE_TOO_SMALL_TO_FIT_HEADER;
    }
    else
    {
        U32 i = 0U;
        U32 calcChecksum = 0U;
        calcChecksum += static_cast<U32>(pBuffer[i++]) << 24U;
        calcChecksum += static_cast<U32>(pBuffer[i++]) << 16U;
        calcChecksum += static_cast<U32>(pBuffer[i++]) << 8U;
        calcChecksum += pBuffer[i++];

        U16 version = 0U;
        version += static_cast<U32>(pBuffer[i++]) << 8U;
        version += pBuffer[i++];

        if (calcChecksum != checksum)
        {
            result = CHECKSUM_ERROR;
        }
        else if (version != FONBIN_VERSION)
        {
            result = VERSION_ERROR;
        }
        else
        {
            m_fonbin = db;
            const U8* const fonbin = static_cast<const U8*>(db.getData());
            m_numImageData = getImageDataCount(fonbin);
        }
    }

    return result;
}

} // namespace psc
