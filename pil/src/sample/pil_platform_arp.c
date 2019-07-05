/******************************************************************************
**
**   File:        pil_platform_linux.c
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
#include <sys/time.h>
#include <errno.h>

extern uint32_t getCurRelTimeInMillisec();

#ifdef __cplusplus
extern "C" {
#endif


void pil_mutex_create(pil_mutex_t* mutex, pil_mutex_id_t id)
{
}

pil_bool_t pil_mutex_lock(pil_mutex_t* mutex)
{
    return pil_true;
}

pil_bool_t pil_mutex_unlock(pil_mutex_t* mutex)
{
    return pil_true;
}

void pil_mutex_destroy(pil_mutex_t* mutex)
{
}

void pil_event_create(pil_event_t* ev, pil_event_id_t id)
{
}

void pil_event_destroy(pil_event_t* ev)
{
}

void pil_event_assign(pil_event_t* to, pil_event_t* from)
{
}

void pil_event_set(pil_event_t* ev)
{
}

void pil_event_clear(pil_event_t* ev)
{
}

void pil_event_wait(pil_event_t* ev)
{
}

void pil_event_wait_timeout(pil_event_t* ev, uint32_t msTimeout)
{
}

uint32_t pilGetMonotonicTime(void)
{
    return getCurRelTimeInMillisec();
}

#ifdef __cplusplus
}
#endif
