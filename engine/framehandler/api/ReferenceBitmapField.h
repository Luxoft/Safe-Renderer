#ifndef LUXOFTSAFERENDERER_REFERENCEBITMAPFIELD_H
#define LUXOFTSAFERENDERER_REFERENCEBITMAPFIELD_H

/******************************************************************************
**
**   File:        ReferenceBitmapField.h
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

namespace unittest
{
    class ReferenceBitmapFieldTest;
}

namespace lsr
{

/**
 * A non-drawing widget which checks video output.
 *
 * The ReferenceBitmap does not perform any drawing operations, but uses its connected
 * texture to perform a video output check.
 * The check is enabled if the visible flag is true.
 *
 * @reqid SW_ENG_073, SW_ENG_076
 */
class ReferenceBitmapField P_FINAL : public Field
{
    friend class unittest::ReferenceBitmapFieldTest;
    friend class unittest::EngineTest;
public:
    /**
     * Create an object.
     *
     * @param[in] pDdh @c lsr::ReferenceBitmapFieldType ddh configuration.
     */
    explicit ReferenceBitmapField(const ReferenceBitmapFieldType* const pDdh);

    virtual LSREngineError setup(const Database& db) P_OVERRIDE;

    /**
     * Returns the cumulated number of verification errors
     * Each verification failure will increase the counter by 1 (@see onVerify())
     * The error counter is reset when:
     * - the field is verified in invisible state
     * - the error counter is explicitly reset by clearVerificationErrors()
     * @return number of verification errors
     */
    U32 getVerificationErrors() const
    {
        return m_verificationErrors;
    }

    /**
     * Resets the number of verification errors to zero
     */
    void clearVerificationErrors();

    /**
     * Returns the result of the most recent verification (@see onVerify())
     * Defaults to false until verification is triggered for the first time
     * @return false if the last onVerify() reported an error, true otherwise
     */
    bool getLastVerificationResult() const
    {
        return m_verified;
    }

private:
    /**
     * Method does nothing. This widget can't be drawn.
     */
    virtual void onDraw(Canvas&, const Area&) const P_OVERRIDE;

    /**
     * If visible flag is enabled, method performs video checking with @c Canvas object.
     *
     * If check fails, the error counter inside @c DataHandler will be incremented.
     * See @c IncrementErrorCounter.
     *
     * @param[in] dst  destination canvas object which provides checking functionality.
     * @param[in] rect area in absolute coordinates.
     *
     * @return @true if check successes or visible flag is @c false, @c false otherwise.
     */
    virtual bool onVerify(Canvas& dst, const Area& rect) P_OVERRIDE;

    virtual LSREngineError getChildError() const
    {
        return LSR_NO_ENGINE_ERROR;
    }

    virtual bool isChildInvalidated() const
    {
        return false;
    }

    bool setupBitmapExpr();

    const ReferenceBitmapFieldType* m_pDdh;
    const Database* m_pDatabase;
    BitmapId m_bitmapId;
    U32 m_verificationErrors;
    bool m_verified;
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_REFERENCEBITMAPFIELD_H
