/******************************************************************************
**
**   File:        PooledObjectFactoryTest.cpp
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

#include "SelfCheckerClass.h"

#include <PooledObjectFactory.h>
#include <LSRError.h>

#include <gtest/gtest.h>
#include <cstddef>
#include <algorithm>

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
 * As PooledObjectFactory has second template parameter as std::size_t, and
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
 * This test fixture will test types for which constructor can be executed.
 */
template <class T>
class PooledObjectFactoryTest : public testing::Test
{
public:
    PooledObjectFactoryTest()
        : m_factory(NULL)
    {
    }

    void SetUp()
    {
        m_factory =
            new PooledObjectFactory<typename T::ObjectType, T::PoolSize::value, T::AlignValue::value>();
    }

    void TearDown()
    {
        delete m_factory;
    }

    typename T::ObjectType* createObject(LSRError& error)
    {
        return m_factory->createObject(error);
    }

    LSRError deleteObject(typename T::ObjectType* object)
    {
        return m_factory->deleteObject(object);
    }

    bool checkFactory() const
    {
        return m_factory->checkFactory();
    }

    virtual ~PooledObjectFactoryTest()
    {}

protected:
    PooledObjectFactory<typename T::ObjectType, T::PoolSize::value, T::AlignValue::value>* m_factory;
};

/**
 * This test fixture will test types for which constructor can't be executed or
 * which are not self-checker types.
 */
template <class T>
class PooledObjectFactoryTestBaseTypes : public PooledObjectFactoryTest<T>
{
public:
    PooledObjectFactoryTestBaseTypes()
    {}

    virtual ~PooledObjectFactoryTestBaseTypes()
    {}
};

typedef ::testing::Types <TypeDefinitions<SelfCheckerClass, TypeValue<2>,   TypeValue<8> >,
                          TypeDefinitions<SelfCheckerClass, TypeValue<20>,  TypeValue<8> >,
                          TypeDefinitions<SelfCheckerClass, TypeValue<512>, TypeValue<sizeof(P_MAX_ALIGN)> >,
                          TypeDefinitions<SelfCheckerClass, TypeValue<512>, TypeValue<8> > > ImplForSelfCheckers;

/**
 * As base types don't have constructors with parameters, there will be an issue in test
 * coverage in calling parameterized createObject methods.
 */
typedef ::testing::Types <TypeDefinitions<U8,  TypeValue<2>,   TypeValue<8> >,
                          TypeDefinitions<U16, TypeValue<20>,  TypeValue<8> >,
                          TypeDefinitions<U16, TypeValue<512>, TypeValue<sizeof(P_MAX_ALIGN)> >,
                          TypeDefinitions<U32, TypeValue<512>, TypeValue<8> > > ImplForBaseTypes;

TYPED_TEST_CASE(PooledObjectFactoryTest, ImplForSelfCheckers);

TYPED_TEST_CASE(PooledObjectFactoryTestBaseTypes, ImplForBaseTypes);

/**
 * These functions will be called from both classes @c PooledObjectFactoryTest and
 * @c PooledObjectFactoryTestBaseTypes
 */
template <class T>
void Defragmentation(PooledObjectFactoryTest<T>* factory)
{
    LSRError error = LSR_NO_ERROR;
    typename T::ObjectType* objectFirst = factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(LSRError(LSR_NO_ERROR), factory->deleteObject(objectFirst));

    // After deleting, another creating method should return the same address.
    typename T::ObjectType* objectSecond = factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(objectFirst, objectSecond);
}

template <class T>
void DeleteObject(PooledObjectFactoryTest<T>* factory)
{
    LSRError error = LSR_NO_ERROR;
    typename T::ObjectType* object = factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(LSRError(LSR_NO_ERROR), factory->deleteObject(object));
}

template <class T>
void DeleteObjectTwice(PooledObjectFactoryTest<T>* factory)
{
    LSRError error = LSR_NO_ERROR;
    typename T::ObjectType* object = factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(LSRError(LSR_NO_ERROR), factory->deleteObject(object));
    EXPECT_EQ(LSRError(LSR_POOL_DOUBLE_DELETE), factory->deleteObject(object));
}

template <class T>
void DeleteObjectWithNullPointer(PooledObjectFactoryTest<T>* factory)
{
    LSRError error = LSR_NO_ERROR;
    factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(LSRError(LSR_POOL_INVALID_OBJECT), factory->deleteObject(NULL));
}

template <class T>
void DeleteObjectWithPointerFromAnotherBuffer(PooledObjectFactoryTest<T>* factory)
{
    // Pointer to memory before storage
    LSRError error = LSR_NO_ERROR;
    typename T::ObjectType* object = factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(LSRError(LSR_POOL_INVALID_OBJECT), factory->deleteObject(object - 0x50U));

    // Pointer to memory after storage
    EXPECT_EQ(LSRError(LSR_POOL_INVALID_OBJECT), factory->deleteObject(object + 0x7FFFU));
}

