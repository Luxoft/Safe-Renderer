#ifndef POPULUSSC_POOLCORRUPTER_H
#define POPULUSSC_POOLCORRUPTER_H

/******************************************************************************
**
**   File:        PoolCorrupter.h
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
            U8 data[psc::impl::NodeDataLength<sizeof(T), AlignValue>::value];
            Node* next;
        };
        NodeBody body;
        psc::impl::PoolMarker<AlignValue> marker;
    };

    void corruptStorage()
    {
        const std::size_t cellSize = sizeof(Node);
        const std::size_t storageSize = sizeof(storage);

        memset(storage + storageSize/2, 0xEE, cellSize);
    }

    void corruptFreeMarker()
    {
        markerFree = psc::impl::PoolMarker<AlignValue>(0xEE);
    }

    void corruptBusyMarker()
    {
        markerBusy = psc::impl::PoolMarker<AlignValue>(0xEE);
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
    psc::impl::PoolMarker<AlignValue> markerFree;
    psc::impl::PoolMarker<AlignValue> markerBusy;
};

#endif // POPULUSSC_POOLCORRUPTER_H
