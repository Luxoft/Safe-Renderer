#ifndef _EXPRESSIONTYPE_H_
#define _EXPRESSIONTYPE_H_

/******************************************************************************
**
**   File:        ExpressionType.h
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
struct ExpressionTermType;

#ifdef _USE_PACK_PRAGMA
#pragma pack(push)
#pragma pack(1)
#endif

struct ExpressionType
{
public:
    //----------------------------------------------------------------
    /**
     * This is the ROM structure for the ExpressionType.
     * Each element of this type has this exact image in ROM memory.
     */
    U16 _operator :16;
    U16 termCount :16;
    U16 termOffset :16;
    U8  PADDING1 :8;
    U8  PADDING2 :8;
    //----------------------------------------------------------------

public:

    /**
     * Returns the value of the operator attribute
     */
    ExpressionOperatorEnumeration GetOperator() const;

    /**
     * Returns the number of term child elements.
     */
    U16 GetTermCount() const;

    /**
     * Returns a pointer to the term child reference at index item.
     * This method checks the index and returns null if there are no
     * ExpressionTermType elements or the 'item' index exceeds the element
     * count.
     */
    const ExpressionTermType* GetTerm(const U16 item) const;
};

P_STATIC_ASSERT((sizeof(ExpressionType)) == 8, "ExpressionType size")


inline ExpressionOperatorEnumeration ExpressionType::GetOperator() const
{
    return static_cast<ExpressionOperatorEnumeration>(_operator);
}

inline U16 ExpressionType::GetTermCount() const
{
    return termCount;
}

inline const ExpressionTermType* ExpressionType::GetTerm(const U16 item) const
{
    const ExpressionTermType* pResult = NULL;
    if (item < GetTermCount())
    {
        const U8* pThis = reinterpret_cast<const U8*>(this);
        const U16* childRefROMPtr = reinterpret_cast<const U16*>(pThis + termOffset);
        pResult = reinterpret_cast<const ExpressionTermType*>(pThis + childRefROMPtr[item] * 4);
    }
    return pResult;
}

} // namespace lsr

#ifdef _USE_PACK_PRAGMA
#pragma pack(pop)
#endif

#endif  // #ifndef _EXPRESSIONTYPE_H_
