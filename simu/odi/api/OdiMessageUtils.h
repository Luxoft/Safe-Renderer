#ifndef LUXOFTSAFERENDERER_ODIMESSAGEUTILS_H
#define LUXOFTSAFERENDERER_ODIMESSAGEUTILS_H

/******************************************************************************
**
**   File:        OdiMessageUtils.h
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

#include "LsrTypes.h"

namespace lsr
{
namespace messageutils
{

/**
 * Function checks if the input type corresponds to the value of @c MessageTypes.
 * @param[in] type the type which has to be checked.
 * @return @c true if the type corresponds to the value, @c false otherwise.
 */
bool checkMsgType(const U8 type);

/**
 * Function checks if the input type corresponds to the value of @c DataMessageTypes.
 * @param[in] type the type which has to be checked.
 * @return @c true if the type corresponds to the value, @c false otherwise.
 */
bool checkOdiMsgType(const U8 type);

/**
 * Function checks if the input mode corresponds to the value of @c RegistrationMode.
 * @param[in] mode the mode which has to be checked.
 * @return @c true if the mode corresponds to the value, @c false otherwise.
 */
bool checkRegistrationMode(const U8 mode);

}
}

#endif // LUXOFTSAFERENDERER_ODIMESSAGEUTILS_H
