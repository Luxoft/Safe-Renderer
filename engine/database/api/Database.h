#ifndef LUXOFTSAFERENDERER_DATABASE_H
#define LUXOFTSAFERENDERER_DATABASE_H

/******************************************************************************
**
**   File:        Database.h
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

#include "BitmapAccess.h"
#include "ddh_defs.h"
#include "LSREngineError.h"
#include "StaticBitmap.h"

namespace lsr
{
class ResourceBuffer;

class Database
{
public:
    Database(const DDHType* const ddh);

    LSREngineError getError() const;

    const DDHType* getDdh() const;

    StaticBitmap getBitmap(const BitmapId id) const;

private:
    const DDHType* m_ddh;
    BitmapAccess m_bitmapAccess;
    LSREngineError m_error;
};

inline LSREngineError Database::getError() const
{
    return m_error;
}

inline const DDHType* Database::getDdh() const
{
    return m_ddh;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DATABASE_H
