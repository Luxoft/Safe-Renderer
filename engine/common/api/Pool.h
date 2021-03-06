#ifndef LUXOFTSAFERENDERER_POOL_H
#define LUXOFTSAFERENDERER_POOL_H

/******************************************************************************
**
**   File:        Pool.h
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
#include "LSREngineError.h"
#include "NodeDataLength.h"
#include "PoolMarker.h"

#include <cstddef>

namespace lsr
{

/**
 * Class implements allocation process of some objects in internal storage.
 * It tracks the amount of free cells in the storage, where new objects can be allocated.
 *
 * There are two main methods which provide the main functionality:
 * @c Pool::allocate and @c Pool::deallocate.
 * Both of them are working with some memory storage:
 * @c Pool::allocate method searches free block in this storage and returns pointer to it to the caller,
 * while @c Pool::deallocate frees memory block, which was passed to the method,
 * and adds this block to the list of free blocks.
 *
 * Memory which was allocated with @c allocate method must be freed only with @c deallocate method.
 *
 * The size of the @c Pool will be more than sizeof(@c T) * @c PoolSize because of alignment,
 * which can be configured with @c AlignValue.
 *
 * @reqid SW_ENG_032, SW_ENG_033, SW_ENG_034, SW_ENG_035, SW_ENG_036, SW_ENG_037, SW_ENG_039, SW_ENG_047
 *
 * @tparam T          the type of objects which would be stored in the pool.
 * @tparam PoolSize   the maximum number of objects with type @c T which the pool can hold.
 *                    This value should be a non-zero value.
 * @tparam AlignValue the alignment value in the pool in bytes. This value should be
 *                    a non-zero power of 2 value.
 */
template<class T, std::size_t PoolSize, std::size_t AlignValue = sizeof(P_MAX_ALIGN)>
class Pool
{
public:
    /**
     * Constructor initializes the @c Pool.
     */
    Pool();

    /**
     * Methods searches the first free block in the internal storage and returns pointer to it.
     * If some errors occur, the @c error flag will be set. See @c LSREngineError.
     *
     * @param[out] error the error value which should be set during operation execution.
     *                   If this value is equal to @c LSR_NO_ENGINE_ERROR, allocation
     *                   finished successfully, and failed in other cases.
     *
     * @return pointer to the first free memory block if it exists, @c NULL otherwise.
     *         Returned pointer is not equal to NULL only if @c error == @c LSR_NO_ENGINE_ERROR.
     */
    void* allocate(LSREngineError& error);

    /**
     * Method sets to zero the memory block to which @c ptr points
     * and adds this block to the free blocks list.
     *
     * Method checks if @c ptr is a pointer to a valid object inside internal storage.
     * If @c ptr isn't a valid pointer, method returns @c LSR_POOL_INVALID_OBJECT.
     *
     * @param[in] ptr pointer to the block which should be deallocated.
     *
     * @return @c LSR_NO_ENGINE_ERROR if deallocation was successful, and other values of
     *         @c LSREngineError in other cases.
     */
    LSREngineError deallocate(void* const ptr);

    /**
     * Method checks if @c ptr is a pointer to a valid object inside internal storage.
     *
     * @param[in] ptr pointer to the object which should be checked.
     *
     * @return @c true if ptr is valid, @c false otherwise.
     */
    bool isAllocated(const void* const ptr) const;

    /**
     * Methods checks the internal storage for correctness.
     *
     * @return @c true if internal storage is in the correct state, @c false otherwise.
     *         @c false result can be interpreted as @c LSR_POOL_IS_CORRUPTED
     *         value.
     */
    bool checkPool() const;

private:

    /**
     * Let's check if @c AlignValue is a power of 2 value and is not equal to 0
     * and if @c PoolSize is a non-zero value.
     */
    P_STATIC_ASSERT((PoolSize != 0U) &&
                    ((AlignValue != 0U) &&
                    !(AlignValue & (AlignValue - 1))), "AlignValue or PoolSize is incorrect.")

