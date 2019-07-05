#ifndef LUXOFTSAFERENDERER_DDHPAGEBUILDER_H
#define LUXOFTSAFERENDERER_DDHPAGEBUILDER_H

/******************************************************************************
**
**   File:        DdhPageBuilder.h
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

#include <PageTypeFactory.h>

namespace framehandlertests
{

class DdhPageBuilder
{
public:
    DdhPageBuilder();

    const lsr::PageType* getDdh() const;

    std::size_t getSize() const;

    void create(U32 panelCount, U16 panelId);

private:
    PageTypeFactory m_factory;
};

inline const lsr::PageType* DdhPageBuilder::getDdh() const
{
    return reinterpret_cast<const lsr::PageType*>(m_factory.getData());
}

inline std::size_t DdhPageBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // LUXOFTSAFERENDERER_DDHPAGEBUILDER_H
