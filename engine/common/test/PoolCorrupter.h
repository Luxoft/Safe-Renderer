#ifndef LUXOFTSAFERENDERER_POOLCORRUPTER_H
#define LUXOFTSAFERENDERER_POOLCORRUPTER_H

/******************************************************************************
**
**   File:        PoolCorrupter.h
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
#include <PoolMarker.h>

/**
 * This class helps to perform false injection tests for the @c Pool class.
 * Its declaration should be exactly the same as the one of the @c Pool class.
 */
template<class T, std::size_t PoolSize, std::size_t AlignValue>
class PoolCorrupter
{
public:
    PoolCorrupter()
    {}

    struct Node
    {
        union NodeBody
        {
            U8 data[lsr::impl::NodeDataLength<sizeof(T), AlignValue>::value];
            Node* next;
        };
        NodeBody body;
        lsr::impl::PoolMarker<AlignValue> marker;
    };

    void corruptStorage()
    {
        const std::size_t cellSize = sizeof(Node);
        const std::size_t storageSize = sizeof(storage);

        memset(storage + storageSize/2, 0xEE, cellSize);
    }

    void corruptFreeMarker()
    {
        markerFree = lsr::impl::PoolMarker<AlignValue>(0xEE);
    }

    void corruptBusyMarker()
    {
        markerBusy = lsr::impl::PoolMarker<AlignValue>(0xEE);
    }

    void corruptFreeNode()
    {
        Node* node = pFreeList->body.next;
        node->marker = markerBusy;
    }

    void corruptFreeListPtrBeforeStorage()
    {
        pFreeList = reinterpret_cast<Node*>(storage - 1U);
    }

    void corruptFreeListPtrAtTheEndOfStorage()
    {
        pFreeList = reinterpret_cast<Node*>(storage + sizeof(storage));
    }

    void corruptFreeListPtrAfterStorage()
    {
        pFreeList = reinterpret_cast<Node*>(storage + sizeof(storage) + 1U);
    }

    void corruptFreeListPtrLessThanCell()
    {
        pFreeList = reinterpret_cast<Node*>(storage + 1U);
    }

    void corruptFreeListPtrMoreThanCell()
    {
        pFreeList = reinterpret_cast<Node*>(storage + sizeof(Node) + 1U);
    }

    void corruptNextPtrBeforeStorage()
    {
        pFreeList->body.next = reinterpret_cast<Node*>(storage - 1U);
    }

    void corrupNextPtrAtTheEndOfStorage()
    {
        pFreeList->body.next = reinterpret_cast<Node*>(storage + sizeof(storage));
    }

    void corruptNextListPtrAfterStorage()
    {
        pFreeList->body.next = reinterpret_cast<Node*>(storage + sizeof(storage) + 1U);
    }

    void corruptNextListPtrLessThanCell()
    {
        pFreeList->body.next = reinterpret_cast<Node*>(storage + 1U);
    }

    void corruptNextListPtrMoreThanCell()
    {
        pFreeList->body.next = reinterpret_cast<Node*>(storage + sizeof(Node) + 1U);
    }

    void createInfLoopFromPos(std::size_t pos)
    {
        Node* ptr = pFreeList;
        for (std::size_t i = 1U; i <= pos; ++i)
        {
            ptr = ptr->body.next;
        }
        ptr->body.next = ptr;
    }

    U8 storage[PoolSize * sizeof(Node)];
    Node* pFreeList;
    lsr::impl::PoolMarker<AlignValue> markerFree;
    lsr::impl::PoolMarker<AlignValue> markerBusy;
};

#endif // LUXOFTSAFERENDERER_POOLCORRUPTER_H
