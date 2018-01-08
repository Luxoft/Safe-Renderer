#ifndef POPULUSSC_RESOURCEBUFFER_H
#define POPULUSSC_RESOURCEBUFFER_H

/******************************************************************************
**
**   File:        ResourceBuffer.h
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

#include "PscTypes.h"

namespace psc
{

/**
 * @brief Provides random read-only access to a file or pre-allocated memory
 *
 * This class is intended to encapsulate access to resources like images or databases
 * Opening the resources could happen in a platform dependent way (not supported yet).
 */
class ResourceBuffer
{
public:
    ResourceBuffer();
    ResourceBuffer(const void* const buf, const size_t sz);

    const void* getData() const;
    size_t getSize() const;
private:
    const void* m_pBuffer;
    size_t m_size;
};

inline ResourceBuffer::ResourceBuffer()
: m_pBuffer(NULL)
, m_size(0U)
{
}

inline ResourceBuffer::ResourceBuffer(const void* const buf, const size_t sz)
: m_pBuffer(buf)
, m_size(sz)
{
}

inline const void* ResourceBuffer::getData() const
{
    return m_pBuffer;
}

inline size_t ResourceBuffer::getSize() const
{
    return m_size;
}

}

#endif //RESOURCE_BUFFER_H
