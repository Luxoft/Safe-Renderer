#ifndef LUXOFTSAFERENDERER_COM_ERROR_H
#define LUXOFTSAFERENDERER_COM_ERROR_H

/******************************************************************************
**
**   File:        ComError.h
**   Description: Error codes for communication and odi
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

namespace lsr
{
    enum ComError
    {
        COM_NO_ERROR,
        COM_UNKNOWN_ERROR,
        COM_INVALID_MESSAGE_TYPE,
        COM_NOT_ENOUGH_BUFFER_SIZE,
        COM_INVALID_FIELD_IN_MSG,
        COM_NOT_ENOUGH_INPUT_DATA,
    };
} // namespace lsr

#endif // LUXOFTSAFERENDERER_COM_ERROR_H
