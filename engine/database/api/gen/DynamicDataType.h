#ifndef _LSR_DYNAMICDATATYPE_H_
#define _LSR_DYNAMICDATATYPE_H_

/******************************************************************************
**
**   File:        DynamicDataType.h
**   Description:
**   Generator:   c78c5138ac2e7c6506a52bfc6fbc0ef05f7ad869
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

/**
 * DynamicDataType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct DynamicDataType
{
    const U32 m_fUDataId;
    const DynamicDataTypeEnumeration m_type;


    /**
     * Returns the value of the fUDataId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U32 GetFUDataId() const
    {
        return m_fUDataId;
    }

    /**
     * Returns the value of the type attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    DynamicDataTypeEnumeration GetType() const
    {
        return m_type;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DYNAMICDATATYPE_H_
