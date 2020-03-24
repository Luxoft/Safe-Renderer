#ifndef LUXOFTSAFERENDERER_WIDGETCHILDREN_H
#define LUXOFTSAFERENDERER_WIDGETCHILDREN_H

/******************************************************************************
**
**   File:        WidgetChildren.h
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

#include <LsrTypes.h>
#include <LSRLimits.h>
#include <LSREngineError.h>
#include <LSRErrorCollector.h>
#include <NonCopyable.h>
#include <Assertion.h>
#include <Area.h>
#include <ReturnValue.h>


namespace lsr
{

/**
 * Implements base functionality for all widgets.
 *
 * @reqid SW_ENG_068, SW_ENG_070, SW_ENG_071, SW_ENG_073
 */
template <class T, size_t maxChildren>
class WidgetChildren: private NonCopyable
{
public:
    WidgetChildren()
        : NonCopyable()
        , m_childrenCount(0U)
    {
        for (size_t pos = 0U; pos < maxChildren; ++pos)
        {
            m_children[pos] = NULL;
        }
    }

    LSREngineError setup(const Database& db)
    {
        LSRErrorCollector err(LSR_NO_ENGINE_ERROR);
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            err = m_children[i]->setup(db);
        }
        return err.get();
    }

    bool addChild(T* const pChild)
    {
        const bool addable = (m_childrenCount < maxChildren);
        if (addable)
        {
            m_children[m_childrenCount] = pChild;
            ++m_childrenCount;
        }
        return addable;
    }

    bool isInvalidated() const
    {
        ReturnValue<bool, false> res;
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            if (m_children[i]->isInvalidated())
            {
                res = true;
                break;
            }
        }
        return res;
    }

    void draw(Canvas& dst, const Area& rect) const
    {
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            T* pChild = m_children[i];
            ASSERT(pChild != NULL);

            Area childArea(pChild->getArea());
            childArea.moveByFP(rect.getLeftFP(), rect.getTopFP());

            pChild->draw(dst, childArea);
        }
    }

    bool verify(Canvas& dst, const Area& rect) const
    {
        ReturnValue<bool, true> result;
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            T* pChild = m_children[i];
            ASSERT(pChild != NULL);

            Area childArea(pChild->getArea());
            childArea.moveByFP(rect.getLeftFP(), rect.getTopFP());

            // coverity[stack_use_unknown]
            if (!pChild->verify(dst, childArea))
            {
                result = false;
                static_cast<void>(result);  // suppress MISRA 0-1-6: Value is not used on this path
            }
        }
        return result;
    }

    LSREngineError getError() const
    {
        LSRErrorCollector error = LSR_NO_ENGINE_ERROR;
        for (std::size_t i = 0U; i < m_childrenCount; ++i)
        {
            T* pChild = m_children[i];
            ASSERT(pChild != NULL);
            const LSREngineError childError = pChild->getError();
            error = childError;
        }
        return error.get();
    }

private:
    T* m_children[maxChildren];
    size_t m_childrenCount;
};


} // namespace lsr

#endif // LUXOFTSAFERENDERER_WIDGETCHILDREN_H
