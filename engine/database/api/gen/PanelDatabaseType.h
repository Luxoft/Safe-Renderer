#ifndef _LSR_PANELDATABASETYPE_H_
#define _LSR_PANELDATABASETYPE_H_

/******************************************************************************
**
**   File:        PanelDatabaseType.h
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
struct PanelType;

struct PanelDatabaseType
{
    const PanelType* const *panel;
    const U16 panelCount;


    /**
     * Returns the number of panel elements.
     */
    U16 GetPanelCount() const
    {
        return panelCount;
    }

    /**
     * Returns a pointer to the panel child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const PanelType* GetPanel(const U16 i) const
    {
        return (i < panelCount) ? panel[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_PANELDATABASETYPE_H_
