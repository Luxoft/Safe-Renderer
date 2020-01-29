#ifndef _LSR_PANELDATABASETYPE_H_
#define _LSR_PANELDATABASETYPE_H_

/******************************************************************************
**
**   File:        PanelDatabaseType.h
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
 * PanelDatabaseType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct PanelDatabaseType
{
    const PanelType* const* const m_panel;
    const U16 m_panelCount;


    /**
     * Returns the number of panel elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetPanelCount() const
    {
        return m_panelCount;
    }

    /**
     * Returns a pointer to the panel child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const PanelType* GetPanel(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_panelCount) ? m_panel[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_PANELDATABASETYPE_H_
