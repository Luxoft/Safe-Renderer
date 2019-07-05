#ifndef LUXOFTSAFERENDERER_EXPRESSIONTERMTYPEFACTORY_H
#define LUXOFTSAFERENDERER_EXPRESSIONTERMTYPEFACTORY_H

/******************************************************************************
**
**   File:        ExpressionTermTypeFactory.h
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

class ExpressionTermTypeFactory: public DdhObject<lsr::ExpressionTermType>
{
public:
    ExpressionTermTypeFactory();

    const lsr::ExpressionTermType* getDdh() const;

    std::size_t getSize() const;

    void createBoolExprTerm(const bool value);

    void createDynamicDataExprTerm(const lsr::DynamicDataType& value);

    void createIntegerExprTerm(const U32 value);

    void createIndicationExprTerm(const lsr::DynamicIndicationIdType& value);

    void createWrongExprTerm(const U32 value);

    void createExpressionExprTerm(const lsr::ExpressionType* expr,
                                  std::size_t exprSize);

    void createBitmapIdTableExprTerm(const lsr::BitmapIdTableType* table,
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

inline const lsr::ExpressionTermType* ExpressionTermTypeFactory::getDdh() const
{
    return reinterpret_cast<const lsr::ExpressionTermType*>(getData());
}

inline std::size_t ExpressionTermTypeFactory::getSize() const
{
    return getDataSize();
}

inline void ExpressionTermTypeFactory::createBoolExprTerm(const bool value)
{
    setAttribute(static_cast<U32>(value));
    setChoise(static_cast<U16>(lsr::ExpressionTermType::BOOLEAN_CHOICE));
}

inline void ExpressionTermTypeFactory::createDynamicDataExprTerm(const lsr::DynamicDataType& value)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(lsr::ExpressionTermType::DYNAMICDATA_CHOICE));
    addData(reinterpret_cast<const U8*>(&value), sizeof(lsr::DynamicDataType));
}

inline void ExpressionTermTypeFactory::createIntegerExprTerm(const U32 value)
{
    setAttribute(value);
    setChoise(static_cast<U16>(lsr::ExpressionTermType::INTEGER_CHOICE));
}

inline void ExpressionTermTypeFactory::createIndicationExprTerm(const lsr::DynamicIndicationIdType& value)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(lsr::ExpressionTermType::INDICATION_CHOICE));
    addData(reinterpret_cast<const U8*>(&value), sizeof(lsr::DynamicIndicationIdType));
}

inline void ExpressionTermTypeFactory::createWrongExprTerm(const U32 value)
{
    setAttribute(value);
    // Some wrong value
    setChoise(0xFFFF);
}

inline void ExpressionTermTypeFactory::createExpressionExprTerm(const lsr::ExpressionType* expr,
                                                               std::size_t exprSize)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(lsr::ExpressionTermType::EXPRESSION_CHOICE));

    addData(reinterpret_cast<const U8*>(expr), exprSize);
}

inline void ExpressionTermTypeFactory::createBitmapIdTableExprTerm(const lsr::BitmapIdTableType* table,
                                                                  std::size_t exprSize)
{
    setAttribute(0U);
    setChoise(static_cast<U16>(lsr::ExpressionTermType::BITMAPIDTABLE_CHOICE));

    addData(reinterpret_cast<const U8*>(table), exprSize);
}

inline void ExpressionTermTypeFactory::setAttribute(U32 value)
{
    lsr::ExpressionTermType& obj = getObj();
    obj.choiceAttribute = value;
}

inline void ExpressionTermTypeFactory::setChoise(U16 value)
{
    lsr::ExpressionTermType& obj = getObj();
    obj.expressionTermTypeChoice = value;
}

#endif // LUXOFTSAFERENDERER_EXPRESSIONTERMTYPEFACTORY_H
