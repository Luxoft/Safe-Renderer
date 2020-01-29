/******************************************************************************
**
**   File:        PoolFaultInjectionTest.cpp
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

#include "PoolTestTypes.h"

#include <LSREngineError.h>

#include <gtest/gtest.h>
#include <cstddef>

template <class T>
class PoolFaultInjectionTest: public PoolTest<T>
{
public:
    PoolFaultInjectionTest()
    {}

    virtual ~PoolFaultInjectionTest()
    {}
};

TYPED_TEST_CASE(PoolFaultInjectionTest, PoolTestCases);

// Testing Allocation method

TYPED_TEST(PoolFaultInjectionTest, AllocateWithBadPool)
{
    this->allocate();

    this->m_corrupter->corruptStorage();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithOverWrittenStandardFreeMarker)
{
    this->allocate();

    this->m_corrupter->corruptFreeMarker();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithOverWrittenStandardBusyMarker)
{
    this->allocate();

    this->m_corrupter->corruptBusyMarker();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithOverWrittenFreeNode)
{

    this->allocate();

    this->m_corrupter->corruptFreeNode();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithCorruptedFreeListPtrOutSideStorage)
{
    this->allocate();

    this->m_corrupter->corruptFreeListPtrBeforeStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());

    this->m_corrupter->corruptFreeListPtrAtTheEndOfStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());

    this->m_corrupter->corruptFreeListPtrAfterStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithCorruptedFreeListPtrInSideStorage)
{
    this->allocate();

    this->m_corrupter->corruptFreeListPtrLessThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());

    this->m_corrupter->corruptFreeListPtrMoreThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithCorruptedNextPtrOutSideStorage)
{
    this->allocate();

    this->m_corrupter->corruptNextPtrBeforeStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());

    this->m_corrupter->corrupNextPtrAtTheEndOfStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());

    this->m_corrupter->corruptNextListPtrAfterStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithCorruptedNextPtrInSideStorage)
{
    this->allocate();

    this->m_corrupter->corruptNextListPtrLessThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());

    this->m_corrupter->corruptNextListPtrMoreThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithLoopInFreeList1)
{
    // make loop with m_pFreeList value
    this->m_corrupter->createInfLoopFromPos(1U);

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

TYPED_TEST(PoolFaultInjectionTest, AllocateWithLoopInFreeList2)
{
    // Make loop with some value inside free list.
    this->m_corrupter->createInfLoopFromPos(2U);

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->allocateFailed());
}

// Testing Deallocation method

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithBadPool)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptStorage();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithOverWrittenStandardFreeMarker)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptFreeMarker();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithOverWrittenStandardBusyMarker)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptBusyMarker();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithOverWrittenFreeNode)
{

    void* ptr = this->allocate();

    this->m_corrupter->corruptFreeNode();

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithCorruptedFreeListPtrOutSideStorage)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptFreeListPtrBeforeStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));

    this->m_corrupter->corruptFreeListPtrAtTheEndOfStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));

    this->m_corrupter->corruptFreeListPtrAfterStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithCorruptedFreeListPtrInSideStorage)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptFreeListPtrLessThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));

    this->m_corrupter->corruptFreeListPtrMoreThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithCorruptedNextPtrOutSideStorage)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptNextPtrBeforeStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));

    this->m_corrupter->corrupNextPtrAtTheEndOfStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));

    this->m_corrupter->corrupNextPtrAtTheEndOfStorage();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithCorruptedNextPtrInSideStorage)
{
    void* ptr = this->allocate();

    this->m_corrupter->corruptNextListPtrLessThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));

    this->m_corrupter->corruptNextListPtrMoreThanCell();
    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithLoopInFreeList1)
{
    void* ptr = this->allocate();

    // make loop with m_pFreeList value
    this->m_corrupter->createInfLoopFromPos(1U);

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

TYPED_TEST(PoolFaultInjectionTest, DeallocateWithLoopInFreeList2)
{
    void* ptr = this->allocate();

    // Make loop with some value inside free list.
    this->m_corrupter->createInfLoopFromPos(2U);

    EXPECT_EQ(LSREngineError(LSR_POOL_IS_CORRUPTED), this->m_pool->deallocate(ptr));
}

// Testing CheckPool method

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithOverWrittenStandardFreeMarker1)
{
    EXPECT_TRUE(this->m_pool->checkPool());

    this->m_corrupter->corruptFreeMarker();

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithOverWrittenStandardFreeMarker2)
{
    this->fillUpPool();

    this->m_corrupter->corruptFreeMarker();

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithOverWrittenStandardBusyMarker1)
{
    this->m_corrupter->corruptBusyMarker();

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithOverWrittenStandardBusyMarker2)
{
    this->fillUpPool();

    this->m_corrupter->corruptBusyMarker();

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithOverWrittenMarker)
{
    this->fillUpPool();

    this->m_corrupter->corruptStorage();

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithOverWrittenFreeNode)
{
    this->allocate();

    this->m_corrupter->corruptFreeNode();

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithCorruptedFreeListPtrOutSideStorage)
{
    EXPECT_TRUE(this->m_pool->checkPool());

    this->m_corrupter->corruptFreeListPtrBeforeStorage();
    EXPECT_FALSE(this->m_pool->checkPool());

    this->m_corrupter->corruptFreeListPtrAtTheEndOfStorage();
    EXPECT_FALSE(this->m_pool->checkPool());

    this->m_corrupter->corruptFreeListPtrAfterStorage();
    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithCorruptedFreeListPtrInSideStorage)
{
    EXPECT_TRUE(this->m_pool->checkPool());

    this->m_corrupter->corruptFreeListPtrLessThanCell();
    EXPECT_FALSE(this->m_pool->checkPool());

    this->m_corrupter->corruptFreeListPtrMoreThanCell();
    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithCorruptedNextPtrOutSideStorage)
{
    EXPECT_TRUE(this->m_pool->checkPool());

    this->m_corrupter->corruptNextPtrBeforeStorage();
    EXPECT_FALSE(this->m_pool->checkPool());

    this->m_corrupter->corrupNextPtrAtTheEndOfStorage();
    EXPECT_FALSE(this->m_pool->checkPool());

    this->m_corrupter->corruptNextListPtrAfterStorage();
    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithCorruptedNextPtrInSideStorage)
{
    EXPECT_TRUE(this->m_pool->checkPool());

    this->m_corrupter->corruptNextListPtrLessThanCell();
    EXPECT_FALSE(this->m_pool->checkPool());

    this->m_corrupter->corruptNextListPtrMoreThanCell();
    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithLoopInFreeList1)
{
    // make loop with m_pFreeList value
    this->m_corrupter->createInfLoopFromPos(1U);

    EXPECT_FALSE(this->m_pool->checkPool());
}

TYPED_TEST(PoolFaultInjectionTest, CheckPoolWithLoopInFreeList2)
{
    // Make loop with some value inside free list.
    this->m_corrupter->createInfLoopFromPos(2U);

    EXPECT_FALSE(this->m_pool->checkPool());
}
