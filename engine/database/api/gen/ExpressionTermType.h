#ifndef _EXPRESSIONTERMTYPE_H_
#define _EXPRESSIONTERMTYPE_H_

/******************************************************************************
**
**   File:        ExpressionTermType.h
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
struct ExpressionType;
struct DynamicDataType;
struct DynamicIndicationIdType;
struct BitmapIdTableType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct ExpressionTermType
{
public:
    /** Choice constants enumeration */
    typedef enum ExpressionTermTypeChoice_Tag
    {
        INTEGER_CHOICE = 1,
        BOOLEAN_CHOICE = 5,
        BITMAPID_CHOICE = 8,
        EXPRESSION_CHOICE = 12,
        DYNAMICDATA_CHOICE = 13,
        INDICATION_CHOICE = 15,
        BITMAPIDTABLE_CHOICE = 16
    } ExpressionTermTypeChoice;

public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the ExpressionTermType.
     * Each element of this type has this exact image in ROM memory.
     */
    U32 choiceAttribute :32;
    U16 expressionTermTypeChoice :16;
    U16 expressionTermTypeChoice_RESERVED :16;  ///< Padding bytes for next 32bit address
    //----------------------------------------------------------------

public:
    /**
     * Returns the type of the choice on the ExpressionTermType as defined in
     * the ExpressionTermTypeChoice enum.
     */
    ExpressionTermType::ExpressionTermTypeChoice GetExpressionTermTypeChoice() const;

    /**
     * Returns value to the integer choice option. Returns 0 if this choice is
     * not the selected option.
     */
    U32 GetInteger() const;

    /**
     * Returns value to the boolean choice option. Returns 0 if this choice is
     * not the selected option.
     */
    bool GetBoolean() const;

    /**
     * Returns value to the bitmapId choice option. Returns 0 if this choice is
     * not the selected option.
     */
    U16 GetBitmapId() const;

    /**
     * Returns a pointer to the expression choice option. Returns null if this
     * choice is not the selected option. Stores a complex expression with
     * operator and n parameters
     */
    const ExpressionType* GetExpression() const;

    /**
     * Returns a pointer to the dynamicData choice option. Returns null if this
     * choice is not the selected option. Refers to a simple dynamic data from
     * an FU interface
     */
    const DynamicDataType* GetDynamicData() const;

    /**
     * Returns a pointer to the indication choice option. Returns null if this
     * choice is not the selected option. Refers to an indication value from an
     * FU interface
     */
    const DynamicIndicationIdType* GetIndication() const;

    /**
     * Returns a pointer to the bitmapIdTable choice option. Returns null if
     * this choice is not the selected option. Stores a table of bitmap ids
     */
    const BitmapIdTableType* GetBitmapIdTable() const;
};

P_STATIC_ASSERT((sizeof(ExpressionTermType)) == 8, "ExpressionTermType size")


inline ExpressionTermType::ExpressionTermTypeChoice ExpressionTermType::GetExpressionTermTypeChoice() const
{
    return static_cast<ExpressionTermType::ExpressionTermTypeChoice>(expressionTermTypeChoice);
}

inline U32 ExpressionTermType::GetInteger() const
{
    U32 result = 0;
    if (GetExpressionTermTypeChoice() == INTEGER_CHOICE)
    {
        result = static_cast<U32>(choiceAttribute);
    }
    return result;
}

inline bool ExpressionTermType::GetBoolean() const
{
    bool result = false;
    if (GetExpressionTermTypeChoice() == BOOLEAN_CHOICE)
    {
        result = (choiceAttribute != 0U);
    }
    return result;
}

inline U16 ExpressionTermType::GetBitmapId() const
{
    U16 result = 0;
    if (GetExpressionTermTypeChoice() == BITMAPID_CHOICE)
    {
        result = static_cast<U16>(choiceAttribute);
    }
    return result;
}

inline const ExpressionType* ExpressionTermType::GetExpression() const
{
    const ExpressionType* pResult = NULL;
    if (GetExpressionTermTypeChoice() == EXPRESSION_CHOICE)
    {
        // The instance starts immediately after the ROM image for the choice class so the offset is after the size of this object.
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const ExpressionType*>(pThis + 8); // +4 attribute, +2 choice, +2 padding
    }
    return pResult;
}

inline const DynamicDataType* ExpressionTermType::GetDynamicData() const
{
    const DynamicDataType* pResult = NULL;
    if (GetExpressionTermTypeChoice() == DYNAMICDATA_CHOICE)
    {
        // The instance starts immediately after the ROM image for the choice class so the offset is after the size of this object.
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const DynamicDataType*>(pThis + 8); // +4 attribute, +2 choice, +2 padding
    }
    return pResult;
}

inline const DynamicIndicationIdType* ExpressionTermType::GetIndication() const
{
    const DynamicIndicationIdType* pResult = NULL;
    if (GetExpressionTermTypeChoice() == INDICATION_CHOICE)
    {
        // The instance starts immediately after the ROM image for the choice class so the offset is after the size of this object.
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const DynamicIndicationIdType*>(pThis + 8); // +4 attribute, +2 choice, +2 padding
    }
    return pResult;
}

inline const BitmapIdTableType* ExpressionTermType::GetBitmapIdTable() const
{
    const BitmapIdTableType* pResult = NULL;
    if (GetExpressionTermTypeChoice() == BITMAPIDTABLE_CHOICE)
    {
        // The instance starts immediately after the ROM image for the choice class so the offset is after the size of this object.
        const U8* pThis = reinterpret_cast<const U8*>(this);
        pResult = reinterpret_cast<const BitmapIdTableType*>(pThis + 8); // +4 attribute, +2 choice, +2 padding
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _EXPRESSIONTERMTYPE_H_
