#ifndef POPULUS_PGW_CONFIG_H_
#define POPULUS_PGW_CONFIG_H_

/******************************************************************************
**
**   File:        pgw_config.h
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

const int PGWBuffersizeFU=500;     ///< Buffer size for the FU App incoming message queues.
const int PGWBufferSizePop=10000;  ///< Buffer size for the Populus Engine incoming messages queue.

const int mutexPopulusQueueID = 0; ///< Mutex ID - ignored for most platforms.
const int mutexFUQueueID = 1;      ///< Mutex ID - ignored for most platforms.

struct ConnectionIndex
{
    typedef enum PGWConnections_Tag
    {
            PGWConn_Populus = 0,
            PGWConn_Fu1App,
            PGWConn_Fu2App,
            PGWConn_MediaApp,
            PGWConn_NaviApp,
            PGWConn_Last,
    } PGWConnections;
};

#endif // POPULUS_PGW_CONFIG_H_
