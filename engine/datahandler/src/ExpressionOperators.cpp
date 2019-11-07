/******************************************************************************
**
**   File:        ExpressionOperators.cpp
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

#include "ExpressionOperators.h"

#include <Assertion.h>

#include <Expression.h>

#include <algorithm>

namespace lsr
{
namespace expressionoperators
{

/**
 * Coverity has an error in this file several times.
 * Error is about infinite recursion.
 * This should be checked by Editor, that's why we can
 * suppress it using "coverity[stack_use_unknown]".
 */

namespace
{

/**
 * NumberList is the auxiliary class for storing
 * an array of @c Number objects and its size.
 */
template <std::size_t ListSize>
class NumberList: private std::pair<std::size_t, lsr::Number[ListSize]>
{
public:
    inline NumberList()
    : std::pair<std::size_t, lsr::Number[ListSize]>()
    {}

    inline void addItem(const lsr::Number item)
    {
        if (this->first < ListSize)
        {
            this->second[this->first] = item;
            ++this->first;
        }
    }

    inline std::size_t itemsCount() const
    {
        return this->first;
    }

    inline bool empty() const
    {
        return this->first == 0U;
    }

    inline lsr::Number item(const std::size_t itemIndex) const
    {
        lsr::Number res;
        if ((this->first > 0U) && (itemIndex < this->first))
        {
            res = this->second[itemIndex];
        }
        return res;
    }
};

/**
 * Method gets 2 ExpressionTermType objects from @c pExpression
 *
 * Method requires that @c pExpression has exactly 2 ExpressionTermType objects, where
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be handled.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value1      value of the first object
 * @param[out] value2      value of the second object
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus getTerms(const ExpressionType* const pExpression,
                    DataContext* const pContext,
                    Number& value1,
                    Number& value2)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(pExpression->GetTermCount() == 2U);

    Number term0;
    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   value1);

    if (DataStatus::VALID == status)
    {
        Number term1;
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(1U),
                                       pContext,
                                       value2);
    }

    return status;
}

/**
 * Method evaluates all child @c ExpressionTermType objects of
 * @c pExpression and place the result to the appropriate list
 * (according to its data status).
 * All objects should return values with the same type.
 *
 * @tparam ExpressionsCount child expressions count in the @c pExpression.
 *
 * @param[in]  pExpression      pointer to @c ExpressionType object.
 *                              It is the owner of objects, that need to be handled.
 * @param[in]  pContext         data context, which shall be used for evaluation.
 * @param[out] validList        list with @c DataStatus::VALID status
 * @param[out] invalidList      list with @c DataStatus::INVALID and
 *                              @c DataStatus::NOT_AVAILABLE status
 * @param[out] inconsistentList list with @c DataStatus::INCONSISTENT status
 */
template <std::size_t ExpressionsCount>
void sortExpressionsResults(const ExpressionType* const pExpression,
                            DataContext* const pContext,
                            NumberList<ExpressionsCount>& validList,
                            NumberList<ExpressionsCount>& invalidList,
                            NumberList<ExpressionsCount>& inconsistentList)
{
    ASSERT(pExpression->GetTermCount() == ExpressionsCount);

    DynamicDataTypeEnumeration type = DATATYPE_ENUM_SIZE;
    const U16 termCount = static_cast<U16>(ExpressionsCount);
    for (U16 i = 0U; i < termCount; ++i)
    {
        DataStatus status = DataStatus::INCONSISTENT;

        Number value;
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(i),
                                       pContext,
                                       value);

        if (type == DATATYPE_ENUM_SIZE)
        {
            type = value.getType();
        }

        ASSERT(type == value.getType());

        switch (status.getValue())
        {
        case DataStatus::VALID:
        {
            validList.addItem(value);
            break;
        }
        case DataStatus::NOT_AVAILABLE:
        case DataStatus::INVALID:
        {
            invalidList.addItem(value);
            break;
        }
        default:
        {
            inconsistentList.addItem(value);
            break;
        }
        }
    }
}

/**
 * Method calculates the Majority element with the count of repeating in the list.
 *
 * TODO: refactor the algorithm to be O(n).
 *
 * @tparam ListSize size of the array
 *
 * @param[in]  list an array with data
 * @param[out] repeated number of repetitions. It will lie in the [1, ListSize].
 *
 * @return index of the majority element in the @c list.
 */
template <std::size_t ListSize>
std::size_t getMajorValue(const NumberList<ListSize>& list, std::size_t& repeated)
{
    repeated = 0U;
    std::size_t resIndex = 0U;
    for (std::size_t i = 0U; i < list.itemsCount(); ++i)
    {
        std::size_t count = 1U;
        for (std::size_t j = i + 1U; j <  list.itemsCount(); ++j)
        {
            if (list.item(i) == list.item(j))
            {
                ++count;
            }
        }
        if (repeated < count)
        {
            repeated = count;
            resIndex = i;
        }
    }

    return resIndex;
}

