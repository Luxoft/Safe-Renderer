#ifndef LUXOFTSAFERENDERER_BITMAP_ACCESS_H
#define LUXOFTSAFERENDERER_BITMAP_ACCESS_H

/******************************************************************************
**
**   File:        BitmapAccess.h
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
#include "FonBinReader.h"
#include "ddh_defs.h"
#include "LSRError.h"
#include "StaticBitmap.h"

namespace lsr
{

struct DDHType;
struct BitmapDefinitionType;
struct BitmapStateDefinitionType;

class BitmapAccess
{
public:
    BitmapAccess(const DDHType* ddh, const ResourceBuffer& imgbin);

    LSRError getError() const;

    StaticBitmap getBitmap(BitmapId bitmapId, U16 skin) const;

    ResourceBuffer getBitmapBuffer(const StaticBitmap& bitmap) const;

private:
    const BitmapDefinitionType* getBitmapDefinition(BitmapId bitmapId, U16 skin) const;
    const DDHType* m_ddh;
    FonBinReader m_fonbin;
    LSRError m_error;
};

} // namespace database

#endif // LUXOFTSAFERENDERER_BITMAP_ACCESS_H
