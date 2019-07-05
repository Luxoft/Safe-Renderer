/******************************************************************************
**
**   File:        OdiRecorder.cpp
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

#include "OdiRecorder.h"

namespace lsr
{

const U32 OdiRecorder::FILE_ID = 0x49444f2E; // ".ODI"
const U32 OdiRecorder::VERSION = 0x0003; // v0.3

OdiRecorder::OdiRecorder(void *buffer, size_t bufferSize)
{
}

OdiRecorder::~OdiRecorder()
{
}


void OdiRecorder::beginChunk(MessageDirection::Val direction)
{
}

void OdiRecorder::endChunk(MessageDirection::Val direction)
{
}

void OdiRecorder::write(const U8* msgBuffer, U32 msgLen, U8 msgType)
{
}

} // namespace lsr
