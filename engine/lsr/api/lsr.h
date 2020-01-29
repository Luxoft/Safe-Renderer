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

// coverity[misra_cpp_2008_rule_18_0_1_violation] <cstdint> cannot be used (C++11)
#include <stdint.h>
// coverity[misra_cpp_2008_rule_18_0_1_violation] <cstddef> cannot be used (C interface)
#include <stddef.h>

#ifdef WIN32
#define LSR_API extern __declspec(dllexport)
#else
#define LSR_API extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif

// coverity[misra_cpp_2008_rule_7_3_1_violation] C interface
typedef int32_t LSRBoolean;
// coverity[misra_cpp_2008_rule_7_3_1_violation] C interface
typedef struct lsr_engine_t* LSREngine;

#define LSR_FALSE 0
#define LSR_TRUE 1

typedef uint32_t LSRFUDataId;

// coverity[misra_cpp_2008_rule_16_2_1_violation] C interface
// coverity[misra_cpp_2008_rule_16_2_2_violation] C interface
#define LSR_NO_ERROR 0U
// coverity[misra_cpp_2008_rule_16_2_1_violation] C interface
// coverity[misra_cpp_2008_rule_16_2_2_violation] C interface
#define LSR_UNKNOWN_ERROR 0xffffffffU
typedef uint32_t LSRError;

// coverity[misra_cpp_2008_rule_7_3_1_violation] C interface
typedef enum
{
    LSR_DATA_STATUS_NOT_AVAILABLE = 0,
    LSR_DATA_STATUS_VALID,
    LSR_DATA_STATUS_INVALID,
    LSR_DATA_STATUS_INCONSISTENT
} LSRDataStatus;

typedef const void* LSRDatabase;

/**
 * Creates an instance of the LSR safe engine.
 *
 * lsrCreate also checks the database for validity and may set error states accordingly.
 * @warning this function is not re-entrant
 * @param db database configuration all database pointers are required to stay valid during engine lifetime
 * @return Returns an engine instance or NULL if there is not enough memory reserved to create a new one.
 */
LSR_API LSREngine lsrCreate(const LSRDatabase db);

/**
 * Shutdown the engine instance
 * @warning this function is not re-entrant
 */
LSR_API void lsrDelete(const LSREngine engine);

/**
 * Reads data from the engine mailbox and renders updates to the framebuffer output
 * Returns true if the framebuffer was refreshed, false otherwise. Returning false not necessarily means an error.
 */
LSR_API LSRBoolean lsrRender(const LSREngine engine);

/**
 * Verifies the framebuffer output with the expected content
 * Returns true if the verification was successful, false otherwise.
 */
LSR_API LSRBoolean lsrVerify(const LSREngine engine);

/**
 * Modifies a boolean data of a functional unit (FU) interface
 * This call will be only successful if the given fuDataId is part of a FU interface and refers to a boolean data
 * @param engine lsr engine instance
 * @param fuDataId identifies the data entry of a FU interface (see generated database header)
 * @param value new value to set
 * @param LSR_TRUE on success, LSR_FALSE otherwise
 */
LSR_API LSRBoolean lsrSetBoolean(const LSREngine engine, const LSRFUDataId fuDataId, const LSRBoolean value);

/**
 * Modifies an integer data of a functional unit (FU) interface
 * This call will be only successful if the given fuDataId is part of a FU interface and refers to an integer data
 * @param engine lsr engine instance
 * @param fuDataId identifies the data entry of a FU interface (see generated database header)
 * @param value new value to set
 * @param LSR_TRUE on success, LSR_FALSE otherwise
 */
LSR_API LSRBoolean lsrSetInteger(const LSREngine engine, const LSRFUDataId fuDataId, const int32_t value);

/**
 * Returns a boolean data from a functional unit (FU) interface
 * Returns DATA_STATUS_INCONSISTENT if the requested data is not a boolean type or does not exist in the interface
 * @param engine lsr engine instance
 * @param fuDataId identifies the data entry of a FU interface (see generated database header)
 * @param[out] return value, if set to NULL only the DataStatus is returned
 * @return DATA_STATUS_INCONSISTENT if the fuDataId does not exist or is not a boolean, otherwise the actual state
 */
LSR_API LSRDataStatus lsrGetBoolean(const LSREngine engine, const LSRFUDataId fuDataId, LSRBoolean* const value);

/**
 * Returns an integer data from a functional unit (FU) interface
 * Returns DATA_STATUS_INCONSISTENT if the requested data is not am integer type or does not exist in the interface
 * @param engine lsr engine instance
 * @param fuDataId identifies the data entry of a FU interface (see generated database header)
 * @param[out] return value, if set to NULL only the DataStatus is returned
 * @return DATA_STATUS_INCONSISTENT if the fuDataId does not exist or is not a boolean, otherwise the actual state
 */
LSR_API LSRDataStatus lsrGetInteger(const LSREngine engine, const LSRFUDataId fuDataId, int32_t* const value);

/**
 * Returns the value of the error flag.
 *
 * Each detectable error is assigned a numeric code and symbolic name. When an error occurs, the error flag is set
 * to the appropriate error code value. No other errors are recorded until lsrGetError is called, the error code is returned,
 * and the flag is reset to LSR_NO_ERROR. If a call to lsrGetError returns LSR_NO_ERROR, there has been no detectable error
 * since the last call to lsrGetError, or since the LSR was initialized.
 *
 * To allow for distributed implementations, there may be several error flags. If any single error flag has recorded an error,
 * the value of that flag is returned and that flag is reset to LSR_NO_ERROR when lsrGetError is called.
 * If more than one flag has recorded an error, lsrGetError returns and clears an arbitrary error flag value.
 * Thus, lsrGetError should always be called in a loop, until it returns LSR_NO_ERROR, if all error flags are to be reset.
 *
 * Initially, all error flags are set to LSR_NO_ERROR.
 *
 * @note lsrGetError() will also report errors from the gil.h
 */
LSR_API LSRError lsrGetError(const LSREngine engine);

#ifdef __cplusplus
}
#endif

#endif // LSR_H
