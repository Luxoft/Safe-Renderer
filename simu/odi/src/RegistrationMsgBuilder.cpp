/******************************************************************************
**
**   File:        RegistrationMsgBuilder.cpp
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

#include "RegistrationMsgBuilder.h"

namespace lsr
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
    const U32 byteCount = (m_fuCount * sizeof(FUClassId));
    return static_cast<U16>(registrationmsgconstants::MINIMUM_MSG_SIZE + byteCount);
}

bool RegistrationMsgBuilder::addFu(const FUClassId fu)
{
    bool result = false;
    if (m_fuCount < registrationmsgconstants::MAX_FU_COUNT)
    {
        m_fuArray[m_fuCount] = fu;
        ++m_fuCount;
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

    for (U8 i = 0U; i < msg.m_fuCount; ++i)
    {
        stream << msg.m_fuArray[i];
    }

    return stream;
}

} // namespace lsr
