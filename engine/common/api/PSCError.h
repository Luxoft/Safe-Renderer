#ifndef POPULUSSC_PSC_ERROR_H
#define POPULUSSC_PSC_ERROR_H

/******************************************************************************
**
**   File:        PSCError.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

/**
 * List of errors in the Populus Safety Critical library.
 * This list is sorted in such way:
 * the most heaviest errors are in the end of the list.
 */
typedef enum
{
    PSC_NO_ERROR = 0,
    PSC_UNKNOWN_ERROR,
    PSC_PGW_INVALID_MSG,
    PSC_SESSION_TOO_MANY_RECEIVERS,
    PSC_SESSION_RECEIVER_ALREADY_REGISTERED,
    PSC_SESSION_UNDEFINED_RECEIVER,
    PSC_SESSION_UNDEFINED_TRANSMITTER,
    PSC_ODI_NOT_ENOUGH_BUFFER_SIZE,
    PSC_ODI_NOT_ENOUGH_MESSAGE_SIZE,
    PSC_ODI_INVALID_FIELD_IN_MSG,
    PSC_COMM_NOT_ENOUGH_BUFFER_SIZE,
    PSC_COMM_NOT_ENOUGH_INPUT_DATA,
    PSC_COMM_INVALID_FIELD_IN_MSG,
    PSC_DH_INVALID_MESSAGE_TYPE,
    PSC_DH_INVALID_DATA_ID,
    PSC_INVALID_PARAMETER,
    PSC_POOL_INVALID_OBJECT,
    PSC_DATASTATUS_NOT_AVAIABLE,
    PSC_DATASTATUS_INVALID,
    PSC_DATASTATUS_INCONSISTENT,
    PSC_POOL_IS_FULL,
    PSC_PGW_BUFFER_OVERFLOW,
    PSC_POOL_DOUBLE_DELETE,
    PSC_POOL_IS_CORRUPTED,
    PSC_DB_INCONSISTENT,
    PSC_DB_ERROR,
    PSC_PGW_MBOX_INVALID,
    PSC_PGW_MBOX_NOT_INITIALIZED,
    PSC_PGW_NOT_INITIALIZED,
    PSC_DB_DDHBIN_VERSION_MISMATCH,
    PSC_DB_IMGBIN_VERSION_MISMATCH,
} PSCError;

#endif // POPULUSSC_PSC_ERROR_H
