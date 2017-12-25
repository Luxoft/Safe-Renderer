#ifndef POPULUSSC_DATABASE_H
#define POPULUSSC_DATABASE_H

/******************************************************************************
**
**   File:        Database.h
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

#include "BitmapAccess.h"
#include "ddh_defs.h"
#include "PSCError.h"
#include "StaticBitmap.h"

namespace psc
{
    class ResourceBuffer;
    struct DDHType;

    class Database
    {
    public:
        Database(const ResourceBuffer& ddhbin, const ResourceBuffer& imgbin);

        PSCError getError() const;

        const DDHType* getDdh() const;

        StaticBitmap getBitmap(BitmapId bitmapId) const;

        void setSkin(const U8 skinId);

    private:
        const DDHType* m_ddh;
        BitmapAccess m_bitmapAccess;
        PSCError m_error;
    };

    inline PSCError Database::getError() const
    {
        return m_error;
    }

    inline const DDHType* Database::getDdh() const
    {
        return m_ddh;
    }

} // namespace database

#endif // POPULUSSC_DATABASE_H
