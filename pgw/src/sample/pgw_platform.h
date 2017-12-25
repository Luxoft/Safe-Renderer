#ifndef POPULUS_PGW_PLATFORM_H
#define POPULUS_PGW_PLATFORM_H

/******************************************************************************
**
**   File:        pgw_platform.h
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

#include "pgw.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
    #include <windows.h>
    typedef HANDLE pgw_mutex_t;
    typedef int pgw_mutex_id_t;
    typedef HANDLE pgw_event_t;
    typedef int pgw_event_id_t;
#elif defined(LINUX)
    #include <pthread.h>
    typedef pthread_mutex_t pgw_mutex_t;
    typedef int pgw_mutex_id_t;
    typedef struct
    {
        pthread_mutex_t mutex;
        pthread_cond_t cond;
        uint8_t created;
        uint8_t signalled;
    } pgw_event_t;
    typedef int pgw_event_id_t;
#elif defined(UCOS)
    typedef void* pgw_mutex_t;
    typedef uint32_t pgw_mutex_id_t;
    typedef void* pgw_event_t;
    typedef uint32_t pgw_event_id_t;
#elif ITRON
    typedef uint32_t pgw_mutex_t;
    typedef uint32_t pgw_mutex_id_t;
    typedef uint32_t pgw_event_t;
    typedef uint32_t pgw_event_id_t;
#else
#error "pgw: platform not supported"
#endif

typedef enum
{
    pgw_false = 0,
    pgw_true = 1
} pgw_bool_t;

/**
 * Creates a mutex.
 * @param[out] mutex Mutex object created by the function.
 * @param id   Mutex id (needed by some platforms, which only have static mutex objects).
 */
void pgw_mutex_create(pgw_mutex_t* mutex, pgw_mutex_id_t id);

/**
 * Locks the provided mutex.
 * @param mutex
 */
pgw_bool_t pgw_mutex_lock(pgw_mutex_t* mutex);

/**
 * Unlocks the provided mutex.
 * @param mutex
 */
pgw_bool_t pgw_mutex_unlock(pgw_mutex_t* mutex);

/**
 * Deletes the provided mutex object.
 * @param mutex
 */
void pgw_mutex_destroy(pgw_mutex_t* mutex);

/**
 * Creates an event which can be used for synchronization between threads.
 * @param[out] ev Event created by the function.
 * @param id Event id (needed by some platforms, which only have static event objects).
 */
void pgw_event_create(pgw_event_t* ev, pgw_event_id_t id);

/**
 * Deletes the provided event object.
 * @param ev Event to delete.
 */
void pgw_event_destroy(pgw_event_t* ev);

/**
 * Sets the given event to active state. Waiting task will be notified.
 * @param ev Event to set.
 */
void pgw_event_set(pgw_event_t* ev);

/**
 * Clears the given event.
 * @param ev Event to clear.
 */
void pgw_event_clear(pgw_event_t* ev);

/**
 * Infinitely waits for the given event until the sender thread sets the event.
 * @param ev Event to wait for.
 */
void pgw_event_wait(pgw_event_t* ev);

/**
 * Waits for the given event until either the event is set or the timeout occurs.
 * @param ev Event to wait for.
 * @param msTimeout Timeout in milliseconds.
 */
void pgw_event_wait_timeout(pgw_event_t* ev, uint32_t msTimeout);

/**
 * Assigns one event object to the other
 * (events might be structures for some platforms).
 * @param to   Destination event object.
 * @param from Source event object.
 */
void pgw_event_assign(pgw_event_t* to, pgw_event_t* from);

#ifdef __cplusplus
}
#endif

#endif //POPULUS_PGW_PLATFORM_H
