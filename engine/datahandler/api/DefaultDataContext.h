#ifndef LUXOFTSAFERENDERER_DEFAULTDATACONTEXT_H
#define LUXOFTSAFERENDERER_DEFAULTDATACONTEXT_H

/******************************************************************************
**
**   File:        DefaultDataContext.h
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

#include "DataContext.h"
#include "IDataHandler.h"

namespace lsr
{

/**
 * Common implementation of @c DataContext class.
 * It stores reference to @c IDataHandler object and provide an access to it.
 */
class DefaultDataContext : public DataContext
{
public:
    /**
     * Constructs an object.
     *
     * @param[in] dataHandler reference to @c IDataHandler object.
     */
    DefaultDataContext(IDataHandler& dataHandler);

    /**
     * @return pointer to stored @c IDataHadnler object.
     */
    virtual IDataHandler* getDataHandler() const P_OVERRIDE;

private:
    IDataHandler& m_dataHandler;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_DEFAULTDATACONTEXT_H
