/******************************************************************************
**
**   File:        MessageHeader.cpp
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

#include "MessageHeader.h"

#include <OdiMessageUtils.h>

namespace lsr
{

MessageHeader::MessageHeader(const MessageTypes::Val msgType, const U32 dataSize)
    : m_type(msgType)
    , m_dataSize(dataSize)
{
}

MessageHeader::MessageHeader()
    : m_type(MessageTypes::UNKNOWN)
    , m_dataSize(0U)
{
}

MessageHeader MessageHeader::fromStream(InputStream& stream)
{
    MessageHeader header;
    stream >> header;
    return header;
}

InputStream& operator>>(InputStream& stream, MessageHeader& header)
{
    U8 tmpType = 0U;
    stream >> tmpType;
    if (!messageutils::checkMsgType(tmpType))
    {
        stream.setError(COM_INVALID_FIELD_IN_MSG);
    }
    else
    {
        header.m_type = static_cast<MessageTypes::Val>(tmpType);
        stream >> header.m_dataSize;
    }

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const MessageHeader& header)
{
    stream << static_cast<U8>(header.m_type);
    stream << header.m_dataSize;

    return stream;
}

} // namespace lsr
