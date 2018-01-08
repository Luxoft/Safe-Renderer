#ifndef POPULUSSC_HEALTH_LOG_H
#define POPULUSSC_HEALTH_LOG_H

/******************************************************************************
**
**   File:        HealthLog.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Renderer.
**
**   Safe Renderer is free software: you can redistribute it and/or
**   modify it under the terms of the GNU Lesser General Public
**   License as published by the Free Software Foundation.
**
**   Safe Renderer is distributed in the hope that it will be useful,
**   but WITHOUT ANY WARRANTY; without even the implied warranty of
**   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
**   Lesser General Public License for more details.
**
**   You should have received a copy of the GNU Lesser General Public
**   License along with Safe Renderer.  If not, see
**   <http://www.gnu.org/licenses/>.
**
**   SPDX-License-Identifier: LGPL-3.0
**
******************************************************************************/

#include "PSCError.h"


enum PscComponentId
{
    PSC_COMP_COMMUNICATION = 1,
    PSC_COMP_ODI,
};

struct PscHealth;

/**
*
* Transfer health information to customer application. This callback
* should be implemented by customer. The main goal is to provide ability
* to receive health information outside of PopulusSC library.
*
* @param componentId Id of the component the callback is called from.
* @param errorId Error code transferred to the customer.
* @param msgHealth Struct which contains binary encoded information for customer.
*        Format and content will be defined later.
*
**/
extern "C" void PscHealthCallback(PscComponentId componentId, PSCError errorId, struct PscHealth* msgHealth);

#ifdef USE_HEALTH_REPORT
    #define LOG_HEALTH(condition, componentId, errorId, msgStruct) if (condition) { PscHealthCallback((placeId), (errorId), (msgStruct)); }
#else
    #define LOG_HEALTH(condition, componentId, errorId, msgStruct)
#endif

#endif // POPULUSSC_HEALTH_LOG_H
