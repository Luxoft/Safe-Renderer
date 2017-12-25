#ifndef PGW_H
#define PGW_H

/******************************************************************************
**
**   File:        pgw.h
**   Description: Populus Gateway Library
**                Provides basic platform / OS dependent features for the
**                Populus Engine.
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


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
typedef unsigned char PGWMailbox; ///< opaque handle with subsequent numbers

const PGWMailbox PGW_UNKNOWN_MAILBOX = 255;

typedef enum
{
    PGW_NO_ERROR = 0,
    PGW_NOT_INITIALIZED,
    PGW_MBOX_NOT_INITIALIZED,
    PGW_MBOX_INVALID,
    PGW_BUFFER_OVERFLOW,
    PGW_INVALID_MSG,
    PGW_UNKNOWN_ERROR,
} PGWError;

/**
 * @brief Initialize the pgw library.
 * @note Must be called once before any other library function.
 */
void pgwInit(void);

/**
* @brief Deinitialize the pgw library.
*/
void pgwClose(void);

/**
 * @brief Creates a new mailbox.
 * @param mbox Unique mailbox handle.
 * @note Must be called once before the mailbox is used.
 * @note Must be called by the receiving task.
 * @return PGWError::PSC_PGW_NO_ERROR for success, error code otherwise.
 */
PGWError pgwMailboxInit(PGWMailbox mbox);

/**
 * @brief Gets next message from the given mailbox.
 * Data is kept in the message queue, it needs to be explicitly removed with @c pgwMailboxPop.
 * @param mbox Unique mailbox handle.
 * @param[out] sender Mailbox handle where responses should be written to.
 * @param[out] data ODI message.
 * @param[out] dataLen Data size in bytes.
 * @return PGWError::PSC_PGW_NO_ERROR for success, error code otherwise.
 */
PGWError pgwMailboxGet(PGWMailbox mbox, PGWMailbox *sender, uint8_t** data, uint32_t *dataLen);

/**
 * @brief Removes next message from the mailbox.
 * @param mbox Unique mailbox handle.
 * @return PGWError::PSC_PGW_NO_ERROR for success, error code otherwise.
 */
PGWError pgwMailboxPop(PGWMailbox mbox);

/**
 * @brief Writes a message to the given mailbox.
 * @param mbox Unique mailbox handle.
 * @param sender Mailbox handle where responses should be written to.
 * @param data Payload.
 * @param dataLen Data size in bytes.
 * @return PGWError::PSC_PGW_NO_ERROR for success, error code otherwise.
 */
PGWError pgwMailboxWrite(PGWMailbox mbox, PGWMailbox sender, const uint8_t* data, uint32_t dataLen);

/**
 * @brief Waits until data is available on the given mailbox or timeout occurred.
 * @param mbox Mailbox handle.
 * @param timeMs Timeout in milliseconds.
 * @return PGWError::PSC_PGW_NO_ERROR for success, error code otherwise.
 */
PGWError pgwMailboxWait(PGWMailbox mbox, uint32_t timeMs);

/**
 * @brief returns the system's monotonic system time in milliseconds
 * @note There will be an overflow every 49 days
 * @return time in milliseconds
 */
uint32_t pgwGetMonotonicTime(void);

/**
 * @brief Logs an engine error for debugging
 * Engine reports occurring errors both to this function and to its internal error state.
 * The textual information is only available here
 * @param errorCode identifier of the occurred error
 * @param msg The error message
 */
void pgwError(uint32_t errorCode, const char* msg);

/**
 * @brief Function to report failed assertions.
 * @param msg Error message.
 * @param file Source file name where assertion failed.
 * @param lineNo Line number where assertion failed.
 */
void pgwAssert(const char* msg, const char* file, int lineNo);

#ifdef __cplusplus
}
#endif

#endif //PGW_H
