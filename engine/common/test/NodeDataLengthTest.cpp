/******************************************************************************
**
**   File:        NodeDataLengthTest.cpp
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

#include <NodeDataLength.h>

#include <gtest/gtest.h>
#include <cstddef>

using namespace lsr;

/**
 * As gtest provides only one template parameter in test fixture
 * to be checked in TYPED_TEST_CASE we have to hide template parameters in some struct.
 */
template <typename A, typename B, typename C>
struct TypeDefinitions
{
    typedef A ObjectSize;
    typedef B AlignValue;
    typedef C ExpectedValue;
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

/**
 * This test fixture will test NodeDataLength.
 */
template <class T>
class NodeDataLengthTest : public testing::Test
{
public:
    NodeDataLengthTest()
    {
    }

    std::size_t getLength()
    {
        return impl::NodeDataLength<T::ObjectSize::value, T::AlignValue::value>::value;
    }

    virtual ~NodeDataLengthTest()
    {}
};

// <TypeDefinitions <ObjectSize, AlignValue, ExpectedValue>
typedef ::testing::Types <TypeDefinitions<TypeValue<1>,  TypeValue<1>,  TypeValue<1> >,
                          // ObjectSize % AlignValue == 0
                          TypeDefinitions<TypeValue<2>,  TypeValue<1>,  TypeValue<2> >,
                          TypeDefinitions<TypeValue<4>,  TypeValue<1>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<8>,  TypeValue<1>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<16>, TypeValue<1>,  TypeValue<16> >,
                          TypeDefinitions<TypeValue<32>, TypeValue<1>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<1>,  TypeValue<2>,  TypeValue<2> >,
                          TypeDefinitions<TypeValue<2>,  TypeValue<2>,  TypeValue<2> >,
                          TypeDefinitions<TypeValue<4>,  TypeValue<2>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<8>,  TypeValue<2>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<16>, TypeValue<2>,  TypeValue<16> >,
                          TypeDefinitions<TypeValue<32>, TypeValue<2>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<1>,  TypeValue<4>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<2>,  TypeValue<4>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<4>,  TypeValue<4>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<8>,  TypeValue<4>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<16>, TypeValue<4>,  TypeValue<16> >,
                          TypeDefinitions<TypeValue<32>, TypeValue<4>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<1>,  TypeValue<8>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<2>,  TypeValue<8>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<4>,  TypeValue<8>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<8>,  TypeValue<8>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<16>, TypeValue<8>,  TypeValue<16> >,
                          TypeDefinitions<TypeValue<32>, TypeValue<8>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<1>,  TypeValue<16>, TypeValue<16> >,
                          TypeDefinitions<TypeValue<2>,  TypeValue<16>, TypeValue<16> >,
                          TypeDefinitions<TypeValue<4>,  TypeValue<16>, TypeValue<16> >,
                          TypeDefinitions<TypeValue<8>,  TypeValue<16>, TypeValue<16> >,
                          TypeDefinitions<TypeValue<16>, TypeValue<16>, TypeValue<16> >,
                          TypeDefinitions<TypeValue<32>, TypeValue<16>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<1>,  TypeValue<32>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<2>,  TypeValue<32>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<4>,  TypeValue<32>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<8>,  TypeValue<32>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<16>, TypeValue<32>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<32>, TypeValue<32>, TypeValue<32> >,
                          // ObjectSize % AlignValue != 0
                          TypeDefinitions<TypeValue<3>,  TypeValue<1>,  TypeValue<3> >,
                          TypeDefinitions<TypeValue<3>,  TypeValue<2>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<3>,  TypeValue<4>,  TypeValue<4> >,
                          TypeDefinitions<TypeValue<3>,  TypeValue<8>,  TypeValue<8> >,
                          TypeDefinitions<TypeValue<3>,  TypeValue<16>, TypeValue<16> >,
                          TypeDefinitions<TypeValue<3>,  TypeValue<32>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<31>, TypeValue<1>,  TypeValue<31> >,
                          TypeDefinitions<TypeValue<31>, TypeValue<2>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<31>, TypeValue<4>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<31>, TypeValue<8>,  TypeValue<32> >,
                          TypeDefinitions<TypeValue<31>, TypeValue<16>, TypeValue<32> >,
                          TypeDefinitions<TypeValue<31>, TypeValue<32>, TypeValue<32> >,
                          // Very large values
                          TypeDefinitions<TypeValue<5000>, TypeValue<3>, TypeValue<5001> >,
                          TypeDefinitions<TypeValue<5000>, TypeValue<4>, TypeValue<5000> > > TestCases;

TYPED_TEST_CASE(NodeDataLengthTest, TestCases);

TYPED_TEST(NodeDataLengthTest, GetLength)
{
    EXPECT_EQ(TypeParam::ExpectedValue::value, this->getLength());
}


