#ifndef _LSR_PANELTYPE_H_
#define _LSR_PANELTYPE_H_

/******************************************************************************
**
**   File:        PanelType.h
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
 * PanelType
 * @note member variables shall not be accessed by name - use the getter functions instead
 */
struct PanelType
{
    const AreaType* const m_area;
    const ExpressionTermType* const m_visible;
    const BaseFieldChoiceType* const* const m_field;
    const U16 m_fieldCount;


    /**
     * Returns a pointer to the area child reference.
     * Defines the area of the element relative to the upper left corner of its parent
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const AreaType* GetArea() const
    {
        return m_area;
    }

    /**
     * Returns a pointer to the visible child reference.
     * Controls the visibility of the element. It can make sense to have a field invisible if it is also enabled because when it receives focus, it becomes visible and when it loses focus, it becomes invisible again
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const ExpressionTermType* GetVisible() const
    {
        return m_visible;
    }

    /**
     * Returns the number of field elements.
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    U16 GetFieldCount() const
    {
        return m_fieldCount;
    }

    /**
     * Returns a pointer to the field child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     * The list of fields in the panel. The fields are drawn in the order they appear in the list
     */
    // coverity[misra_cpp_2008_rule_0_1_10_violation] Generic code
    const BaseFieldChoiceType* GetField(const U16 i) const
    {
        // coverity[misra_cpp_2008_rule_5_0_15_violation]
        return (i < m_fieldCount) ? m_field[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_PANELTYPE_H_
