#ifndef _FIELDTYPE_H_
#define _FIELDTYPE_H_

/******************************************************************************
**
**   File:        FieldType.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
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
#include "LsrTypes.h"  // for P_STATIC_ASSERT


namespace lsr
{
struct StaticBitmapFieldType;
struct ReferenceBitmapFieldType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct FieldType
{
public:
    /** Choice constants enumeration */
    typedef enum FieldTypeChoice_Tag
    {
        STATICBITMAPFIELD_CHOICE = 2,
        REFERENCEBITMAPFIELD_CHOICE = 22
    } FieldTypeChoice;

public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the FieldType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 fieldTypeChoice :16;
    U16 fieldTypeChoice_RESERVED :16;  ///< Padding bytes for next 32bit address
    //----------------------------------------------------------------

public:
    /**
     * Returns the type of the choice on the FieldType as defined in the
     * FieldTypeChoice enum.
     */
    FieldType::FieldTypeChoice GetFieldTypeChoice() const;

    /**
     * Returns a pointer to the staticBitmapField choice option. Returns null if
     * this choice is not the selected option. Static Bitmap Field is used for
     * displaying static bitmaps where the specific bitmap is always the same.
     * Only the visibility of it will change
     */
    const StaticBitmapFieldType* GetStaticBitmapField() const;

    /**
     * Returns a pointer to the referenceBitmapField choice option. Returns null
     * if this choice is not the selected option. Reference Bitmap Field is
     * used for checking rendered output with a reference image
     */
    const ReferenceBitmapFieldType* GetReferenceBitmapField() const;
};

P_STATIC_ASSERT((sizeof(FieldType)) == 4, "FieldType size")


inline FieldType::FieldTypeChoice FieldType::GetFieldTypeChoice() const
{
    return static_cast<FieldType::FieldTypeChoice>(fieldTypeChoice);
}

inline const StaticBitmapFieldType* FieldType::GetStaticBitmapField() const
{
    const StaticBitmapFieldType* pResult = NULL;
    if (GetFieldTypeChoice() == STATICBITMAPFIELD_CHOICE)
    {
        // The instance starts immediately after the ROM image for the choice class so the offset is after the size of this object.
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const StaticBitmapFieldType*>(pThis + 4); // +2 choice, +2 padding
    }
    return pResult;
}

inline const ReferenceBitmapFieldType* FieldType::GetReferenceBitmapField() const
{
    const ReferenceBitmapFieldType* pResult = NULL;
    if (GetFieldTypeChoice() == REFERENCEBITMAPFIELD_CHOICE)
    {
        // The instance starts immediately after the ROM image for the choice class so the offset is after the size of this object.
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ReferenceBitmapFieldType*>(pThis + 4); // +2 choice, +2 padding
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _FIELDTYPE_H_
