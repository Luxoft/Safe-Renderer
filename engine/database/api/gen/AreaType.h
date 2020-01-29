#ifndef _LSR_AREATYPE_H_
#define _LSR_AREATYPE_H_

/******************************************************************************
**
**   File:        AreaType.h
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
 * AreaType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct AreaType
{
    const I16 m_xCoord;
    const I16 m_yCoord;
    const I16 m_width;
    const I16 m_height;


    /**
     * Returns the value of the xCoord attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    I16 GetXCoord() const
    {
        return m_xCoord;
    }

    /**
     * Returns the value of the yCoord attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    I16 GetYCoord() const
    {
        return m_yCoord;
    }

    /**
     * Returns the value of the width attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    I16 GetWidth() const
    {
        return m_width;
    }

    /**
     * Returns the value of the height attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    I16 GetHeight() const
    {
        return m_height;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_AREATYPE_H_
