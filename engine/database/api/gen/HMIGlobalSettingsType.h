#ifndef _LSR_HMIGLOBALSETTINGSTYPE_H_
#define _LSR_HMIGLOBALSETTINGSTYPE_H_

/******************************************************************************
**
**   File:        HMIGlobalSettingsType.h
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
 * HMIGlobalSettingsType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct HMIGlobalSettingsType
{
    const DisplaySizeType* const m_displaySize;


    /**
     * Returns a pointer to the displaySize child reference.
     * The size of the display in pixels
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const DisplaySizeType* GetDisplaySize() const
    {
        return m_displaySize;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_HMIGLOBALSETTINGSTYPE_H_
