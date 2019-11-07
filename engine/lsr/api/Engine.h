#ifndef LUXOFTSAFERENDERER_ENGINE_H
#define LUXOFTSAFERENDERER_ENGINE_H

/******************************************************************************
**
**   File:        Engine.h
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

#include <ddh_defs.h>
#include "Database.h"
#include "FrameHandler.h"
#include "DisplayManager.h"
#include "DataHandler.h"


namespace lsr
{

class Engine
{
public:
    Engine(const DDHType* ddhbin);

    bool render();
    bool verify();

    bool setData(const DynamicData& dataId,
                 const Number& value,
                 const DataStatus status);
    DataStatus getData(const DynamicData& dataId, Number &value) const;

    bool handleWindowEvents();

    LSRError getError();

private:
    Database m_db;
    DisplayManager m_display;
    DataHandler m_dataHandler;
    FrameHandler m_frameHandler;
    LSRError m_error;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_ENGINE_H