/**
 * Method searches the value connected to the key @c key in the @c pTable.
 *
 * @param[in]  pTable pointer to @c BitmapIdTableType object with a list of key-value pairs.
 *                    In this table the search will be executed.
 * @param[in]  key    the key corresponding to the value that shall be searched for in the table.
 * @param[out] status status of @c value, see @c DataStatus.
 *
 * @return value from the pair key-value, where key is equal to @c key.
 */
BitmapId searchInTable(const BitmapIdTableType* const pTable, const Number& key, DataStatus& status)
{
    BitmapId ret = 0U;
    status = DataStatus::INVALID;
    ASSERT(NULL != pTable);

    // TODO: check if binary search is possible
    for (U16 i = 0U; i < pTable->GetItemCount(); ++i)
    {
        const EnumerationBitmapMapType* const pItem = pTable->GetItem(i);
        ASSERT(NULL != pItem);

        if (pItem->GetKey() == key.getU32())
        {
            ret = pItem->GetBitmapId();
            status = DataStatus::VALID;
            break;
        }
    }

    return ret;
}

} // anonymous namespace

DataStatus minMax(const ExpressionType* const pExpression,
                  DataContext* const pContext,
                  Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(pExpression->GetTermCount() == 3U);

    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   value);

    if (DataStatus::VALID == status)
    {
        Number minValue;
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(1U),
                                       pContext,
                                       minValue);

        if (DataStatus::VALID == status)
        {
            ASSERT(value.getType() == minValue.getType());

            Number maxValue;
            // coverity[stack_use_unknown]
            status = Expression::getNumber(pExpression->GetTerm(2U),
                                           pContext,
                                           maxValue);

            if (DataStatus::VALID == status)
            {
                ASSERT(value.getType() == maxValue.getType());

                value = std::max(value, minValue);
                value = std::min(value, maxValue);
            }
        }
    }

    return status;
}

DataStatus equals(const ExpressionType* const pExpression,
                  DataContext* const pContext,
                  Number& value)
{
    Number term0;
    Number term1;
    const DataStatus status = getTerms(pExpression,
                                       pContext,
                                       term0,
                                       term1);

    if (DataStatus::VALID == status)
    {
        value = Number(term0 == term1);
    }

    return status;
}

DataStatus notEquals(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value)
{
    const DataStatus status = equals(pExpression, pContext, value);

    value = Number(!value.getBool());

    return status;
}

DataStatus lessThan(const ExpressionType* const pExpression,
                    DataContext* const pContext,
                    Number& value)
{
    Number term0;
    Number term1;
    const DataStatus status = getTerms(pExpression,
                                       pContext,
                                       term0,
                                       term1);

    if (DataStatus::VALID == status)
    {
        value = Number(term0 < term1);
    }

    return status;
}

DataStatus lessThanOrEquals(const ExpressionType* const pExpression,
                            DataContext* const pContext,
                            Number& value)
{
    const DataStatus status = greaterThan(pExpression, pContext, value);

    value = Number(!value.getBool());

    return status;
}

DataStatus greaterThan(const ExpressionType* const pExpression,
                       DataContext* const pContext,
                       Number& value)
{
    Number term0;
    Number term1;
    const DataStatus status = getTerms(pExpression,
                                       pContext,
                                       term0,
                                       term1);

    if (DataStatus::VALID == status)
    {
        value = Number(term1 < term0);
    }

    return status;
}

DataStatus greaterThanOrEquals(const ExpressionType* const pExpression,
                               DataContext* const pContext,
                               Number& value)
{
    const DataStatus status = lessThan(pExpression, pContext, value);

    value = Number(!value.getBool());

    return status;
}

DataStatus itemAt(const ExpressionType* const pExpression,
                        DataContext* const pContext,
                        Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(NULL != pExpression);

    Number valueToSearch;
    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   valueToSearch);
    if (DataStatus::VALID == status)
    {
        const ExpressionTermType* const exprWithTable = pExpression->GetTerm(1U);
        ASSERT(NULL != exprWithTable);

        const BitmapId id = searchInTable(exprWithTable->GetBitmapIdTable(),
                                          valueToSearch,
                                          status);
        switch (status.getValue())
        {
        case DataStatus::VALID:
        {
            value = Number(static_cast<U32>(id), DATATYPE_INTEGER);
            break;
        }
        case DataStatus::INVALID:
        {
            if (pExpression->GetTermCount() > 2U)
            {
                Number defaultValue;
                // coverity[stack_use_unknown]
                status = Expression::getNumber(pExpression->GetTerm(2U),
                                               pContext,
                                               defaultValue);
                if (DataStatus::VALID == status)
                {
                    value = defaultValue;
                }
            }
            break;
        }
        default:
        {
            status = DataStatus::INCONSISTENT;
            break;
        }
        }
    }
    return status;
}

