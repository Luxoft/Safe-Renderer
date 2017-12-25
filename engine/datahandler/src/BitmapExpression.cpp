/******************************************************************************
**
**   File:        BitmapExpression.cpp
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

#include <BitmapExpression.h>

namespace psc
{

BitmapExpression::BitmapExpression()
    : NumberExpression()
{
}

DataStatus BitmapExpression::getValue(BitmapId& value) const
{
    Number tmpValue;
    DataStatus status = NumberExpression::getValue(tmpValue);

    if (DataStatus::VALID == status)
    {
        value = static_cast<BitmapId>(tmpValue.getU32());
    }

    return status;
}

} // namespace datahandler
