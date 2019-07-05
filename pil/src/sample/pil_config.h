#ifndef LSR_PIL_CONFIG_H_
#define LSR_PIL_CONFIG_H_

/******************************************************************************
**
**   File:        pil_config.h
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

const int PILBuffersizeFU=500;     ///< Buffer size for the FU App incoming message queues.
const int PILBufferSizePop=10000;  ///< Buffer size for the LSR Engine incoming messages queue.

const int mutexLSRQueueID = 0; ///< Mutex ID - ignored for most platforms.
const int mutexFUQueueID = 1;      ///< Mutex ID - ignored for most platforms.

struct ConnectionIndex
{
    typedef enum PILConnections_Tag
    {
            PILConn_Lsr = 0,
            PILConn_Fu1App,
            PILConn_Fu2App,
            PILConn_MediaApp,
            PILConn_NaviApp,
            PILConn_Last,
    } PILConnections;
};

#endif // LSR_PIL_CONFIG_H_
