/******************************************************************************
**
**   File:        Database.cpp
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

#include "Database.h"
#include "ResourceBuffer.h"
#include "DDHType.h"

namespace lsr
{
Database::Database(const ResourceBuffer& ddhbin, const ResourceBuffer& imgbin)
: m_ddh(static_cast<const DDHType*>(ddhbin.getData()))
, m_bitmapAccess(m_ddh, imgbin)
, m_error(LSR_NO_ERROR)
{
    if (m_ddh == NULL)
    {
        m_error = LSR_DB_DDHBIN_EMPTY;
    }
    else if(!m_ddh->IsVersionOK())
    {
        m_error = LSR_DB_DDHBIN_VERSION_MISMATCH;
    }
    else
    {
        m_error = m_bitmapAccess.getError();
    }
}

StaticBitmap Database::getBitmap(BitmapId id) const
{
    ASSERT(m_ddh != NULL);
    return m_bitmapAccess.getBitmap(id, 0U);
}

}
