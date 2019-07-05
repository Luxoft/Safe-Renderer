#ifndef LUXOFTSAFERENDERER_DATABASEACCESSOR_H
#define LUXOFTSAFERENDERER_DATABASEACCESSOR_H

/******************************************************************************
**
**   File:        DatabaseAccessor.h
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

#include <ddh_defs.h>

namespace lsr
{

class DatabaseAccessor
{
public:

    static DatabaseAccessor& instance()
    {
        static DatabaseAccessor obj;
        return obj;
    }

    void toDefault();

    void setRequestedBitmapId(BitmapId id);

    BitmapId getRequestedBitmapId() const;

    ~DatabaseAccessor();

private:
    DatabaseAccessor();

    BitmapId m_bitmapId;
};

inline DatabaseAccessor::DatabaseAccessor()
{
    toDefault();
}

inline DatabaseAccessor::~DatabaseAccessor()
{}

inline void DatabaseAccessor::toDefault()
{
    m_bitmapId = 0U;
}

inline void DatabaseAccessor::setRequestedBitmapId(BitmapId id)
{
    m_bitmapId = id;
}

inline BitmapId DatabaseAccessor::getRequestedBitmapId() const
{
    return m_bitmapId;
}

} // namespace ddh

#endif // LUXOFTSAFERENDERER_DATABASEACCESSOR_H
