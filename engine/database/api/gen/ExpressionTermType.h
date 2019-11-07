#ifndef _LSR_EXPRESSIONTERMTYPE_H_
#define _LSR_EXPRESSIONTERMTYPE_H_

/******************************************************************************
**
**   File:        ExpressionTermType.h
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
struct ExpressionType;
struct DynamicDataType;
struct BitmapIdTableType;

struct ExpressionTermType
{
    /** Choice constants enumeration */
    typedef enum ExpressionTermTypeChoice_Tag
    {
        NONE = 0,
        INTEGER_CHOICE,
        UINT_CHOICE,
        HEX_CHOICE,
        BOOLEAN_CHOICE,
        BITMAPID_CHOICE,
        EXPRESSION_CHOICE,
        DYNAMICDATA_CHOICE,
        BITMAPIDTABLE_CHOICE,
    } ExpressionTermTypeChoice;

    const ExpressionTermTypeChoice choiceTag;
    const U32 choiceAttribute;
    const void* const ptr;


    ExpressionTermTypeChoice GetExpressionTermTypeChoice() const
    {
        return choiceTag;
    }
    /**
     * Returns the value of the integer choice option.
     * Returns 0 if this choice is not the selected option
     */
    I32 GetInteger() const
    {
        return (choiceTag == INTEGER_CHOICE) ?
            static_cast<I32>(choiceAttribute) : 0;
    }
    /**
     * Returns the value of the uInt choice option.
     * Returns 0 if this choice is not the selected option
     */
    U32 GetUInt() const
    {
        return (choiceTag == UINT_CHOICE) ?
            static_cast<U32>(choiceAttribute) : 0U;
    }
    /**
     * Returns the value of the hex choice option.
     * Returns 0 if this choice is not the selected option
     */
    U32 GetHex() const
    {
        return (choiceTag == HEX_CHOICE) ?
            static_cast<U32>(choiceAttribute) : 0U;
    }
    /**
     * Returns the value of the boolean choice option.
     * Returns 0 if this choice is not the selected option
     */
    bool GetBoolean() const
    {
        return (choiceTag == BOOLEAN_CHOICE) ?
            (choiceAttribute != 0U) : false;
    }
    /**
     * Returns the value of the bitmapId choice option.
     * Returns 0 if this choice is not the selected option
     */
    U16 GetBitmapId() const
    {
        return (choiceTag == BITMAPID_CHOICE) ?
            static_cast<U16>(choiceAttribute) : 0U;
    }
    /**
     * Returns a pointer to the Expression choice option. Return NULL
     * if this choice is not the selected option.
     */
    const ExpressionType* GetExpression() const
    {
        return (choiceTag == EXPRESSION_CHOICE) ?
            static_cast<const ExpressionType*>(ptr) : NULL;
    }

    /**
     * Returns a pointer to the DynamicData choice option. Return NULL
     * if this choice is not the selected option.
     */
    const DynamicDataType* GetDynamicData() const
    {
        return (choiceTag == DYNAMICDATA_CHOICE) ?
            static_cast<const DynamicDataType*>(ptr) : NULL;
    }

    /**
     * Returns a pointer to the BitmapIdTable choice option. Return NULL
     * if this choice is not the selected option.
     */
    const BitmapIdTableType* GetBitmapIdTable() const
    {
        return (choiceTag == BITMAPIDTABLE_CHOICE) ?
            static_cast<const BitmapIdTableType*>(ptr) : NULL;
    }

};

} // namespace lsr

#endif // #ifndef _LSR_EXPRESSIONTERMTYPE_H_
