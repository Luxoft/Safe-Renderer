#ifndef _LSR_COLORSETTYPE_H_
#define _LSR_COLORSETTYPE_H_

/******************************************************************************
**
**   File:        ColorSetType.h
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
 * ColorSetType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct ColorSetType
{
    const U16 m_defaultDisplayBackgroundColorId;
    const U16 m_defaultPageBackgroundColorId;
    const U16 m_defaultPanelBackgroundColorId;


    /**
     * Returns the value of the defaultDisplayBackgroundColorId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetDefaultDisplayBackgroundColorId() const
    {
        return m_defaultDisplayBackgroundColorId;
    }

    /**
     * Returns the value of the defaultPageBackgroundColorId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetDefaultPageBackgroundColorId() const
    {
        return m_defaultPageBackgroundColorId;
    }

    /**
     * Returns the value of the defaultPanelBackgroundColorId attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetDefaultPanelBackgroundColorId() const
    {
        return m_defaultPanelBackgroundColorId;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_COLORSETTYPE_H_
