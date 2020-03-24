/******************************************************************************
**
**   File:        OdiMessageUtils.cpp
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

#include "OdiMessageUtils.h"
#include "OdiTypes.h"

namespace lsr
{
namespace messageutils
{

bool checkMsgType(const U8 type)
{
    bool ret = false;
    switch (type)
    {
    case MessageTypes::REGISTRATION:
    case MessageTypes::ODI:
    case MessageTypes::ALIVE:
        ret = true;
        break;
    default:
        break;
    }
    return ret;
}

bool checkOdiMsgType(const U8 type)
{
    bool ret = false;
    switch (type)
    {
    case DataMessageTypes::DYN_DATA_RESP:
    case DataMessageTypes::EVENT:
    case DataMessageTypes::INDICATION:
        ret = true;
    default:
        break;
    }
    return ret;
}

bool checkRegistrationMode(const U8 mode)
{
    return ((mode >= static_cast<U8>(RegistrationMode::REPLACE)) &&
            (mode < static_cast<U8>(RegistrationMode::LAST)));
}

} // namespace messageutils
} // namespace lsr
