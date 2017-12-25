#ifndef OUTPUTSTREAMCORRUPTER_H
#define OUTPUTSTREAMCORRUPTER_H

/******************************************************************************
**
**   File:        OutputStreamCorrupter.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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

#include <stdint.h>

#include "PSCError.h"


/**
 * Class is needed to corrupt internal state of OutputStream object.
 * It should have exactly the same sequence of fields and field types as they are
 * in OutputStream class.
 *
 * Example of usage:
 * psc::OutputStream stream(...);
 * OutputStreamCorrupter* corrupter = reinterpret_cast<OutputStreamCorrupter*>(&stream);
 * corrupter->setPos(someNewPosition);
 * EXPECT_TRUE(stream.isWorkingFine());
 */
class OutputStreamCorrupter
{
public:
    OutputStreamCorrupter(const void* buffer, uint32_t bufferSize);

    void setBufferSize(uint32_t size);
    void setPos(uint32_t pos);
    void setError(PSCError error);

private:
    const uint8_t* m_buffer;
    uint32_t m_bufferSize;
    uint32_t m_pos;
    PSCError m_error;
};

inline void OutputStreamCorrupter::setBufferSize(uint32_t size)
{
    m_bufferSize = size;
}

inline void OutputStreamCorrupter::setPos(uint32_t pos)
{
    m_pos = pos;
}

inline void OutputStreamCorrupter::setError(PSCError error)
{
    m_error = error;
}

#endif // OUTPUTSTREAMCORRUPTER_H
