#ifndef LUXOFTSAFERENDERER_RESOURCEBUFFER_H
#define LUXOFTSAFERENDERER_RESOURCEBUFFER_H

/******************************************************************************
**
**   File:        ResourceBuffer.h
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

namespace lsr
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
