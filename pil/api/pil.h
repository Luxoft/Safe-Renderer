#ifndef PIL_H
#define PIL_H

/******************************************************************************
**
**   File:        pil.h
**   Description: Platform Interface Laayer for Luxoft Safe Renderer
**                Provides basic platform / OS dependent features for the
**                LSR Engine.
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


#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
typedef unsigned char PILMailbox; ///< opaque handle with subsequent numbers

static const PILMailbox PIL_UNKNOWN_MAILBOX = 255;

typedef enum
{
    PIL_NO_ERROR = 0,
    PIL_NOT_INITIALIZED,
    PIL_MBOX_NOT_INITIALIZED,
    PIL_MBOX_INVALID,
    PIL_BUFFER_OVERFLOW,
    PIL_INVALID_MSG,
    PIL_UNKNOWN_ERROR,
} PILError;

/**
 * @brief Initialize the pil library.
 * @note Must be called once before any other library function.
 */
void pilInit(void);

/**
* @brief Deinitialize the pil library.
*/
void pilClose(void);

/**
 * @brief Creates a new mailbox.
 * @param mbox Unique mailbox handle.
 * @note Must be called once before the mailbox is used.
 * @note Must be called by the receiving task.
 * @return PILError::LSR_PIL_NO_ERROR for success, error code otherwise.
 */
PILError pilMailboxInit(PILMailbox mbox);

/**
 * @brief Gets next message from the given mailbox.
 * Data is kept in the message queue, it needs to be explicitly removed with @c pilMailboxPop.
 * @param mbox Unique mailbox handle.
 * @param[out] sender Mailbox handle where responses should be written to.
 * @param[out] data ODI message.
 * @param[out] dataLen Data size in bytes.
 * @return PILError::LSR_PIL_NO_ERROR for success, error code otherwise.
 */
PILError pilMailboxGet(PILMailbox mbox, PILMailbox *sender, uint8_t** data, uint32_t *dataLen);

/**
 * @brief Removes next message from the mailbox.
 * @param mbox Unique mailbox handle.
 * @return PILError::LSR_PIL_NO_ERROR for success, error code otherwise.
 */
PILError pilMailboxPop(PILMailbox mbox);

/**
 * @brief Writes a message to the given mailbox.
 * @param mbox Unique mailbox handle.
 * @param sender Mailbox handle where responses should be written to.
 * @param data Payload.
 * @param dataLen Data size in bytes.
 * @return PILError::LSR_PIL_NO_ERROR for success, error code otherwise.
 */
PILError pilMailboxWrite(PILMailbox mbox, PILMailbox sender, const uint8_t* data, uint32_t dataLen);

/**
 * @brief Waits until data is available on the given mailbox or timeout occurred.
 * @param mbox Mailbox handle.
 * @param timeMs Timeout in milliseconds.
 * @return PILError::LSR_PIL_NO_ERROR for success, error code otherwise.
 */
PILError pilMailboxWait(PILMailbox mbox, uint32_t timeMs);

/**
 * @brief returns the system's monotonic system time in milliseconds
 * @note There will be an overflow every 49 days
 * @return time in milliseconds
 */
uint32_t pilGetMonotonicTime(void);

/**
 * @brief Logs an engine error for debugging
 * Engine reports occurring errors both to this function and to its internal error state.
 * The textual information is only available here
 * @param errorCode identifier of the occurred error
 * @param msg The error message
 */
void pilError(uint32_t errorCode, const char* msg);

/**
 * @brief Logs an engine trace message for debugging
 * @param msg The trace message
 */
void pilTrace(const char* msg);

/**
 * @brief Function to report failed assertions.
 * @param msg Error message.
 * @param file Source file name where assertion failed.
 * @param lineNo Line number where assertion failed.
 */
void pilAssert(const char* msg, const char* file, int lineNo);

#ifdef __cplusplus
}
#endif

#endif //PIL_H
