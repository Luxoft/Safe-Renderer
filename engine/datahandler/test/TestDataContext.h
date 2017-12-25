#ifndef POPULUSSC_TEXTDATACONTEXT_H
#define POPULUSSC_TEXTDATACONTEXT_H

/******************************************************************************
**
**   File:        TestDataContext.h
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

#include <DataContext.h>
#include <IDataHandler.h>

#include <PscTypes.h>

class TestDataContext: public psc::DataContext
{
public:
    TestDataContext()
        : m_handler(NULL)
    {}

    void setHandler(psc::IDataHandler* handler)
    {
        m_handler = handler;
    }

    virtual psc::IDataHandler* getDataHandler() const P_OVERRIDE
    {
        return m_handler;
    }

private:
    psc::IDataHandler* m_handler;
};

#endif // POPULUSSC_TEXTDATACONTEXT_H
