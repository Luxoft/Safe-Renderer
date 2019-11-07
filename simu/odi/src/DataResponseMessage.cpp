/******************************************************************************
**
**   File:        DataResponseMessage.cpp
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

#include "DataResponseMessage.h"

namespace lsr
{

DataResponseMessage::DataResponseMessage()
    : m_dataId(0U)
    , m_dataType(DATATYPE_ENUM_SIZE)
    , m_fuId(0U)
    , m_invalidFlag(true)
    , m_value(0U)
{
}

DataResponseMessage DataResponseMessage::fromStream(InputStream& stream)
{
    DataResponseMessage msg;
    stream >> msg;
    return msg;
}

U16 DataResponseMessage::getSize() const
{
    return static_cast<U16>(sizeof(m_dataId) +
        sizeof(m_fuId) + sizeof(m_invalidFlag) + sizeof(m_value) +
         + sizeof(U8) /* size of data type*/);
}

InputStream& operator>>(InputStream& stream, DataResponseMessage& msg)
{
    stream >> msg.m_fuId;
    stream >> msg.m_dataId;

    U8 tmp = 0U;
    stream >> tmp;
    msg.m_dataType = static_cast<DynamicDataTypeEnumeration>(tmp);
    stream >> msg.m_invalidFlag;
    stream >> msg.m_value;

    return stream;
}

OutputStream& operator<<(OutputStream& stream, const DataResponseMessage& msg)
{
    stream << msg.m_fuId;
    stream << msg.m_dataId;
    stream << static_cast<U8>(msg.m_dataType);
    stream << msg.m_invalidFlag;
    stream << msg.m_value;

    return stream;
}

} // namespace lsr
