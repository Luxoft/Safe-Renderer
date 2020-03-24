/******************************************************************************
**
**   File:        Canvas.cpp
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Luxoft Safe Renderer.
**
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "Canvas.h"
#include "DisplayManager.h"
#include "gil.h"
#include "Area.h"
#include "Color.h"
#include "Assertion.h"

namespace lsr
{

Canvas::Canvas(DisplayManager& dsp, const U16 width, const U16 height)
: m_dsp(dsp)
, m_width(width)
, m_height(height)
, m_error(LSR_NO_ENGINE_ERROR)
{
}

// coverity[misra_cpp_2008_rule_9_3_3_violation]
void Canvas::clear(const Color& chroma)
{
    const GILContext ctx = m_dsp.getContext();
    const U8 r = chroma.getRed();
    const U8 g = chroma.getGreen();
    const U8 b = chroma.getBlue();
    const U8 a = chroma.getAlpha();
    static_cast<void>(gilSetColor(ctx, r, g, b, a));  // ignore return value (gilError will be raised)
    gilClear(ctx);
}

void Canvas::drawBitmap(const StaticBitmap& bitmap, const Area& rect)
{
    Texture* const t = m_dsp.loadTexture(bitmap);
    if (t != NULL)
    {
        const GILContext ctx = m_dsp.getContext();
        t->bind(ctx);
        // output coordinates
        const I32 x1 = rect.getLeftFP();
        const I32 y1 = rect.getTopFP();
        const I32 x2 = rect.getRightFP();
        const I32 y2 = rect.getBottomFP();
        // TODO: get texture coordinates
        const I32 u1 = 0;
        const I32 v1 = 0;
        const U32 widthFP = (static_cast<U32>(t->getWidth()) - 1U) << 4U;
        const U32 heightFP = (static_cast<U32>(t->getHeight()) - 1U) << 4U;
        const I32 u2 = static_cast<I32>(widthFP);
        const I32 v2 = static_cast<I32>(heightFP);
        gilDrawQuad(ctx, x1, y1, u1, v1, x2, y2, u2, v2);
    }
    else
    {
        // configuration error
        m_error = LSR_ERROR_NO_TEXTURE;
    }
}

bool Canvas::verify(const StaticBitmap& bitmap, const Area& rect)
{
    bool verified = false;
    Texture* const t = m_dsp.loadTexture(bitmap);
    if (NULL != t)
    {
        const GILContext ctx = m_dsp.getContext();
        t->bind(ctx);
        // output coordinates
        const I32 x1 = rect.getLeftFP();
        const I32 y1 = rect.getTopFP();
        const I32 x2 = rect.getRightFP();
        const I32 y2 = rect.getBottomFP();
        // TODO: get texture coordinates
        const I32 u1 = 0;
        const I32 v1 = 0;
        const U32 widthFP = (static_cast<U32>(t->getWidth()) - 1U) << 4U;
        const U32 heightFP = (static_cast<U32>(t->getHeight()) - 1U) << 4U;
        const I32 u2 = static_cast<I32>(widthFP);
        const I32 v2 = static_cast<I32>(heightFP);
        const GILBoolean res = gilVerify(ctx, x1, y1, u1, v1, x2, y2, u2, v2);
        static_cast<void>(verified);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
        verified = (res == GIL_TRUE);
    }
    else
    {
        // configuration error
        m_error = LSR_ERROR_NO_TEXTURE;
    }
    return verified;
}

} // namespace lsr