    /**
     * @reqid SW_ENG_032
     */
    struct Node
    {
        // coverity[misra_cpp_2008_rule_9_5_1_violation]
        union NodeBody
        {
            /**
             * Size of data should be at least >= sizeof(T) and be compliant with the expression:
             * size % @c AlignValue == 0.
             */
            U8 data[impl::NodeDataLength<sizeof(T), AlignValue>::value];
            Node* next;
        };
        NodeBody body;
        impl::PoolMarker<AlignValue> marker;
    };

    static const U8 MARKER_FREE_CHAR = 0xAAU;
    static const U8 MARKER_BUSY_CHAR = 0x55U;

    /**
     * Methods can be used to check objects inside the pool.
     */
    bool checkObjectIsFree(const void * const ptr) const;
    bool checkObjectIsInsideStorage(const void* const ptr) const;
    bool checkBeginningOfObject(const void* const ptr) const;
    bool checkMarker(const void* const ptr) const;

    /**
     * Methods can be used to check the whole pool.
     */
    bool checkStorage() const;
    bool checkStandardMarkers() const;
    bool checkFreeList() const;

    U8 m_storage[PoolSize * sizeof(Node)];
    Node* m_pFreeList;
    const impl::PoolMarker<AlignValue> m_markerFree;
    const impl::PoolMarker<AlignValue> m_markerBusy;
};

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline Pool<T, PoolSize, AlignValue>::Pool()
    : m_pFreeList(NULL)
    , m_markerFree(MARKER_FREE_CHAR)
    , m_markerBusy(MARKER_BUSY_CHAR)
{
    // coverity[misra_cpp_2008_rule_0_1_2_violation] Template parameter
    static const std::size_t lastIndex = (PoolSize - 1U);

    // coverity[misra_cpp_2008_rule_5_2_7_violation]
    m_pFreeList = reinterpret_cast<Node*>(m_storage);
    if (lastIndex > 0U)
    {
        for (std::size_t i = 0U; i < lastIndex; ++i)
        {
            // coverity[misra_cpp_2008_rule_5_0_15_violation]
            Node& currentNode = m_pFreeList[i];
            // coverity[misra_cpp_2008_rule_5_0_15_violation]
            currentNode.body.next = &m_pFreeList[i + 1U];
            currentNode.marker = m_markerFree;
        }
    }

    // coverity[misra_cpp_2008_rule_5_0_15_violation]
    Node& lastNode = m_pFreeList[lastIndex];
    lastNode.body.next = NULL;
    lastNode.marker = m_markerFree;
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline void* Pool<T, PoolSize, AlignValue>::allocate(LSREngineError& error)
{
    void* pData = NULL;
    if (checkPool())
    {
        if (m_pFreeList != NULL)
        {
            static_cast<void>(pData);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            pData = m_pFreeList->body.data;
            m_pFreeList->marker = m_markerBusy;
            m_pFreeList = m_pFreeList->body.next;
            error = LSR_NO_ENGINE_ERROR;
        }
        else
        {
            error = LSR_POOL_IS_FULL;
        }
    }
    else
    {
        error = LSR_POOL_IS_CORRUPTED;
    }
    // coverity[misra_cpp_2008_rule_9_3_2_violation]
    return pData;
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline LSREngineError Pool<T, PoolSize, AlignValue>::deallocate(void* const ptr)
{
    LSREngineError res = LSR_NO_ENGINE_ERROR;
    if (checkPool())
    {
        // Check if ptr points inside the storage and to the beginning of the Node.
        if ((ptr != NULL) && isAllocated(ptr))
        {
            // Check if this is not double deallocation
            if (!checkObjectIsFree(ptr))
            {
                // coverity[misra_cpp_2008_rule_5_2_8_violation]
                Node* const pNode = static_cast<Node*>(ptr);
                static_cast<void>(std::memset(pNode->body.data, 0, sizeof(T)));  // ignore return value
                pNode->body.next = m_pFreeList;
                pNode->marker = m_markerFree;
                m_pFreeList = pNode;
                static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            }
            else
            {
                static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
                res = LSR_POOL_DOUBLE_DELETE;
            }
        }
        else
        {
            static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            res = LSR_POOL_INVALID_OBJECT;
        }
    }
    else
    {
        static_cast<void>(res);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        res = LSR_POOL_IS_CORRUPTED;
    }
    return res;
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkPool() const
{
    bool res = checkStandardMarkers()
            && checkStorage();
    if ((NULL != m_pFreeList) && res)
    {
        res = checkFreeList();
    }
    return res;
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::isAllocated(const void* const ptr) const
{
    return checkObjectIsInsideStorage(ptr) && checkBeginningOfObject(ptr) && checkMarker(ptr);
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkObjectIsInsideStorage(const void* const ptr) const
{
    // coverity[misra_cpp_2008_rule_5_2_8_violation]
    const U8* const tmpPtr = reinterpret_cast<const U8* const>(ptr);
    // coverity[misra_cpp_2008_rule_5_0_15_violation]
    return (tmpPtr >= m_storage) && (tmpPtr < (m_storage + sizeof(m_storage)));
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkBeginningOfObject(const void* const ptr) const
{
    // coverity[misra_cpp_2008_rule_5_2_8_violation]
    const U8* const tmpPtr = reinterpret_cast<const U8* const>(ptr);
    // coverity[misra_cpp_2008_rule_5_0_15_violation]
    const std::ptrdiff_t length = (tmpPtr - m_storage);

    return ((length == 0) || ((length >= static_cast<ptrdiff_t>(sizeof(Node))) && ((length % static_cast<ptrdiff_t>(sizeof(Node))) == 0)));
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkMarker(const void* const ptr) const
{
    // coverity[misra_cpp_2008_rule_5_2_8_violation]
    const Node* const pNode = reinterpret_cast<const Node* const>(ptr);
    return (pNode->marker == m_markerBusy) || (pNode->marker == m_markerFree);
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkStorage() const
{
    bool res = true;
    for (std::size_t idx = 0U; res && (idx < sizeof(m_storage)); idx += sizeof(Node))
    {
        res = checkMarker(&m_storage[idx]);
    }
    return res;
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkStandardMarkers() const
{
    return impl::PoolMarker<AlignValue>::isEqualToPattern(m_markerFree, MARKER_FREE_CHAR) &&
           impl::PoolMarker<AlignValue>::isEqualToPattern(m_markerBusy, MARKER_BUSY_CHAR);
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkObjectIsFree(const void* const ptr) const
{
    // coverity[misra_cpp_2008_rule_5_2_8_violation]
    const Node* const pNode = static_cast<const Node* const>(ptr);
    return pNode->marker == m_markerFree;
}

template<class T, std::size_t PoolSize, std::size_t AlignValue>
inline bool Pool<T, PoolSize, AlignValue>::checkFreeList() const
{
    bool res = true;
    const void* ptr = m_pFreeList;

    /**
     * If there is an infinite loop because of corruption
     * (some magic situation, when @c Pool::Node::NodeBody::next or @c m_pFreeList points
     * to some previous node in the list or to itself),
     * we should break the loop.
     * For this purpose we can use @c PoolSize value and counter of checked nodes.
     */
    std::size_t nodeCounter = 0U;
    while ((NULL != ptr) && res && (nodeCounter <= PoolSize))
    {
        res = checkObjectIsInsideStorage(ptr)
           && checkBeginningOfObject(ptr)
           && checkObjectIsFree(ptr);
        if (res)
        {
            // coverity[misra_cpp_2008_rule_5_2_8_violation]
            const Node* const pNode = static_cast<const Node*>(ptr);
            ptr = pNode->body.next;
            ++nodeCounter;
        }
    }

    /**
     * If there was an infinite loop, than
     * @c nodeCounter will be more than @c PoolSize.
     */
    if (nodeCounter > PoolSize)
    {
        res = false;
    }

    return res;
}

} // namespace lsr

#endif // LUXOFTSAFERENDERER_POOL_H
