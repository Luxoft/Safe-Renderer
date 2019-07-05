/******************************************************************************
**
**   File:        pil_platform_win32.c
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

#include "pil_platform.h"

#ifdef __cplusplus
extern "C" {
#endif

void pil_mutex_create(pil_mutex_t* mutex, pil_mutex_id_t id)
{
    *mutex = CreateMutex(NULL, FALSE, NULL);
}

pil_bool_t pil_mutex_lock(pil_mutex_t* mutex)
{
    WaitForSingleObject(*mutex, INFINITE);
    return pil_true;
}

pil_bool_t pil_mutex_unlock(pil_mutex_t* mutex)
{
    ReleaseMutex(*mutex);
    return pil_true;
}

void pil_mutex_destroy(pil_mutex_t* mutex)
{
    CloseHandle(*mutex);
}

void pil_event_create(pil_event_t* ev, pil_event_id_t id)
{
    *ev = CreateEvent(NULL, TRUE, FALSE, NULL);
}

void pil_event_destroy(pil_event_t* ev)
{
}

void pil_event_set(pil_event_t* ev)
{
    SetEvent(*ev);
}

void pil_event_clear(pil_event_t* ev)
{
    ResetEvent(*ev);
}

void pil_event_wait(pil_event_t* ev)
{
    WaitForSingleObject(*ev, INFINITE);
}

void pil_event_wait_timeout(pil_event_t* ev, uint32_t msTimeout)
{
    WaitForSingleObject(*ev, msTimeout);
}

void pil_event_assign(pil_event_t* to, pil_event_t* from)
{
    *to = *from;
}

uint32_t pilGetMonotonicTime(void)
{
    return timeGetTime();
}

#ifdef __cplusplus
}
#endif
