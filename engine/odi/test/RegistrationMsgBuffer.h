#ifndef POPULUSSC_REGISTRATIONMSGBUFFER_H
#define POPULUSSC_REGISTRATIONMSGBUFFER_H

/******************************************************************************
**
**   File:        RegistrationMsgBuffer.h
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

#include <OdiTypes.h>
#include <PscTypes.h>

class RegistrationMsgBuffer
{
public:
    RegistrationMsgBuffer()
        : m_buffer(NULL)
        , m_bufferSize(1024)
        , m_firstNullFuPos(0u)
    {
        m_buffer = new U8[m_bufferSize];
        memset(m_buffer, 0u, m_bufferSize);

        toDefault();
    }

    ~RegistrationMsgBuffer()
    {
        delete[] m_buffer;
    }

    void toDefault()
    {
        m_buffer[0] = static_cast<U8>(OdiVersion::VERSION_MAJOR);
        m_buffer[1] = static_cast<U8>(OdiVersion::VERSION_MINOR);
        m_buffer[2] = static_cast<U8>(RegistrationMode::UNKNOWN);
        m_buffer[3] = static_cast<U8>(0);
        m_buffer[4] = static_cast<U8>(0);
        m_buffer[5] = static_cast<U8>(0);
        m_buffer[6] = static_cast<U8>(0);
        m_buffer[7] = 0u;

        m_firstNullFuPos = 0u;
    }

    void setRegistrationMode(RegistrationMode::Val mode)
    {
        m_buffer[2] = static_cast<U8>(mode);
    }

    void setRemoteUid(U32 uid)
    {
        m_buffer[3] = static_cast<U8>(uid >> 24);
        m_buffer[4] = static_cast<U8>(uid >> 16);
        m_buffer[5] = static_cast<U8>(uid >> 8);
        m_buffer[6] = static_cast<U8>(uid);
    }

    void setFuCount(U8 count)
    {
        m_buffer[7] = count;
    }

    void addFu(FUClassId fu)
    {
        m_buffer[8 + m_firstNullFuPos++] = static_cast<U8>(fu >> 8);
        m_buffer[8 + m_firstNullFuPos++] = static_cast<U8>(fu);
    }

    inline const U8* getBuffer() const
    {
        return m_buffer;
    }

private:
    U8* m_buffer;
    U16 m_bufferSize;
    U16 m_firstNullFuPos;
};

#endif // POPULUSSC_REGISTRATIONMSGBUFFER_H
