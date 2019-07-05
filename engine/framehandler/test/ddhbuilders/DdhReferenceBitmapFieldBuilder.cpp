/******************************************************************************
**
**   File:        DdhReferenceBitmapFieldBuilder.cpp
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

#include "DdhReferenceBitmapFieldBuilder.h"

#include <ExpressionTermTypeFactory.h>

namespace framehandlertests
{

DdhReferenceBitmapFieldBuilder::DdhReferenceBitmapFieldBuilder()
{
}

void DdhReferenceBitmapFieldBuilder::create(const U16 errorCounter,
                                            const lsr::AreaType& area,
                                            const bool isVisible,
                                            const U32 bitmapId)
{
    setErrorCounter(errorCounter);
    addArea(area);
    addVisibility(isVisible);
    addBitmap(bitmapId);
}

void DdhReferenceBitmapFieldBuilder::create(const U16 errorCounter,
                                            const lsr::AreaType& area,
                                            const bool isVisible,
                                            const lsr::DynamicDataType& bitmapId)
{
    setErrorCounter(errorCounter);
    addArea(area);
    addVisibility(isVisible);
    addDynamicBitmap(bitmapId);
}

void DdhReferenceBitmapFieldBuilder::createWithoutVisibility(const U16 errorCounter,
                                                             const lsr::AreaType& area,
                                                             const U32 bitmapId)
{
    setErrorCounter(errorCounter);
    addArea(area);
    addBitmap(bitmapId);
}

void DdhReferenceBitmapFieldBuilder::createWithoutBitmap(const U16 errorCounter,
                                                         const lsr::AreaType& area,
                                                         const bool isVisible)
{
    setErrorCounter(errorCounter);
    addArea(area);
    addVisibility(isVisible);
}

void DdhReferenceBitmapFieldBuilder::createWithoutArea(const U16 errorCounter,
                                                       const bool isVisible,
                                                       const U32 bitmapId)
{
    setErrorCounter(errorCounter);
    addVisibility(isVisible);
    addBitmap(bitmapId);
}

void DdhReferenceBitmapFieldBuilder::setErrorCounter(const U16 value)
{
    m_factory.setErrorCounter(value);
}

void DdhReferenceBitmapFieldBuilder::addArea(const lsr::AreaType& area)
{
    m_factory.addArea(area);
}

void DdhReferenceBitmapFieldBuilder::addVisibility(const bool isVisible)
{
    ExpressionTermTypeFactory visibilityExpr;
    visibilityExpr.createBoolExprTerm(isVisible);

    m_factory.addVisibleExpr(visibilityExpr.getDdh(), visibilityExpr.getSize());
}

void DdhReferenceBitmapFieldBuilder::addBitmap(const U32 bitmapId)
{
    ExpressionTermTypeFactory bitmapExpr;
    bitmapExpr.createIntegerExprTerm(bitmapId);

    m_factory.addBitmapExpr(bitmapExpr.getDdh(), bitmapExpr.getSize());
}

void DdhReferenceBitmapFieldBuilder::addDynamicBitmap(const lsr::DynamicDataType& bitmapId)
{
    ExpressionTermTypeFactory bitmapExpr;
    bitmapExpr.createDynamicDataExprTerm(bitmapId);

    m_factory.addBitmapExpr(bitmapExpr.getDdh(), bitmapExpr.getSize());
}

} // namespace framehandlertests
