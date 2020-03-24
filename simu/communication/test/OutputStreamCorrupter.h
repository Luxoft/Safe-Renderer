#ifndef OUTPUTSTREAMCORRUPTER_H
#define OUTPUTSTREAMCORRUPTER_H

/******************************************************************************
**
**   File:        OutputStreamCorrupter.h
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

#include <stdint.h>

#include "ComError.h"


/**
 * Class is needed to corrupt internal state of OutputStream object.
 * It should have exactly the same sequence of fields and field types as they are
 * in OutputStream class.
 *
 * Example of usage:
 * lsr::OutputStream stream(...);
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
    void setError(lsr::ComError error);

private:
    const uint8_t* m_buffer;
    uint32_t m_bufferSize;
    uint32_t m_pos;
    lsr::ComError m_error;
};

inline void OutputStreamCorrupter::setBufferSize(uint32_t size)
{
    m_bufferSize = size;
}

inline void OutputStreamCorrupter::setPos(uint32_t pos)
{
    m_pos = pos;
}

inline void OutputStreamCorrupter::setError(lsr::ComError error)
{
    m_error = error;
}

#endif // OUTPUTSTREAMCORRUPTER_H
