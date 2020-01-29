#ifndef _LSR_HMIGLOBALSETTINGSTYPE_H_
#define _LSR_HMIGLOBALSETTINGSTYPE_H_

/******************************************************************************
**
**   File:        HMIGlobalSettingsType.h
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
 * HMIGlobalSettingsType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct HMIGlobalSettingsType
{
    const DisplaySizeType* const m_displaySize;
    const ColorSetType* const m_colorSet;


    /**
     * Returns a pointer to the displaySize child reference.
     * The size of the display in pixels
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const DisplaySizeType* GetDisplaySize() const
    {
        return m_displaySize;
    }

    /**
     * Returns a pointer to the colorSet child reference.
     * Defines which colors shall be used for backgrounds, field types, specific fields, etc.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ColorSetType* GetColorSet() const
    {
        return m_colorSet;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_HMIGLOBALSETTINGSTYPE_H_
