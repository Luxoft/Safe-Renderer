#ifndef PSC_H
#define PSC_H

/******************************************************************************
**
**   File:        psc.h
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

#include <stdint.h>
#include <stddef.h>
#include <pgw.h>
#include <PSCError.h>

#ifdef WIN32
#define PSC_API extern __declspec(dllexport)
#else
#define PSC_API extern
#endif

#ifdef __cplusplus
extern "C"
{
#endif

typedef int PSCBoolean;
typedef void* PSCEngine;

#define PSC_FALSE 0
#define PSC_TRUE 1

typedef struct PSCDatabase
{
    const void* ddhbin;
    const size_t ddhbinSize;
    const void* imgbin;
    const size_t imgbinSize;
} PSCDatabase;

/**
 * Creates an instance of the populus safe engine.
 *
 * pscCreate also checks the database for validity and may set error states accordingly.
 * @warning this function is not re-entrant
 * @param db database configuration all database pointers are required to stay valid during engine lifetime
 * @param mailbox pgw mailbox for receiving incoming ODI messages
 * @return Returns an engine instance or NULL if there is not enough memory reserved to create a new one.
 */
PSC_API PSCEngine pscCreate(const PSCDatabase* db, PGWMailbox mailbox);

/**
 * Shutdown the engine instance
 * @warning this function is not re-entrant
 */
PSC_API PSCError pscDelete(PSCEngine engine);

/**
 * Reads data from the engine mailbox and renders updates to the framebuffer output
 * Returns true if the framebuffer was refreshed, false otherwise. Returning false not necessarily means an error.
 */
PSC_API PSCBoolean pscRender(PSCEngine engine);

/**
 * Verifies the framebuffer output with the expected content
 * Returns true if the verification was successful, false otherwise.
 */
PSC_API PSCBoolean pscVerify(PSCEngine engine);

/**
 * Returns the value of the error flag.
 *
 * Each detectable error is assigned a numeric code and symbolic name. When an error occurs, the error flag is set
 * to the appropriate error code value. No other errors are recorded until pglGetError is called, the error code is returned,
 * and the flag is reset to PSC_NO_ERROR. If a call to pglGetError returns PSC_NO_ERROR, there has been no detectable error
 * since the last call to pglGetError, or since the GL was initialized.
 *
 * To allow for distributed implementations, there may be several error flags. If any single error flag has recorded an error,
 * the value of that flag is returned and that flag is reset to PSC_NO_ERROR when pglGetError is called.
 * If more than one flag has recorded an error, pglGetError returns and clears an arbitrary error flag value.
 * Thus, pglGetError should always be called in a loop, until it returns PSC_NO_ERROR, if all error flags are to be reset.
 *
 * Initially, all error flags are set to PSC_NO_ERROR.
 */
PSC_API PSCError pscGetError(PSCEngine engine);

#ifdef __cplusplus
}
#endif

#endif // PSC_H
