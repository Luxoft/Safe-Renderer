#ifndef _LSR_DYNAMICDATAENTRYTYPE_H_
#define _LSR_DYNAMICDATAENTRYTYPE_H_

/******************************************************************************
**
**   File:        DynamicDataEntryType.h
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
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "ddh_defs.h"

namespace lsr
{

struct DynamicDataEntryType
{
    const U16 dataId;
    const DynamicDataTypeEnumeration dataType;
    const I32 minimum;
    const I32 maximum;
    const U16 repeatTimeout;


    /**
     * Returns the value of the dataId attribute
     */
    U16 GetDataId() const
    {
        return dataId;
    }

    /**
     * Returns the value of the dataType attribute
     */
    DynamicDataTypeEnumeration GetDataType() const
    {
        return dataType;
    }

    /**
     * Returns the value of the minimum attribute
     */
    I32 GetMinimum() const
    {
        return minimum;
    }

    /**
     * Returns the value of the maximum attribute
     */
    I32 GetMaximum() const
    {
        return maximum;
    }

    /**
     * Returns the value of the repeatTimeout attribute
     */
    U16 GetRepeatTimeout() const
    {
        return repeatTimeout;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DYNAMICDATAENTRYTYPE_H_
