#ifndef POPULUSSC_DDHPAGEBUILDER_H
#define POPULUSSC_DDHPAGEBUILDER_H

/******************************************************************************
**
**   File:        DdhPageBuilder.h
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

#include <PageTypeFactory.h>

namespace framehandlertests
{

class DdhPageBuilder
{
public:
    DdhPageBuilder();

    const psc::PageType* getDdh() const;

    std::size_t getSize() const;

    void create(U32 panelCount, U16 panelId);

private:
    PageTypeFactory m_factory;
};

inline const psc::PageType* DdhPageBuilder::getDdh() const
{
    return reinterpret_cast<const psc::PageType*>(m_factory.getData());
}

inline std::size_t DdhPageBuilder::getSize() const
{
    return m_factory.getDataSize();
}

} // namespace framehandlertests

#endif // POPULUSSC_DDHPAGEBUILDER_H
