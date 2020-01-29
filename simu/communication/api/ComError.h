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
