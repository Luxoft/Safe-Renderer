/******************************************************************************
**
**   File:        MessageHeader.cpp
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
