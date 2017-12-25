#ifndef POPULUSSC_DATARESPONSEMESSAGE_H
#define POPULUSSC_DATARESPONSEMESSAGE_H

/******************************************************************************
**
**   File:        DataResponseMessage.h
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

#include "OdiTypes.h"

#include <InputStream.h>
#include <OutputStream.h>
#include <PscTypes.h>
#include <PSCError.h>
#include <ddh_defs.h>

namespace psc
{

class DataResponseMessage;

InputStream& operator>>(InputStream& stream, DataResponseMessage& msg);
OutputStream& operator<<(OutputStream& stream, const DataResponseMessage& msg);

/**
 * The message holds the dynamic data as a response to some request.
 * It holds the ID of the data, its type, value, flag of correctness, and the FU ID which
 * delivers this information.
 * Serialization and deserialization functions should be implemented as friend functions:
 * @c InputStream& operator>>(InputStream&, AliveMessage&) and
 * @c OutputStream& operator<<(OutputStream&, const AliveMessage&)
 */
class DataResponseMessage
{
public:
    explicit DataResponseMessage();

    static DataResponseMessage fromStream(InputStream& stream);

    U16 getSize() const;

    MessageTypes::Val getType() const;

    void setDataId(const DataId id);
    void setDataType(const DynamicDataTypeEnumeration type);
    void setFuId(const FUClassId id);
    void setInvalidFlag(const bool isInvalid);
    void setDataValue(const U32 value);

    DataId getDataId() const;
    DynamicDataTypeEnumeration getDataType() const;
    FUClassId getFuId() const;
    bool getInvalidFlag() const;
    U32 getDataValue() const;

private:
    friend InputStream& operator>>(InputStream& stream, DataResponseMessage& msg);
    friend OutputStream& operator<<(OutputStream& stream, const DataResponseMessage& msg);

    DataId m_dataId;
    DynamicDataTypeEnumeration m_dataType;
    FUClassId m_fuId;
    bool m_invalidFlag;
    U32 m_value;
};

inline MessageTypes::Val DataResponseMessage::getType() const
{
    return MessageTypes::ODI;
}

inline DataId DataResponseMessage::getDataId() const
{
    return m_dataId;
}

inline DynamicDataTypeEnumeration DataResponseMessage::getDataType() const
{
    return m_dataType;
}

inline U16 DataResponseMessage::getFuId() const
{
    return m_fuId;
}

inline bool DataResponseMessage::getInvalidFlag() const
{
    return m_invalidFlag;
}

inline U32 DataResponseMessage::getDataValue() const
{
    return m_value;
}

inline void DataResponseMessage::setDataId(const DataId id)
{
    m_dataId = id;
}

inline void DataResponseMessage::setDataType(const DynamicDataTypeEnumeration type)
{
    m_dataType = type;
}

inline void DataResponseMessage::setFuId(const FUClassId id)
{
    m_fuId = id;
}

inline void DataResponseMessage::setInvalidFlag(const bool isInvalid)
{
    m_invalidFlag = isInvalid;
}

inline void DataResponseMessage::setDataValue(const U32 value)
{
    m_value = value;
}

} // namespace psc

#endif // POPULUSSC_DATARESPONSEMESSAGE_H
