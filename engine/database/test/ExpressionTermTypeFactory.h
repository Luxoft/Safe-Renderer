#ifndef POPULUSSC_EXPRESSIONTERMTYPEFACTORY_H
#define POPULUSSC_EXPRESSIONTERMTYPEFACTORY_H

/******************************************************************************
**
**   File:        ExpressionTermTypeFactory.h
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

#include "DdhObject.h"

#include <ExpressionTermType.h>
#include <DynamicDataType.h>
#include <DynamicIndicationIdType.h>


namespace ddh
{
    struct ExpressionType;
    struct BitmapIdTableType;
}

class ExpressionTermTypeFactory: public DdhObject<psc::ExpressionTermType>
{
public:
    ExpressionTermTypeFactory();

    const psc::ExpressionTermType* getDdh() const;

    std::size_t getSize() const;

    void createBoolExprTerm(const bool value);

    void createDynamicDataExprTerm(const psc::DynamicDataType& value);

    void createIntegerExprTerm(const U32 value);

    void createIndicationExprTerm(const psc::DynamicIndicationIdType& value);

    void createWrongExprTerm(const U32 value);

    void createExpressionExprTerm(const psc::ExpressionType* expr,
                                  std::size_t exprSize);

    void createBitmapIdTableExprTerm(const psc::BitmapIdTableType* table,
                                     std::size_t exprSize);

protected:
    void setAttribute(U32 value);

    void setChoise(U16 value);
};

inline ExpressionTermTypeFactory::ExpressionTermTypeFactory()
{
    setAttribute(0U);
    setChoise(0U);
}

inline const psc::ExpressionTermType* ExpressionTermTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::ExpressionTermType*>(getData());
}

inline std::size_t ExpressionTermTypeFactory::getSize() const
{
    return getDataSize();
}

inline void ExpressionTermTypeFactory::createBoolExprTerm(const bool value)
{
    setAttribute(static_cast<U32>(value));
    setChoise(static_cast<U16>(psc::ExpressionTermType::BOOLEAN_CHOICE));
}

inline void ExpressionTermTypeFactory::createDynamicDataExprTerm(const psc::DynamicDataType& value)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(psc::ExpressionTermType::DYNAMICDATA_CHOICE));
    addData(reinterpret_cast<const U8*>(&value), sizeof(psc::DynamicDataType));
}

inline void ExpressionTermTypeFactory::createIntegerExprTerm(const U32 value)
{
    setAttribute(value);
    setChoise(static_cast<U16>(psc::ExpressionTermType::INTEGER_CHOICE));
}

inline void ExpressionTermTypeFactory::createIndicationExprTerm(const psc::DynamicIndicationIdType& value)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(psc::ExpressionTermType::INDICATION_CHOICE));
    addData(reinterpret_cast<const U8*>(&value), sizeof(psc::DynamicIndicationIdType));
}

inline void ExpressionTermTypeFactory::createWrongExprTerm(const U32 value)
{
    setAttribute(value);
    // Some wrong value
    setChoise(0xFFFF);
}

inline void ExpressionTermTypeFactory::createExpressionExprTerm(const psc::ExpressionType* expr,
                                                               std::size_t exprSize)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(psc::ExpressionTermType::EXPRESSION_CHOICE));

    addData(reinterpret_cast<const U8*>(expr), exprSize);
}

inline void ExpressionTermTypeFactory::createBitmapIdTableExprTerm(const psc::BitmapIdTableType* table,
                                                                  std::size_t exprSize)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(psc::ExpressionTermType::BITMAPIDTABLE_CHOICE));

    addData(reinterpret_cast<const U8*>(table), exprSize);
}

inline void ExpressionTermTypeFactory::setAttribute(U32 value)
{
    psc::ExpressionTermType& obj = getObj();
    obj.choiceAttribute = value;
}

inline void ExpressionTermTypeFactory::setChoise(U16 value)
{
    psc::ExpressionTermType& obj = getObj();
    obj.expressionTermTypeChoice = value;
}

#endif // POPULUSSC_EXPRESSIONTERMTYPEFACTORY_H
