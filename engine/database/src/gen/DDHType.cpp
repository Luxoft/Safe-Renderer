/******************************************************************************
**
**   File:        DDHType.cpp
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

#include "DDHType.h"


namespace psc
{

const char* const DDHType::serializerVersionError = "Data has been serialized with another version of the serializer than what the HMI Engine expects (Expecting Serializer version: 4.41.0)";
const char* const DDHType::schemaVersionError = "Data has been generated from another schema version than the HMI Engine expects (Expecting Schema Version: 4.58.x)";
const char* const DDHType::schemaChecksumError = "Data has been generated from a schema version with another checksum than the HMI Engine expects (Expecting Schema checksum: 0x6ed7ab2d)";

bool DDHType::IsVersionOK() const
{
    return GetSerializerVersion() == SERIALIZER_VERSION &&
           GetSchemaVersion() == SCHEMA_VERSION &&
           GetSchemaChecksum() == SCHEMA_CHECKSUM;
}

const char* DDHType::GetErrorMessage() const
{
    const char* errorMessage = "";
    if (GetSerializerVersion() != SERIALIZER_VERSION)
    {
        errorMessage = serializerVersionError;
    }
    else if (GetSchemaVersion() != SCHEMA_VERSION)
    {
        errorMessage = schemaVersionError;
    }
    else if (GetSchemaChecksum() != SCHEMA_CHECKSUM)
    {
        errorMessage = schemaChecksumError;
    }
    return errorMessage;
}


} // namespace psc
