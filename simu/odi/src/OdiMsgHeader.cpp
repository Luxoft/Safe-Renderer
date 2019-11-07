/******************************************************************************
**
**   File:        OdiMsgHeader.cpp
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
        stream.setError(LSR_COMM_INVALID_FIELD_IN_MSG);
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
