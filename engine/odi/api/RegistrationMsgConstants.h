#ifndef POPULUSSC_REGISTRATIONMSGCONSTANTS_H
#define POPULUSSC_REGISTRATIONMSGCONSTANTS_H

/******************************************************************************
**
**   File:        RegistrationMsgConstants.h
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

#include <PscTypes.h>

namespace psc
{
namespace registrationmsgconstants
{

enum Constants
{
    MAX_FU_COUNT = UINT8_MAX,
    MINIMUM_MSG_SIZE = 8
};

} // namespace registrationmsgconstants
} // namespace psc

#endif // POPULUSSC_REGISTRATIONMSGCONSTANTS_H
