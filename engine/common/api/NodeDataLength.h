#ifndef LUXOFTSAFERENDERER_NODEDATALENGTH_H
#define LUXOFTSAFERENDERER_NODEDATALENGTH_H

/******************************************************************************
**
**   File:        NodeDataLength.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "LsrTypes.h"

#include <cstddef>

namespace lsr
{

namespace impl
{

/**
 * Structure calculates the remainder of the division of @c A by @c B.
 * This statement should be true: @c A >= @c B
 *
 * @tparam A the dividend
 * @tparam B the divider
 */
template <std::size_t A, std::size_t B>
struct DivRemainder
{
    P_STATIC_ASSERT(A >= B, "DivRemainder: operands are incorrect")

    enum
    {
        value = A - (B * (A / B))
    };
};

/**
 * Structure calculates the length, which corresponds to such requirements:
 * - size >= @c ObjectSize;
 * - size % @c AlignValue == 0.
 *
 * @tparam ObjectSize      the size of the object which will be stored in the @c Pool
 * @tparam AlignValue      the align value of data inside the @c Pool
 * @tparam RemainderIsZero the flag which should be @c true if the reminder of
 *                         @c ObjectSize / @c AlignValue operation is equal to zero,
 *                         @c false otherwise. This parameter typically shouldn't be set by
 *                         user. It is a technical parameter.
 */
// coverity[misra_cpp_2008_rule_14_7_1_violation] Used for calculations during preprocessing
template <std::size_t ObjectSize, std::size_t AlignValue, bool RemainderIsZero>
struct LengthWithRemainder
{
};

template <std::size_t ObjectSize, std::size_t AlignValue>
struct LengthWithRemainder<ObjectSize, AlignValue, true>
{
    enum
    {
        value = ObjectSize
    };
};

template <std::size_t ObjectSize, std::size_t AlignValue>
struct LengthWithRemainder<ObjectSize, AlignValue, false>
{
    enum
    {
        value = (ObjectSize / AlignValue) * AlignValue + AlignValue
    };
};

/**
 * Structure calculates the length, which corresponds to such requirements:
 * - size >= @c ObjectSize;
 * - size % @c AlignValue == 0.
 *
 * @tparam ObjectSize     the size of the object which will be stored in the @c Pool
 * @tparam AlignValue     the align value of data inside the @c Pool
 * @tparam ObjectIsBigger the flag which should be @c true if @c ObjectSize > @c AlignValue
 *                        @c false otherwise. This parameter typically shouldn't be set by
 *                        user. It is a technical parameter.
 */
// coverity[misra_cpp_2008_rule_14_7_1_violation] Used for calculations during preprocessing
template <std::size_t ObjectSize, std::size_t AlignValue, bool ObjectIsBigger>
struct Length
{
};

template <std::size_t ObjectSize, std::size_t AlignValue>
struct Length<ObjectSize, AlignValue, true>
{
    enum
    {
        value = LengthWithRemainder<ObjectSize,
                                    AlignValue,
                                    (DivRemainder<ObjectSize, AlignValue>::value == 0U)>::value
    };
};

// coverity[misra_cpp_2008_rule_14_7_1_violation] Used for calculations during preprocessing
template <std::size_t ObjectSize, std::size_t AlignValue>
struct Length<ObjectSize, AlignValue, false>
{
    enum
    {
        value = AlignValue
    };
};

/**
 * Structure calculates the size of data inside Node (see @c Pool::Node::NodeBody)
 * This size should be at least >= @c ObjectSize and be compliant with the expression:
 * size % @c AlignValue == 0.
 *
 * @reqid SW_ENG_035
 *
 * @tparam ObjectSize     the size of the object which will be stored in the @c Pool
 * @tparam AlignValue     the align value of data inside the @c Pool
 * @tparam ObjectIsBigger the flag which should be @c true if @c ObjectSize > @c AlignValue
 *                        @c false otherwise. This parameter typically shouldn't be set by
 *                        user. It is a technical parameter.
 */
template<std::size_t ObjectSize, std::size_t AlignValue>
struct NodeDataLength
{
    enum
    {
        value = Length<ObjectSize,
                       AlignValue,
                       (ObjectSize > AlignValue)>::value
    };
};

} // namespace impl

} // namespace lsr

#endif // LUXOFTSAFERENDERER_NODEDATALENGTH_H
