#ifndef LUXOFTSAFERENDERER_POOLTESTTYPES_H
#define LUXOFTSAFERENDERER_POOLTESTTYPES_H

/******************************************************************************
**
**   File:        PoolTestTypes.h
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

#include "PoolCorrupter.h"

#include <Pool.h>

#include <cstddef>
#include <gtest/gtest.h>

using namespace lsr;

/**
 * As gtest provides only one template parameter in test fixture
 * to be checked in TYPED_TEST_CASE we have to hide template parameters in some struct.
 */
template <typename A, typename B, typename C>
struct TypeDefinitions
{
    typedef A ObjectType;
    typedef B PoolSize;
    typedef C AlignValue;
};

/**
 * As Pool has second template parameter as std::size_t, and
 * TypeDefinitions needs to have a type as both parameters, we
 * use TypeValue to pass std::size-t value as type.
 */
template <std::size_t N>
class TypeValue
{
public:
    static const std::size_t value = N;
};
template <std::size_t N> const std::size_t TypeValue<N>::value;

typedef ::testing::Types <TypeDefinitions<U8,  TypeValue<256>, TypeValue<1> >,
                          TypeDefinitions<U16, TypeValue<256>, TypeValue<1> >,
                          TypeDefinitions<U32, TypeValue<256>, TypeValue<1> >,
                          TypeDefinitions<U64, TypeValue<256>, TypeValue<1> >,
                          TypeDefinitions<U8,  TypeValue<256>, TypeValue<2> >,
                          TypeDefinitions<U16, TypeValue<256>, TypeValue<2> >,
                          TypeDefinitions<U32, TypeValue<256>, TypeValue<2> >,
                          TypeDefinitions<U64, TypeValue<256>, TypeValue<2> >,
                          TypeDefinitions<U8,  TypeValue<256>, TypeValue<4> >,
                          TypeDefinitions<U16, TypeValue<256>, TypeValue<4> >,
                          TypeDefinitions<U32, TypeValue<256>, TypeValue<4> >,
                          TypeDefinitions<U64, TypeValue<256>, TypeValue<4> >,
                          TypeDefinitions<U8,  TypeValue<256>, TypeValue<8> >,
                          TypeDefinitions<U16, TypeValue<256>, TypeValue<8> >,
                          TypeDefinitions<U32, TypeValue<256>, TypeValue<8> >,
                          TypeDefinitions<U64, TypeValue<256>, TypeValue<8> >,
                          // Default value of the alignment
                          TypeDefinitions<U8,  TypeValue<256>, TypeValue<sizeof(P_MAX_ALIGN)> >,
                          TypeDefinitions<U16, TypeValue<256>, TypeValue<sizeof(P_MAX_ALIGN)> >,
                          TypeDefinitions<U32, TypeValue<256>, TypeValue<sizeof(P_MAX_ALIGN)> >,
                          TypeDefinitions<U64, TypeValue<256>, TypeValue<sizeof(P_MAX_ALIGN)> >,
                          TypeDefinitions<U8,  TypeValue<512>, TypeValue<8> >,
                          TypeDefinitions<U8,  TypeValue<20>,  TypeValue<8> >,
                          TypeDefinitions<U8,  TypeValue<4>,   TypeValue<8> > > PoolTestCases;

/**
 * This test fixture will test Pool.
 */
template <class T>
class PoolTest : public testing::Test
{
public:
    typedef Pool<typename T::ObjectType,
                 T::PoolSize::value,
                 T::AlignValue::value> PoolType;

    typedef PoolCorrupter<typename T::ObjectType,
                          T::PoolSize::value,
                          T::AlignValue::value> CorrupterType;

    PoolTest()
        : m_pool(NULL)
        , m_corrupter(NULL)
    {
    }

    void SetUp()
    {
        m_pool = new PoolType();
        m_corrupter = reinterpret_cast<CorrupterType*>(m_pool);
    }

    void TearDown()
    {
        delete m_pool;
        m_corrupter = NULL;
        m_pool = NULL;
    }

    virtual ~PoolTest()
    {}

    void* allocate()
    {
        LSRError error = LSR_NO_ERROR;
        void* ptr = this->m_pool->allocate(error);
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
        EXPECT_TRUE(NULL != ptr);
        return ptr;
    }

    LSRError allocateFailed()
    {
        LSRError error = LSR_NO_ERROR;
        const void* ptr = this->m_pool->allocate(error);
        EXPECT_TRUE(error != LSRError(LSR_NO_ERROR));
        EXPECT_TRUE(NULL == ptr);
        return error;
    }

    void fillUpPool(const std::size_t count = T::PoolSize::value)
    {
        for (std::size_t i = 0U; i < count; ++i)
        {
            allocate();
        }
    }

protected:
    PoolType* m_pool;
    CorrupterType* m_corrupter;
};

#endif // LUXOFTSAFERENDERER_POOLTESTTYPES_H
