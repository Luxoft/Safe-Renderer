/******************************************************************************
**
**   File:        OdiMsgHeader.cpp
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

#include <OdiMsgHeader.h>
#include <OdiMessageUtils.h>

namespace lsr
{

OdiMsgHeader::OdiMsgHeader(const DataMessageTypes::Val type)
    : m_type(type)
{
}

OdiMsgHeader::OdiMsgHeader()
    : m_type(DataMessageTypes::UNKNOWN)
{
}

OdiMsgHeader OdiMsgHeader::fromStream(InputStream& stream)
{
    OdiMsgHeader header;
    stream >> header;
    return header;
}

U16 OdiMsgHeader::getSize() const
{
    return static_cast<U16>(sizeof(U8));
}

InputStream& operator>>(InputStream& stream, OdiMsgHeader& header)
{
    U8 tmp = 0U;
    stream >> tmp;
    if (!messageutils::checkOdiMsgType(tmp))
    {
        stream.setError(COM_INVALID_FIELD_IN_MSG);
    }
    else
    {
        header.m_type = static_cast<DataMessageTypes::Val>(tmp);
    }

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const OdiMsgHeader& header)
{
    stream << static_cast<U8>(header.m_type);

    return stream;
}

} // namespace lsr
