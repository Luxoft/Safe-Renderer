#ifndef LUXOFTSAFERENDERER_BITMAPFIELD_H
#define LUXOFTSAFERENDERER_BITMAPFIELD_H

/******************************************************************************
**
**   File:        BitmapField.h
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

#include "Field.h"
#include <ddh_defs.h>

namespace lsr
{

/**
 * Class provides functionality to draw Bitmap on some canvas.
 *
 * @reqid SW_ENG_076, SW_ENG_077
 */
class BitmapField P_FINAL : public Field
{
    friend class unittest::EngineTest;
public:
    /**
     * Creates a bitmap field.
     *
     * @param[in] pDdh @c lsr::StaticBitmapFieldType ddh configuration.
     */
    explicit BitmapField(const StaticBitmapFieldType* const pDdh);

    virtual LSREngineError setup(const Database& db) P_OVERRIDE;

private:
    virtual void onDraw(Canvas& dst, const Area& rect) const P_OVERRIDE;

    virtual bool onVerify(Canvas&, const Area&) P_OVERRIDE;

    virtual LSREngineError getChildError() const P_OVERRIDE
    {
        return LSR_NO_ENGINE_ERROR;
    }

    virtual bool isChildInvalidated() const P_OVERRIDE
    {
        return false;
    }

    bool setupBitmapExpr();

    const StaticBitmapFieldType* m_pDdh;
    const Database* m_pDatabase;
    BitmapId m_bitmapId;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_BITMAPFIELD_H
