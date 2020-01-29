/******************************************************************************
**
**   File:        DatabaseMock.cpp
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
#include "DatabaseAccessor.h"

namespace lsr
{

Database::Database(const DDHType* ddh)
    : m_ddh(ddh)
    , m_bitmapAccess(m_ddh)
    , m_error(LSR_NO_ENGINE_ERROR)
{
}

StaticBitmap Database::getBitmap(BitmapId id) const
{
    DatabaseAccessor& accessor = DatabaseAccessor::instance();
    accessor.setRequestedBitmapId(id);

    return StaticBitmap(m_bitmapAccess, NULL);
}

} // namespace ddh
