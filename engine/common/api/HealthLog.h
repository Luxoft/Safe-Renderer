#ifndef LUXOFTSAFERENDERER_HEALTH_LOG_H
#define LUXOFTSAFERENDERER_HEALTH_LOG_H

/******************************************************************************
**
**   File:        HealthLog.h
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

#include "LSRError.h"


enum LsrComponentId
{
    LSR_COMP_COMMUNICATION = 1,
    LSR_COMP_ODI,
};

struct LsrHealth;

/**
*
* Transfer health information to customer application. This callback
* should be implemented by customer. The main goal is to provide ability
* to receive health information outside of LSR library.
*
* @param componentId Id of the component the callback is called from.
* @param errorId Error code transferred to the customer.
* @param msgHealth Struct which contains binary encoded information for customer.
*        Format and content will be defined later.
*
**/
extern "C" void LsrHealthCallback(LsrComponentId componentId, LSRError errorId, struct LsrHealth* msgHealth);

#ifdef USE_HEALTH_REPORT
    #define LOG_HEALTH(condition, componentId, errorId, msgStruct) if (condition) { LsrHealthCallback((placeId), (errorId), (msgStruct)); }
#else
    #define LOG_HEALTH(condition, componentId, errorId, msgStruct)
#endif

#endif // LUXOFTSAFERENDERER_HEALTH_LOG_H
