/******************************************************************************
**
**   File:        pgw_platform_win32.c
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

#include "pgw_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

void pgw_mutex_create(pgw_mutex_t* mutex, pgw_mutex_id_t id)
{
    *mutex = CreateMutex(NULL, FALSE, NULL);
}

pgw_bool_t pgw_mutex_lock(pgw_mutex_t* mutex)
{
    WaitForSingleObject(*mutex, INFINITE);
    return pgw_true;
}

pgw_bool_t pgw_mutex_unlock(pgw_mutex_t* mutex)
{
    ReleaseMutex(*mutex);
    return pgw_true;
}

void pgw_mutex_destroy(pgw_mutex_t* mutex)
{
    CloseHandle(*mutex);
}

void pgw_event_create(pgw_event_t* ev, pgw_event_id_t id)
{
    *ev = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void pgw_event_destroy(pgw_event_t* ev)
{
}

void pgw_event_set(pgw_event_t* ev)
{
    SetEvent(*ev);
}

void pgw_event_clear(pgw_event_t* ev)
{
    ResetEvent(*ev);
}

void pgw_event_wait(pgw_event_t* ev)
{
    WaitForSingleObject(*ev, INFINITE);
}

void pgw_event_wait_timeout(pgw_event_t* ev, uint32_t msTimeout)
{
    WaitForSingleObject(*ev, msTimeout);
}

void pgw_event_assign(pgw_event_t* to, pgw_event_t* from)
{
    *to = *from;
}

uint32_t pgwGetMonotonicTime(void)
{
    return timeGetTime();
}

#ifdef __cplusplus
}
#endif
