#ifndef LUXOFTSAFERENDERER_STATIC_BITMAP_H
#define LUXOFTSAFERENDERER_STATIC_BITMAP_H

/******************************************************************************
**
**   File:        StaticBitmap.h
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

#include "ResourceBuffer.h"
#include "BitmapStateDefinitionType.h"

namespace lsr
{

class BitmapAccess;

/**
 * @brief Provides access to a static bitmap in the database
 */
class StaticBitmap
{
    friend class BitmapAccess;
public:
    StaticBitmap(const BitmapAccess& db, const BitmapStateDefinitionType* const bmp);

    const LsrImage* getData() const;
    U16 getId() const;

private:
    const BitmapAccess& m_db;
    const BitmapStateDefinitionType* m_bmp;
};

inline StaticBitmap::StaticBitmap(const BitmapAccess& db, const BitmapStateDefinitionType* const bmp)
: m_db(db)
, m_bmp(bmp)
{
}

inline U16 StaticBitmap::getId() const
{
    return (NULL != m_bmp) ? m_bmp->GetStateBitmapId() : 0U;
}

}

#endif //RESOURCE_STATIC_BITMAP_H
