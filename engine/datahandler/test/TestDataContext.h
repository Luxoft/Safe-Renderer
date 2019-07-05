#ifndef LUXOFTSAFERENDERER_TEXTDATACONTEXT_H
#define LUXOFTSAFERENDERER_TEXTDATACONTEXT_H

/******************************************************************************
**
**   File:        TestDataContext.h
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

#include <DataContext.h>
#include <IDataHandler.h>

#include <LsrTypes.h>

class TestDataContext: public lsr::DataContext
{
public:
    TestDataContext()
        : m_handler(NULL)
    {}

    void setHandler(lsr::IDataHandler* handler)
    {
        m_handler = handler;
    }

    virtual lsr::IDataHandler* getDataHandler() const P_OVERRIDE
    {
        return m_handler;
    }

private:
    lsr::IDataHandler* m_handler;
};

#endif // LUXOFTSAFERENDERER_TEXTDATACONTEXT_H
