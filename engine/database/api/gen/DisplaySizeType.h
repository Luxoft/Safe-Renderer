#ifndef _LSR_DISPLAYSIZETYPE_H_
#define _LSR_DISPLAYSIZETYPE_H_

/******************************************************************************
**
**   File:        DisplaySizeType.h
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
 * DisplaySizeType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct DisplaySizeType
{
    const U16 m_width;
    const U16 m_height;


    /**
     * Returns the value of the width attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetWidth() const
    {
        return m_width;
    }

    /**
     * Returns the value of the height attribute
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetHeight() const
    {
        return m_height;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_DISPLAYSIZETYPE_H_
