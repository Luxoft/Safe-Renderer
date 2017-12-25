#ifndef _PANELTYPE_H_
#define _PANELTYPE_H_

/******************************************************************************
**
**   File:        PanelType.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Render is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Render.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "ddh_defs.h"
#include "PscTypes.h"  // for P_STATIC_ASSERT


namespace psc
{
struct AreaType;
struct ExpressionTermType;
struct FieldsType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct PanelType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the PanelType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 areaOffset :16;
    U16 visibleOffset :16;
    U16 fieldsOffset :16;
    //----------------------------------------------------------------

public:

    /**
     * Returns a pointer to the area child reference.
     * Defines the area of the element relative to the upper left corner of its
     * parent
     */
    const AreaType* GetArea() const;

    /**
     * Returns a pointer to the visible child reference.
     * Controls the visibility of the element. It can make sense to have a field
     * invisible if it is also enabled because when it receives focus, it
     * becomes visible and when it loses focus, it becomes invisible again
     */
    const ExpressionTermType* GetVisible() const;

    /**
     * Returns a pointer to the fields child reference.
     * The list of fields in the panel. The fields are drawn in the order they
     * appear in the list
     */
    const FieldsType* GetFields() const;
};

P_STATIC_ASSERT((sizeof(PanelType)) == 6, "PanelType size")


inline const AreaType* PanelType::GetArea() const
{
    const AreaType* pResult = NULL;
    if (areaOffset != 0)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const AreaType*>(pThis + areaOffset * 4);
    }
    return pResult;
}

inline const ExpressionTermType* PanelType::GetVisible() const
{
    const ExpressionTermType* pResult = NULL;
    if (visibleOffset != 0)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ExpressionTermType*>(pThis + visibleOffset * 4);
    }
    return pResult;
}

inline const FieldsType* PanelType::GetFields() const
{
    const FieldsType* pResult = NULL;
    if (fieldsOffset != 0)
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const FieldsType*>(pThis + fieldsOffset * 4);
    }
    return pResult;
}

} // namespace psc

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _PANELTYPE_H_
