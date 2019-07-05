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
