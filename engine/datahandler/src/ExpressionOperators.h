#ifndef LUXOFTSAFERENDERER_EXPRESSIONOPERATORS_H
#define LUXOFTSAFERENDERER_EXPRESSIONOPERATORS_H

/******************************************************************************
**
**   File:        ExpressionOperators.h
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

#include <IDataHandler.h>
#include <DataContext.h>
#include <Number.h>
#include <DataStatus.h>

#include <ExpressionType.h>
#include <ExpressionTermType.h>
#include <BitmapIdTableType.h>
#include <EnumerationBitmapMapType.h>

namespace lsr
{
namespace expressionoperators
{
/**
 * Method sets @c value to the interval [min, max].
 *
 * Method requires that @c pExpression has exactly 3 ExpressionTermType objects, where
 * the first one  - value which should be re-set;
 * the second one - the minimum value of the interval;
 * the third one  - the maximum value of the interval.
 * All these objects must have the same type, see @c DynamicDataTypeEnumeration.
 *
 * @reqid SW_ENG_056
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be handled.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain:
 *                          - the first @c ExpressionTermType value if it lies in the
 *                         interval [min, max];
 *                          - the second @c ExpressionTermType value if the first
 *                         @c ExpressionTermType value is less than the second one;
 *                          - the third @c ExpressionTermType value if the first
 *                         @c ExpressionTermType value is greater than the third one.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus minMax(const ExpressionType* const pExpression,
                  DataContext* const pContext,
                  Number& value);

/**
 * Method checks if two @c ExpressiontermType objects,
 * which @c pExpression contains, are equal.
 *
 * @reqid SW_ENG_052
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         objects are equal, @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus equals(const ExpressionType* const pExpression,
                  DataContext* const pContext,
                  Number& value);

/**
 * Method checks if two @c ExpressiontermType objects,
 * which @c pExpression contains, are not equal to each other.
 *
 * @reqid SW_ENG_052
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         objects are not equal, @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus notEquals(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value);

/**
 * Method checks if the first @c ExpressiontermType object is less than the second one,
 * @c pExpression is the owner of both objects.
 *
 * @reqid SW_ENG_052
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         the first object is less than the second one, @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus lessThan(const ExpressionType* const pExpression,
                    DataContext* const pContext,
                    Number& value);

/**
 * Method checks if the first @c ExpressiontermType object is less or equal to the second one,
 * @c pExpression is the owner of both objects.
 *
 * @reqid SW_ENG_052
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         the first object is less or equal to the second one,
 *                         @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus lessThanOrEquals(const ExpressionType* const pExpression,
                            DataContext* const pContext,
                            Number& value);

/**
 * Method checks if the first @c ExpressiontermType object is greater than the second one,
 * @c pExpression is the owner of both objects.
 *
 * @reqid SW_ENG_052
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         the first object is greater than the second one, @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus greaterThan(const ExpressionType* const pExpression,
                       DataContext* const pContext,
                       Number& value);

/**
 * Method checks if the first @c ExpressiontermType object is greater or equal to the second one,
 * @c pExpression is the owner of both objects.
 *
 * @reqid SW_ENG_052
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         the first object is greater or equal to the second one,
 *                         @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus greaterThanOrEquals(const ExpressionType* const pExpression,
                               DataContext* const pContext,
                               Number& value);

/**
 * Method searches for @c BitmapId which is associated with @c value in the
 * @c BitmapIdTableType object.
 *
 * Method requires that @c pExpression has exactly 2 or 3 ExpressionTermType objects, where
 * the first one  - the key value which should be searched in the table;
 * the second one - object, which contains @c BitmapIdTableType object;
 * the third one  - the default value, which will be set, if searching failed.
 *
 * @reqid SW_ENG_055
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be handled.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain @c BitmapId value which
 *                         is associated with incoming parameter @c value.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus itemAt(const ExpressionType* const pExpression,
                  DataContext* const pContext,
                  Number& value);

/**
 * Method evaluates "logical and" operation with two @c ExpressiontermType objects,
 * @c pExpression is the owner of both objects.
 * Both these objects should return @c DATATYPE_BOOLEAN object.
 *
 * @reqid SW_ENG_105
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         both objects are equal to @c true,
 *                         @c false otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus booleanAnd(const ExpressionType* const pExpression,
                      DataContext* const pContext,
                      Number& value);

/**
 * Method evaluates "logical or" operation with two @c ExpressiontermType objects,
 * @c pExpression is the owner of both objects.
 * Both these objects should return @c DATATYPE_BOOLEAN object.
 *
 * @reqid SW_ENG_105
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c false if
 *                         both objects are equal to @c false,
 *                         @c true otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus booleanOr(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value);

/**
 * Method evaluates "logical not" operation with @c ExpressiontermType object,
 * @c pExpression is the owner of this object.
 * That object should return @c DATATYPE_BOOLEAN object.
 *
 * @reqid SW_ENG_105
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value. It will contain Boolean value @c true if
 *                         the object is equal to @c false,
 *                         @c true otherwise.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus booleanNot(const ExpressionType* const pExpression,
                      DataContext* const pContext,
                      Number& value);

/**
 * Method returns the result of evaluation the first @c ExpressiontermType object.
 * If this result has the status other than @c DataStatus::VALID, method returns
 * the result of evaluation the second @c ExpressiontermType object
 * @c pExpression is the owner of both objects.
 *
 * @reqid SW_ENG_106
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus fallback(const ExpressionType* const pExpression,
                    DataContext* const pContext,
                    Number& value);

/**
 * Method returns the result of evaluation the first @c ExpressiontermType object.
 * If this result has the status
 * - @c DataStatus::INVALID: method returns the result of evaluation
 *                           the second @c ExpressiontermType object;
 * - other cases:            method returns the result of evaluation
 *                           the third @c ExpressiontermType object;
 * @c pExpression is the owner of all these objects.
 *
 * @reqid SW_ENG_106
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus fallback2(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value);

/**
 * Method returns the result of evaluation the first @c ExpressiontermType object.
 * If this result has the status
 * - @c DataStatus::INVALID       method returns the result of evaluation
 *                                the second @c ExpressiontermType object;
 * - @c DataStatus::NOT_AVAILABLE method returns the result of evaluation
 *                                the third @c ExpressiontermType object;
 * - other cases:                 method returns the result of evaluation
 *                                the fourth @c ExpressiontermType object;
 * @c pExpression is the owner of all these objects.
 *
 * @reqid SW_ENG_106
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus fallback3(const ExpressionType* const pExpression,
                     DataContext* const pContext,
                     Number& value);

/**
 * Method takes as input parameter @c ExpressionType object with 3
 * child @c ExpressiontermType objects. method calculates all
 * these expressions and according to the comparison rules returns the result.
 *
 * Values comparison rules:
 * 1. Returns value of the first @c ExpressionType object and
 *    valid state if all values are equal;
 * 2. If 2 values of @c ExpressionType objects are equal,
 *    return this value, but raise invalid state;
 * 3. If all values of @c ExpressionType objects are different,
 *    return any value, but raise inconsistent state.
 *
 * State comparison rules:
 * 1. If one of the values is inconsistent, the result value is also inconsistent;
 * 2. If one of the value is invalid, the result value is invalid or inconsistent;
 * 3. If two values are invalid and one - valid, result is invalid.

 * All @c ExpressionType objects should be of the same type.
 *
 * @reqid SW_ENG_113
 *
 * @param[in]  pExpression pointer to @c ExpressionType object.
 *                         It is the owner of objects, that need to be compared.
 * @param[in]  pContext    data context, which shall be used for evaluation.
 * @param[out] value       the output value.
 *
 * @return status of @c value, see @c DataStatus.
 */
DataStatus redundancy(const ExpressionType* const pExpression,
                      DataContext* const pContext,
                      Number& value);

} // namespace expressionoperators
} // namespace lsr

#endif // LUXOFTSAFERENDERER_EXPRESSIONOPERATORS_H
