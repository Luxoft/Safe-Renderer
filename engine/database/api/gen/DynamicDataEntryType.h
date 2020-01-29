#ifndef _LSR_DYNAMICDATAENTRYTYPE_H_
#define _LSR_DYNAMICDATAENTRYTYPE_H_

/******************************************************************************
**
**   File:        DynamicDataEntryType.h
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
 * DynamicDataEntryType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct DynamicDataEntryType
{
    const U16 m_dataId;
    const DynamicDataTypeEnumeration m_dataType;
    const I32 m_minimum;
    const I32 m_maximum;
    const U16 m_repeatTimeout;


    /**
     * Returns the value of the dataId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetDataId() const
    {
        return m_dataId;
    }

    /**
     * Returns the value of the dataType attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    DynamicDataTypeEnumeration GetDataType() const
    {
        return m_dataType;
    }

    /**
     * Returns the value of the minimum attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    I32 GetMinimum() const
    {
        return m_minimum;
    }

    /**
     * Returns the value of the maximum attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    I32 GetMaximum() const
    {
        return m_maximum;
    }

    /**
     * Returns the value of the repeatTimeout attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetRepeatTimeout() const
    {
        return m_repeatTimeout;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DYNAMICDATAENTRYTYPE_H_
