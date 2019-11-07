/******************************************************************************
**
**   File:        AliveMessage.cpp
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

#include "AliveMessage.h"

namespace lsr
{

AliveMessage::AliveMessage(const U8 id)
    : m_id(id)
{
}

AliveMessage::AliveMessage()
    : m_id(0U)
{
}

AliveMessage AliveMessage::fromStream(InputStream& stream)
{
    AliveMessage msg;
    stream >> msg;
    return msg;
}

U16 AliveMessage::getSize() const
{
    return static_cast<U16>(sizeof(m_id));
}

InputStream& operator>>(InputStream& stream, AliveMessage& msg)
{
    stream >> msg.m_id;

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const AliveMessage& msg)
{
    stream << msg.m_id;

    return stream;
}

} // namespace lsr
