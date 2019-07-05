#ifndef LSR_H
#define LSR_H

/******************************************************************************
**
**   File:        lsr.h
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

#include <stdint.h>
#include <stddef.h>
#include <LSRError.h>

#ifdef WIN32
#define LSR_API extern __declspec(dllexport)
#else
#define LSR_API extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef int LSRBoolean;
typedef void* LSREngine;

#define LSR_FALSE 0
#define LSR_TRUE 1

typedef uint32_t LSRDataValue;

typedef uint16_t LSRDataId;
typedef uint16_t LSRFUClassId;
typedef uint16_t LSREventId;
typedef uint8_t LSRIndicationId;

typedef enum LSRDataStatusEnum
{
    LSR_DATA_STATUS_NOT_AVAILABLE = 0,
    LSR_DATA_STATUS_VALID,
    LSR_DATA_STATUS_INVALID,
    LSR_DATA_STATUS_INCONSISTENT
} LSRDataStatusEnum;

typedef enum LSRDataTypeEnum
{
    LSR_DATA_TYPE_INTEGER = 0,
    LSR_DATA_TYPE_DECIMAL,
    LSR_DATA_TYPE_BITMAP_ID,
    LSR_DATA_TYPE_DECIMAL_SHORT,
    LSR_DATA_TYPE_BOOLEAN,
    LSR_DATA_TYPE_ENUM_SIZE
} LSRDataTypeEnum;

typedef struct LSRDatabase
{
    const void* ddhbin;
    const size_t ddhbinSize;
    const void* imgbin;
    const size_t imgbinSize;
} LSRDatabase;

/**
 * Creates an instance of the LSR safe engine.
 *
 * lsrCreate also checks the database for validity and may set error states accordingly.
 * @warning this function is not re-entrant
 * @param db database configuration all database pointers are required to stay valid during engine lifetime
 * @param error error value, which can be rised during creation engine
 * @return Returns an engine instance or NULL if there is not enough memory reserved to create a new one.
 */
LSR_API LSREngine lsrCreate(const LSRDatabase* db, LSRError* error);

/**
 * Shutdown the engine instance
 * @warning this function is not re-entrant
 */
LSR_API LSRError lsrDelete(LSREngine engine);

/**
 * Reads data from the engine mailbox and renders updates to the framebuffer output
 * Returns true if the framebuffer was refreshed, false otherwise. Returning false not necessarily means an error.
 */
LSR_API LSRBoolean lsrRender(LSREngine engine);

/**
 * Verifies the framebuffer output with the expected content
 * Returns true if the verification was successful, false otherwise.
 */
LSR_API LSRBoolean lsrVerify(LSREngine engine);


/**
 * Set new value inside Engine.
 * TODO: fill description
 */
LSR_API LSRBoolean lsrSetValue(LSREngine e,
                               LSRFUClassId fuId,
                               LSRDataId dataId,
                               LSRDataValue value,
                               LSRDataTypeEnum dataType,
                               LSRDataStatusEnum dataStatus);

/**
 * Returns the value of the error flag.
 *
 * Each detectable error is assigned a numeric code and symbolic name. When an error occurs, the error flag is set
 * to the appropriate error code value. No other errors are recorded until gilGetError is called, the error code is returned,
 * and the flag is reset to LSR_NO_ERROR. If a call to gilGetError returns LSR_NO_ERROR, there has been no detectable error
 * since the last call to gilGetError, or since the GL was initialized.
 *
 * To allow for distributed implementations, there may be several error flags. If any single error flag has recorded an error,
 * the value of that flag is returned and that flag is reset to LSR_NO_ERROR when gilGetError is called.
 * If more than one flag has recorded an error, gilGetError returns and clears an arbitrary error flag value.
 * Thus, gilGetError should always be called in a loop, until it returns LSR_NO_ERROR, if all error flags are to be reset.
 *
 * Initially, all error flags are set to LSR_NO_ERROR.
 */
LSR_API LSRError lsrGetError(LSREngine engine);

#ifdef __cplusplus
}
#endif

#endif // LSR_H