DataStatus booleanAnd(const ExpressionType* const pExpression,
                      DataContext* const pContext,
                      Number& value)
{
    Number term0;
    Number term1;
    DataStatus status = getTerms(pExpression,
                                 pContext,
                                 term0,
                                 term1);

    if (DataStatus::VALID == status)
    {
        if ((term0.getType() == DATATYPE_BOOLEAN) &&
            (term1.getType() == DATATYPE_BOOLEAN))
        {
            value = Number(term0.getBool() && term1.getBool());
        }
        else
        {
            status = DataStatus::INCONSISTENT;
        }
    }

    return status;
}

DataStatus booleanOr(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value)
{
    Number term0;
    Number term1;
    DataStatus status = getTerms(pExpression,
                                 pContext,
                                 term0,
                                 term1);

    if (DataStatus::VALID == status)
    {
        if ((term0.getType() == DATATYPE_BOOLEAN) &&
            (term1.getType() == DATATYPE_BOOLEAN))
        {
            // We have branch coverage gap here because of:
            // according to ISO/IEC 14882:2003,
            // section 5.15 Unlike |, || guarantees left-to-right evaluation;
            // moreover, the second operand is not evaluated
            // if the first operand evaluates to true.
            value = Number(term0.getBool() || term1.getBool());
        }
        else
        {
            status = DataStatus::INCONSISTENT;
        }
    }

    return status;
}

DataStatus booleanNot(const ExpressionType* const pExpression,
                      DataContext* const pContext,
                      Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(pExpression->GetTermCount() == 1U);

    Number term;
    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   term);

    if (DataStatus::VALID == status)
    {
        if (term.getType() == DATATYPE_BOOLEAN)
        {
            value = Number(!term.getBool());
        }
        else
        {
            status = DataStatus::INCONSISTENT;
        }
    }

    return status;
}

DataStatus fallback(const ExpressionType* const pExpression,
                    DataContext* const pContext,
                    Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(pExpression->GetTermCount() == 2U);

    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   value);

    if (DataStatus::VALID != status)
    {
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(1U),
                                       pContext,
                                       value);
    }

    return status;
}

DataStatus fallback2(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(pExpression->GetTermCount() == 3U);

    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   value);

    if (DataStatus::INVALID == status)
    {
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(1U),
                                       pContext,
                                       value);
    }
    else if (DataStatus::VALID != status)
    {
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(2U),
                                       pContext,
                                       value);
    }
    else
    {
        // ignore other data status
    }

    return status;
}

DataStatus fallback3(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    ASSERT(pExpression->GetTermCount() == 4U);

    // coverity[stack_use_unknown]
    status = Expression::getNumber(pExpression->GetTerm(0U),
                                   pContext,
                                   value);

    if (DataStatus::INVALID == status)
    {
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(1U),
                                       pContext,
                                       value);
    }
    else if (DataStatus::NOT_AVAILABLE == status)
    {
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(2U),
                                       pContext,
                                       value);
    }
    else if (DataStatus::VALID != status)
    {
        // coverity[stack_use_unknown]
        status = Expression::getNumber(pExpression->GetTerm(3U),
                                       pContext,
                                       value);
    }
    else
    {
        // ignore other data status
    }

    return status;
}

DataStatus redundancy(const ExpressionType* const pExpression,
                      DataContext* const pContext,
                      Number& value)
{
    DataStatus status = DataStatus::INCONSISTENT;

    const std::size_t expressionsCount = 3U;

    ASSERT(pExpression->GetTermCount() == expressionsCount);

    NumberList<expressionsCount> validList;
    NumberList<expressionsCount> invalidList;
    NumberList<expressionsCount> inconsistentList;

    sortExpressionsResults(pExpression, pContext, validList, invalidList, inconsistentList);

    if (inconsistentList.empty())
    {
        if (invalidList.itemsCount() >= validList.itemsCount())
        {
            std::size_t repeated = 0U;
            const std::size_t idx = getMajorValue(invalidList, repeated);
            value = (1U < repeated) ? invalidList.item(idx) : invalidList.item(0U);
            status = DataStatus::INVALID;
        }
        else
        {
            std::size_t repeated = 0U;
            const std::size_t idx = getMajorValue(validList, repeated);
            if (expressionsCount == repeated)
            {
                value = validList.item(idx);
                status = DataStatus::VALID;
            }
            else
            {
                value = validList.item(idx);
                status = DataStatus::INVALID;
            }
        }
    }

    return status;
}

} // namespace expressionoperators
} // namespace lsr
