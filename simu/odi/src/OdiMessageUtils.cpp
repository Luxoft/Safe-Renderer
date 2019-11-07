/******************************************************************************
**
**   File:        OdiMessageUtils.cpp
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
