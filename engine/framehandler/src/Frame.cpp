/******************************************************************************
**
**   File:        Frame.cpp
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

#include "Frame.h"
#include "WidgetPool.h"

#include <Assertion.h>

#include <PageType.h>
#include <DDHType.h>
#include <PageDatabaseType.h>
#include <PanelDatabaseType.h>
#include <Database.h>
#include <HMIGlobalSettingsType.h>
#include <DisplaySizeType.h>

#include <new>

namespace lsr
{

Frame::Frame(const PageType* const pDdh)
    : Widget()
    , m_pDdh(pDdh)
{
}

bool Frame::setup(WidgetPool& factory,
                  const Database& db,
                  DataContext* const pContext,
                  LSRErrorCollector& error)
{
    bool successful = true;
    const DDHType* const pDdh = db.getDdh();
    ASSERT(NULL != pDdh);
    const HMIGlobalSettingsType* const pSettings = pDdh->GetHMIGlobalSettings();
    ASSERT(pSettings != NULL);
    const DisplaySizeType* const pDisplaySize = pSettings->GetDisplaySize();
    ASSERT(pDisplaySize != NULL);
    Area rect;
    rect.setWidth(static_cast<I32>(pDisplaySize->GetWidth()));
    rect.setHeight(static_cast<I32>(pDisplaySize->GetHeight()));
    setArea(rect);

    const U16 numPanels = m_pDdh->GetSizeOfPanelIdList();
    for (U16 i = 0U; i < numPanels; ++i)
    {
        const PanelId itemPanelId = m_pDdh->GetPanelIdItem(i);
        ASSERT(0U != itemPanelId);

        const PanelDatabaseType* const pPanelDB = pDdh->GetPanelDatabase();
        ASSERT((NULL != pPanelDB) && (itemPanelId <= pPanelDB->GetPanelCount()));

        // As id's are 1 based, database is 0 based. we should decrement id.
        const PanelType* const pDdhPanel = pPanelDB->GetPanel(itemPanelId - 1U);

        Panel* const pPanel = Panel::create(factory, db, pDdhPanel, pContext, error);
        /**
         * While @c MAX_PANELS_COUNT < @c MAX_WIDGET_CHILDREN_COUNT,
         * @c addChild method will always return @c true value.
         * That's why we have coverage gap here.
         */
        if ((NULL == pPanel) || (!addChild(pPanel)))
        {
            static_cast<void>(successful);  // suppress MISRA 0-1-6: Value is overwritten without previous usage on this path
            successful = false;
            break;
        }
    }
    return successful;
}

Frame* Frame::create(WidgetPool& factory,
                     const Database& db,
                     const FrameId id,
                     Window* /* parent */,
                     DataContext* const pContext,
                     LSRErrorCollector& error)
{
    const DDHType* const pDdh = db.getDdh();
    ASSERT(NULL != pDdh);

    const PageDatabaseType* const pDdhPageDB = pDdh->GetPageDatabase();
    ASSERT(NULL != pDdhPageDB);

    const PageType* const pDdhPage = pDdhPageDB->GetPage(static_cast<U16>(id) - 1U);
    ASSERT(NULL != pDdhPage);

    LSREngineError tmpError = LSR_NO_ENGINE_ERROR;
    void* const pRawMemory = factory.framePool().allocate(tmpError);
    error = tmpError;

    Frame* pFrame = new(pRawMemory)Frame(pDdhPage);
    if (NULL != pFrame)
    {
        if (!pFrame->setup(factory, db, pContext, error))
        {
            pFrame->~Frame();
            error = factory.framePool().deallocate(pRawMemory);
            pFrame = NULL;
        }
    }
    return pFrame;
}

void Frame::onUpdate(const U32 monotonicTimeMs)
{
    static_cast<void>(monotonicTimeMs);  // ignore unused variable
}

void Frame::onDraw(Canvas& /* dst */, const Area& /* rect */) const
{}

bool Frame::onVerify(Canvas&, const Area&)
{
    return true;
}

} // namespace lsr
