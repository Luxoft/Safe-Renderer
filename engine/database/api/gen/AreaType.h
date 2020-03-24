#ifndef _LSR_AREATYPE_H_
#define _LSR_AREATYPE_H_

/******************************************************************************
**
**   File:        AreaType.h
**   Description:
**   Generator:   7db08a476f8107a993e0bf7183b0cf60031dad3e
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
