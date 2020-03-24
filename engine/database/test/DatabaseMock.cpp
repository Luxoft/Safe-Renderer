/******************************************************************************
**
**   File:        DatabaseMock.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "Database.h"
#include "ResourceBuffer.h"
#include "DDHType.h"

namespace lsr
{

Database::Database(const DDHType* ddh)
    : m_ddh(ddh)
    , m_error(LSR_NO_ENGINE_ERROR)
{
}

StaticBitmap Database::getBitmap(BitmapId id) const
{
    return StaticBitmap(NULL);
}

} // namespace ddh
