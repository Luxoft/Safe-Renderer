#ifndef LUXOFTSAFERENDERER_LSR_ERROR_H
#define LUXOFTSAFERENDERER_LSR_ERROR_H

/******************************************************************************
**
**   File:        LSRError.h
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

/**
 * List of errors in the LSR Critical library.
 * This list is sorted in such way:
 * the most heaviest errors are in the end of the list.
 */
typedef enum
{
    LSR_NO_ERROR = 0,
    LSR_UNKNOWN_ERROR,
    LSR_PIL_INVALID_MSG,
    LSR_SESSION_TOO_MANY_RECEIVERS,
    LSR_SESSION_RECEIVER_ALREADY_REGISTERED,
    LSR_SESSION_UNDEFINED_RECEIVER, // 5
    LSR_SESSION_UNDEFINED_TRANSMITTER,
    LSR_ODI_NOT_ENOUGH_BUFFER_SIZE,
    LSR_ODI_NOT_ENOUGH_MESSAGE_SIZE,
    LSR_ODI_INVALID_FIELD_IN_MSG,
    LSR_COMM_NOT_ENOUGH_BUFFER_SIZE, // 10
    LSR_COMM_NOT_ENOUGH_INPUT_DATA,
    LSR_COMM_INVALID_FIELD_IN_MSG,
    LSR_DH_INVALID_MESSAGE_TYPE,
    LSR_DH_INVALID_DATA_ID,
    LSR_INVALID_PARAMETER, //15
    LSR_POOL_INVALID_OBJECT,
    LSR_DATASTATUS_NOT_AVAIABLE,
    LSR_DATASTATUS_INVALID,
    LSR_DATASTATUS_INCONSISTENT,
    LSR_CRITICAL_ERRORS, //20  All which are ore than this should emit program abort
    LSR_POOL_IS_FULL,
    LSR_PIL_BUFFER_OVERFLOW,
    LSR_POOL_DOUBLE_DELETE,
    LSR_POOL_IS_CORRUPTED,
    LSR_DB_INCONSISTENT, //25
    LSR_DB_ERROR,
    LSR_PIL_MBOX_INVALID,
    LSR_PIL_MBOX_NOT_INITIALIZED,
    LSR_PIL_NOT_INITIALIZED,
    LSR_DB_DDHBIN_VERSION_MISMATCH, //30
    LSR_DB_IMGBIN_VERSION_MISMATCH,
    LSR_DB_DDHBIN_EMPTY,
} LSRError;

#endif // LUXOFTSAFERENDERER_LSR_ERROR_H
