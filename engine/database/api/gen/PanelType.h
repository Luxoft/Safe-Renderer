#ifndef _LSR_PANELTYPE_H_
#define _LSR_PANELTYPE_H_

/******************************************************************************
**
**   File:        PanelType.h
**   Description:
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
struct AreaType;
struct ExpressionTermType;
struct BaseFieldChoiceType;

struct PanelType
{
    const AreaType* const area;
    const ExpressionTermType* const visible;
    const BaseFieldChoiceType* const *field;
    const U16 fieldCount;


    /**
     * Returns a pointer to the area child reference.
     * Defines the area of the element relative to the upper left corner of its parent
     */
    const AreaType* GetArea() const
    {
        return area;
    }

    /**
     * Returns a pointer to the visible child reference.
     * Controls the visibility of the element. It can make sense to have a field invisible if it is also enabled because when it receives focus, it becomes visible and when it loses focus, it becomes invisible again
     */
    const ExpressionTermType* GetVisible() const
    {
        return visible;
    }

    /**
     * Returns the number of field elements.
     */
    U16 GetFieldCount() const
    {
        return fieldCount;
    }

    /**
     * Returns a pointer to the field child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     * The list of fields in the panel. The fields are drawn in the order they appear in the list
     */
    const BaseFieldChoiceType* GetField(const U16 i) const
    {
        return (i < fieldCount) ? field[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_PANELTYPE_H_