template <class T>
void DeleteObjectWithShiftedPointer(PooledObjectFactoryTest<T>* factory)
{
    LSRError error = LSR_NO_ERROR;
    U8* ptr = reinterpret_cast<U8*>(factory->createObject(error));
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    // check at the position < getCellSize
    typename T::ObjectType* object =
        reinterpret_cast<typename T::ObjectType*>(ptr + 1U);
    EXPECT_EQ(LSRError(LSR_POOL_INVALID_OBJECT), factory->deleteObject(object));

    // check at the position > getCellSize
    object = reinterpret_cast<typename T::ObjectType*>(ptr - 1U);
    EXPECT_EQ(LSRError(LSR_POOL_INVALID_OBJECT), factory->deleteObject(object));
}

template <class T>
void CheckFactory(PooledObjectFactoryTest<T>* factory)
{
    LSRError error = LSR_NO_ERROR;
    typename T::ObjectType* object = factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_NO_ERROR), error);

    EXPECT_EQ(LSRError(LSR_NO_ERROR), factory->deleteObject(object));

    EXPECT_TRUE(factory->checkFactory());
}

/**
 * Tests for PooledObjectFactoryTest
 */
TYPED_TEST(PooledObjectFactoryTest, CreateObject)
{
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        LSRError error = LSR_NO_ERROR;
        typename TypeParam::ObjectType* object = this->m_factory->createObject(error);
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
        EXPECT_TRUE(object->wasConstructed());
    }
}

TYPED_TEST(PooledObjectFactoryTest, CreateTooManyObjects)
{
    LSRError error = LSR_NO_ERROR;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        typename TypeParam::ObjectType* object = this->m_factory->createObject(error);
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
        EXPECT_TRUE(object->wasConstructed());
    }
    typename TypeParam::ObjectType* object = this->m_factory->createObject(error);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}


TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg1)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg2)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg3)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg4)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg5)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg6)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg7)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg8)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7, i * 8);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7, i * 8);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg9)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7, i * 8, i * 9);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7, i * 8, i * 9);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, CreateObjectWithArg10)
{
    LSRError error = LSR_NO_ERROR;
    typename TypeParam::ObjectType* object = NULL;
    std::size_t i = 0U;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7, i * 8, i * 9, i * 10);
        EXPECT_TRUE(object->wasConstructed());
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }

    object = this->m_factory->createObject(error, i, i * 2, i * 3, i * 4, i * 5, i * 6, i * 7, i * 8, i * 9, i * 10);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
    EXPECT_EQ(NULL, object);
}

TYPED_TEST(PooledObjectFactoryTest, Defragmentation)
{
    Defragmentation<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, DeleteObject)
{
    DeleteObject<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, DeleteObjectTwice)
{
    DeleteObjectTwice<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, DeleteObjectWithNullPointer)
{
    DeleteObjectWithNullPointer<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, DeleteObjectWithPointerFromAnotherBuffer)
{
    DeleteObjectWithPointerFromAnotherBuffer<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, DeleteObjectWithShiftedPointer)
{
    DeleteObjectWithShiftedPointer<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, CheckFactory)
{
    CheckFactory<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTest, CheckFactoryWithCorruptedMemory)
{
    LSRError error = LSR_NO_ERROR;
    U8* objectFirst = reinterpret_cast<U8*>(this->m_factory->createObject(error));
    U8* objectSecond = reinterpret_cast<U8*>(this->m_factory->createObject(error));
    const std::size_t cellSize = objectSecond - objectFirst;

    memset(this->m_factory, 0xEE, cellSize * 2);

    EXPECT_FALSE(this->m_factory->checkFactory());
}

/**
 * Tests for PooledObjectFactoryTestBaseTypes
 */
TYPED_TEST(PooledObjectFactoryTestBaseTypes, CreateObject)
{
    LSRError error = LSR_NO_ERROR;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        this->m_factory->createObject(error);
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, CreateTooManyObjects)
{
    LSRError error = LSR_NO_ERROR;
    for (std::size_t i = 0U; i < TypeParam::PoolSize::value; ++i)
    {
        this->m_factory->createObject(error);
        EXPECT_EQ(LSRError(LSR_NO_ERROR), error);
    }
    typename TypeParam::ObjectType* object = this->m_factory->createObject(error);
    EXPECT_EQ(NULL, object);
    EXPECT_EQ(LSRError(LSR_POOL_IS_FULL), error);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, Defragmentation)
{
    Defragmentation<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, DeleteObject)
{
    DeleteObject<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, DeleteObjectTwice)
{
    DeleteObjectTwice<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, DeleteObjectWithNullPointer)
{
    DeleteObjectWithNullPointer<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, DeleteObjectWithPointerFromAnotherBuffer)
{
    DeleteObjectWithPointerFromAnotherBuffer<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, DeleteObjectWithShiftedPointer)
{
    DeleteObjectWithShiftedPointer<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, CheckFactory)
{
    CheckFactory<TypeParam>(this);
}

TYPED_TEST(PooledObjectFactoryTestBaseTypes, CheckFactoryWithCorruptedMemory)
{
    LSRError error = LSR_NO_ERROR;
    U8* objectFirst = reinterpret_cast<U8*>(this->m_factory->createObject(error));
    U8* objectSecond = reinterpret_cast<U8*>(this->m_factory->createObject(error));
    const std::size_t cellSize = objectSecond - objectFirst;

    memset(this->m_factory, 0xEE, cellSize * 2);

    EXPECT_FALSE(this->m_factory->checkFactory());
}
