/******************************************************************************
**
**   File:        Frame.cpp
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

namespace psc
{

Frame::Frame(const PageType* pDdh)
    : Widget()
    , m_pDdh(pDdh)
{
}

bool Frame::setup(WidgetPool& widgetPool,
                  const Database& db,
                  DataContext* pContext,
                  PSCErrorCollector& error)
{
    bool success = true;
    const DDHType* pDdh = db.getDdh();
    ASSERT(NULL != pDdh);
    const HMIGlobalSettingsType* pSettings = pDdh->GetHMIGlobalSettings();
    ASSERT(pSettings != NULL);
    const DisplaySizeType* pDisplaySize = pSettings->GetDisplaySize();
    ASSERT(pDisplaySize != NULL);
    Area area;
    area.setWidth(static_cast<I32>(pDisplaySize->GetWidth()));
    area.setHeight(static_cast<I32>(pDisplaySize->GetHeight()));
    setArea(area);

    const U16 numPanels = m_pDdh->GetSizeOfPanelIdList();
    for (U16 i = 0U; i < numPanels; ++i)
    {
        const PanelId panelId = m_pDdh->GetPanelIdItem(i);
        ASSERT(0U != panelId);

        const PanelDatabaseType* pPanelDB = pDdh->GetPanelDatabase();
        ASSERT(NULL != pPanelDB && panelId <= pPanelDB->GetPanelCount());

        // As id's are 1 based, database is 0 based. we should decrement id.
        const PanelType* pDdhPanel = pPanelDB->GetPanel(panelId - 1U);

        Panel* pPanel = Panel::create(widgetPool, db, pDdhPanel, pContext, error);
        /**
         * While @c MAX_PANELS_COUNT < @c MAX_WIDGET_CHILDREN_COUNT,
         * @c addChild method will always return @c true value.
         * That's why we have coverage gap here.
         */
        if (NULL == pPanel || !addChild(pPanel))
        {
            success = false;
            break;
        }
    }
    return success;
}

Frame* Frame::create(WidgetPool& widgetPool,
                     const Database& db,
                     FrameId frameId,
                     Window* /* parent */,
                     DataContext* pContext,
                     PSCErrorCollector& error)
{
    const DDHType* pDdh = db.getDdh();
    ASSERT(NULL != pDdh);

    const PageDatabaseType* pDdhPageDB = pDdh->GetPageDatabase();
    ASSERT(NULL != pDdhPageDB);

    const PageType* pDdhPage = pDdhPageDB->GetPage(static_cast<U16>(frameId - 1U));
    ASSERT(NULL != pDdhPage);

    PSCError tmpError = PSC_NO_ERROR;
    void* pRawMemory = widgetPool.framePool().allocate(tmpError);
    error = tmpError;

    Frame* pFrame = new(pRawMemory)Frame(pDdhPage);
    if (NULL != pFrame)
    {
        if (!pFrame->setup(widgetPool, db, pContext, error))
        {
            pFrame->~Frame();
            error = widgetPool.framePool().deallocate(pRawMemory);
            pFrame = NULL;
        }
    }
    return pFrame;
}

void Frame::onUpdate(const U32 /* monotonicTimeMs */)
{}

void Frame::onDraw(Canvas& /* canvas */, const Area& /* area */)
{}

bool Frame::onVerify(Canvas&, const Area&)
{
    return true;
}


}
