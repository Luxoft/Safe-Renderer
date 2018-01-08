#ifndef POPULUSSC_EXPRESSIONTYPEFACTORY_H
#define POPULUSSC_EXPRESSIONTYPEFACTORY_H

/******************************************************************************
**
**   File:        ExpressionTypeFactory.h
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

#include "DdhArrayObject.h"

#include <ExpressionType.h>

#include <PscLimits.h>

namespace psc
{
    struct ExpressionTermType;
    struct DynamicDataType;
}

class ExpressionTypeFactory: public DdhArrayObject<psc::ExpressionType>
{
public:
    ExpressionTypeFactory();

    const psc::ExpressionType* getDdh() const;

    std::size_t getSize() const;

    void createExpr(psc::ExpressionOperatorEnumeration op, U16 termCount);

    void addExprTerm(const psc::ExpressionTermType* term, std::size_t termSize);

    void createInfiniteExpr(const psc::DynamicDataType& dataType);

protected:
    void setOperator(U16 op);

    void setTermCount(U16 value);

    void setTermOffset(U16 value);

private:
    void createExpr(ExpressionTypeFactory& factory,
                    psc::ExpressionOperatorEnumeration op,
                    U16 termCount);

    bool createLinkList(ExpressionTypeFactory& factory,
                        psc::ExpressionOperatorEnumeration op,
                        U16 termCount,
                        const psc::DynamicDataType& dataType,
                        U32 nestingLevel);

    void addExprTerm(ExpressionTypeFactory& factory,
                     const psc::ExpressionTermType* term,
                     std::size_t termSize);
};

inline ExpressionTypeFactory::ExpressionTypeFactory()
{
    setOperator(0U);
    setTermCount(0U);
    setTermOffset(0U);
}

inline const psc::ExpressionType* ExpressionTypeFactory::getDdh() const
{
    return reinterpret_cast<const psc::ExpressionType*>(getData());
}

inline std::size_t ExpressionTypeFactory::getSize() const
{
    return getDataSize();
}

inline void ExpressionTypeFactory::createExpr(psc::ExpressionOperatorEnumeration op, U16 termCount)
{
    createExpr(*this, op, termCount);
}

inline void ExpressionTypeFactory::createExpr(ExpressionTypeFactory& factory,
                                              psc::ExpressionOperatorEnumeration op,
                                              U16 termCount)
{
    factory.setOperator(static_cast<U16>(op));
    factory.setTermCount(termCount);

    U16 termOffset = factory.addArray(termCount);
    factory.setTermOffset(termOffset);
}

inline void ExpressionTypeFactory::createInfiniteExpr(const psc::DynamicDataType& dataType)
{
    U32 nestingLevel = MAX_EXPRESSION_NESTING + 2;

    createLinkList(*this,
                   psc::EXPRESSION_OPERATOR_EQUALS,
                   2U,
                   dataType,
                   nestingLevel);
}

inline bool ExpressionTypeFactory::createLinkList(ExpressionTypeFactory& factory,
                                                  psc::ExpressionOperatorEnumeration op,
                                                  U16 termCount,
                                                  const psc::DynamicDataType& dataType,
                                                  U32 nestingLevel)
{
    bool res = false;

    --nestingLevel;
    if (nestingLevel > 0U)
    {
        createExpr(factory, op, termCount);

        // create and add child
        ExpressionTypeFactory factoryChild;
        if (createLinkList(factoryChild, op, termCount, dataType, nestingLevel))
        {
            ExpressionTermTypeFactory factoryForFirstValue;
            factoryForFirstValue.createExpressionExprTerm(factoryChild.getDdh(), factoryChild.getSize());
            addExprTerm(factory, factoryForFirstValue.getDdh(), factoryForFirstValue.getSize());
        }
        else
        {
            ExpressionTermTypeFactory factoryForSecondValue;
            factoryForSecondValue.createDynamicDataExprTerm(dataType);
            addExprTerm(factory, factoryForSecondValue.getDdh(), factoryForSecondValue.getSize());
        }

        ExpressionTermTypeFactory factoryForSecondValue;
        factoryForSecondValue.createDynamicDataExprTerm(dataType);
        addExprTerm(factory, factoryForSecondValue.getDdh(), factoryForSecondValue.getSize());

        res = true;
    }

    return res;
}

inline void ExpressionTypeFactory::addExprTerm(const psc::ExpressionTermType* term,
                                               std::size_t termSize)
{
    addExprTerm(*this, term, termSize);
}

inline void ExpressionTypeFactory::addExprTerm(ExpressionTypeFactory& factory,
                                               const psc::ExpressionTermType* term,
                                               std::size_t termSize)
{
    factory.addDataToArray(reinterpret_cast<const U8*>(term), termSize);
}

inline void ExpressionTypeFactory::setOperator(U16 op)
{
    psc::ExpressionType& obj = getObj();
    obj._operator = op;
}

inline void ExpressionTypeFactory::setTermCount(U16 value)
{
    psc::ExpressionType& obj = getObj();
    obj.termCount = value;
}

inline void ExpressionTypeFactory::setTermOffset(U16 value)
{
    psc::ExpressionType& obj = getObj();
    obj.termOffset = value;
}

#endif // POPULUSSC_EXPRESSIONTYPEFACTORY_H
