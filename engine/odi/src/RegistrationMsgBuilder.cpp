/******************************************************************************
**
**   File:        RegistrationMsgBuilder.cpp
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

#include "RegistrationMsgBuilder.h"

namespace psc
{

RegistrationMsgBuilder::RegistrationMsgBuilder()
    : m_majorVersion(OdiVersion::VERSION_MAJOR)
    , m_minorVersion(OdiVersion::VERSION_MINOR)
    , m_registrationMode(RegistrationMode::UNKNOWN)
    , m_remoteUid(0U)
    , m_fuCount(0U)
{
    memset(m_fuArray, 0, sizeof(m_fuArray));
}

U16 RegistrationMsgBuilder::getSize() const
{
    return static_cast<U16>(registrationmsgconstants::MINIMUM_MSG_SIZE + m_fuCount * sizeof(FUClassId));
}

bool RegistrationMsgBuilder::addFu(const FUClassId fu)
{
    bool result = false;
    if (m_fuCount < registrationmsgconstants::MAX_FU_COUNT)
    {
        m_fuArray[m_fuCount++] = fu;
        result = true;
    }
    return result;
}

OutputStream& operator<<(OutputStream& stream, const RegistrationMsgBuilder& msg)
{
    stream << msg.m_majorVersion;
    stream << msg.m_minorVersion;
    stream << static_cast<U8>(msg.m_registrationMode);
    stream << msg.m_remoteUid;
    stream << msg.m_fuCount;

    for (U8 i = 0; i < msg.m_fuCount; ++i)
    {
        stream << msg.m_fuArray[i];
    }

    return stream;
}

} // namespace psc
