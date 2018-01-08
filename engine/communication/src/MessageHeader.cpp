/******************************************************************************
**
**   File:        MessageHeader.cpp
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

#include "MessageHeader.h"

#include <OdiMessageUtils.h>

namespace psc
{

MessageHeader::MessageHeader(MessageTypes::Val msgType, U32 dataSize)
    : m_type(msgType)
    , m_dataSize(dataSize)
{
}

MessageHeader::MessageHeader()
    : m_type(MessageTypes::UNKNOWN)
    , m_dataSize(0u)
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
    U8 tmpType = 0u;
    stream >> tmpType;
    if (!messageutils::checkMsgType(tmpType))
    {
        stream.setError(PSC_COMM_INVALID_FIELD_IN_MSG);
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

} // namespace psc
