#ifndef LSR_PIL_PLATFORM_H
#define LSR_PIL_PLATFORM_H

/******************************************************************************
**
**   File:        pil_platform.h
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

#include "pil.h"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32
    #include <windows.h>
    typedef HANDLE pil_mutex_t;
    typedef int pil_mutex_id_t;
    typedef HANDLE pil_event_t;
    typedef int pil_event_id_t;
#elif defined(LINUX)
    #include <pthread.h>
    typedef pthread_mutex_t pil_mutex_t;
    typedef int pil_mutex_id_t;
    typedef struct
    {
        pthread_mutex_t  mutex;
        pthread_cond_t cond;
        uint8_t created;
        uint8_t signalled;
    } pil_event_t;
    typedef int pil_event_id_t;
#elif defined(UCOS)
    typedef void* pil_mutex_t;
    typedef uint32_t pil_mutex_id_t;
    typedef void* pil_event_t;
    typedef uint32_t pil_event_id_t;
#elif defined(ARP)
    typedef void* pil_mutex_t;
    typedef uint32_t pil_mutex_id_t;
    typedef void* pil_event_t;
    typedef uint32_t pil_event_id_t;
#elif ITRON
    typedef uint32_t pil_mutex_t;
    typedef uint32_t pil_mutex_id_t;
    typedef uint32_t pil_event_t;
    typedef uint32_t pil_event_id_t;
#else
#error "pil: platform not supported"
#endif

typedef enum
{
    pil_false = 0,
    pil_true = 1
} pil_bool_t;

/**
 * Creates a mutex.
 * @param[out] mutex Mutex object created by the function.
 * @param id   Mutex id (needed by some platforms, which only have static mutex objects).
 */
void pil_mutex_create(pil_mutex_t* mutex, pil_mutex_id_t id);

/**
 * Locks the provided mutex.
 * @param mutex
 */
pil_bool_t pil_mutex_lock(pil_mutex_t* mutex);

/**
 * Unlocks the provided mutex.
 * @param mutex
 */
pil_bool_t pil_mutex_unlock(pil_mutex_t* mutex);

/**
 * Deletes the provided mutex object.
 * @param mutex
 */
void pil_mutex_destroy(pil_mutex_t* mutex);

/**
 * Creates an event which can be used for synchronization between threads.
 * @param[out] ev Event created by the function.
 * @param id Event id (needed by some platforms, which only have static event objects).
 */
void pil_event_create(pil_event_t* ev, pil_event_id_t id);

/**
 * Deletes the provided event object.
 * @param ev Event to delete.
 */
void pil_event_destroy(pil_event_t* ev);

/**
 * Sets the given event to active state. Waiting task will be notified.
 * @param ev Event to set.
 */
void pil_event_set(pil_event_t* ev);

/**
 * Clears the given event.
 * @param ev Event to clear.
 */
void pil_event_clear(pil_event_t* ev);

/**
 * Infinitely waits for the given event until the sender thread sets the event.
 * @param ev Event to wait for.
 */
void pil_event_wait(pil_event_t* ev);

/**
 * Waits for the given event until either the event is set or the timeout occurs.
 * @param ev Event to wait for.
 * @param msTimeout Timeout in milliseconds.
 */
void pil_event_wait_timeout(pil_event_t* ev, uint32_t msTimeout);

/**
 * Assigns one event object to the other
 * (events might be structures for some platforms).
 * @param to   Destination event object.
 * @param from Source event object.
 */
void pil_event_assign(pil_event_t* to, pil_event_t* from);

#ifdef __cplusplus
}
#endif

#endif //LSR_PIL_PLATFORM_H
