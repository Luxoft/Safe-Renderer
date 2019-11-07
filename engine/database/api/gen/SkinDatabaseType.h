#ifndef _LSR_SKINDATABASETYPE_H_
#define _LSR_SKINDATABASETYPE_H_

/******************************************************************************
**
**   File:        SkinDatabaseType.h
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
struct SkinType;

struct SkinDatabaseType
{
    const SkinType* const *skin;
    const U16 skinCount;


    /**
     * Returns the number of skin elements.
     */
    U16 GetSkinCount() const
    {
        return skinCount;
    }

    /**
     * Returns a pointer to the skin child reference at index i.
     * This method checks the index and returns NULL if the item index exceeds the element count.
     *
     */
    const SkinType* GetSkin(const U16 i) const
    {
        return (i < skinCount) ? skin[i] : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_SKINDATABASETYPE_H_
