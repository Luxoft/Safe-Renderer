/******************************************************************************
**
**   File:        DdhStaticBitmapFieldBuilder.cpp
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

#include "DdhStaticBitmapFieldBuilder.h"

#include <ExpressionTermTypeFactory.h>

namespace framehandlertests
{

DdhStaticBitmapFieldBuilder::DdhStaticBitmapFieldBuilder()
{
}

void DdhStaticBitmapFieldBuilder::create(const lsr::AreaType& area,
                                         const bool isVisible,
                                         const U32 bitmapId)
{
    addArea(area);
    addVisibility(isVisible);
    addBitmap(bitmapId);
}

void DdhStaticBitmapFieldBuilder::create(const lsr::AreaType& area,
                                         const bool isVisible,
                                         const lsr::DynamicDataType& bitmapId)
{
    addArea(area);
    addVisibility(isVisible);
    addDynamicBitmap(bitmapId);
}

void DdhStaticBitmapFieldBuilder::createWithoutVisibility(const lsr::AreaType& area,
                                                          const U32 bitmapId)
{
    addArea(area);
    addBitmap(bitmapId);
}

void DdhStaticBitmapFieldBuilder::createWithoutBitmap(const lsr::AreaType& area,
                                                      const bool isVisible)
{
    addArea(area);
    addVisibility(isVisible);
}

void DdhStaticBitmapFieldBuilder::createWithoutArea(const bool isVisible,
                                                    const U32 bitmapId)
{
    addVisibility(isVisible);
    addBitmap(bitmapId);
}

void DdhStaticBitmapFieldBuilder::addArea(const lsr::AreaType& area)
{
    m_factory.addArea(area);
}

void DdhStaticBitmapFieldBuilder::addVisibility(const bool isVisible)
{
    ExpressionTermTypeFactory visibilityExpr;
    visibilityExpr.createBoolExprTerm(isVisible);

    m_factory.addVisibleExpr(visibilityExpr.getDdh(), visibilityExpr.getSize());
}

void DdhStaticBitmapFieldBuilder::addBitmap(const U32 bitmapId)
{
    ExpressionTermTypeFactory bitmapExpr;
    bitmapExpr.createIntegerExprTerm(bitmapId);

    m_factory.addBitmapExpr(bitmapExpr.getDdh(), bitmapExpr.getSize());
}

void DdhStaticBitmapFieldBuilder::addDynamicBitmap(const lsr::DynamicDataType& bitmapId)
{
    ExpressionTermTypeFactory bitmapExpr;
    bitmapExpr.createDynamicDataExprTerm(bitmapId);

    m_factory.addBitmapExpr(bitmapExpr.getDdh(), bitmapExpr.getSize());
}


} // namespace framehandlertests
