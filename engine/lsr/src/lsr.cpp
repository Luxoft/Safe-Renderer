/******************************************************************************
**
**   File:        lsr.cpp
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

#include "lsr.h"
#include "Assertion.h"
#include "Pool.h"
#include "Engine.h"
#include "pil.h"

#include <ddh_defs.h>
#include <Number.h>
#include <DataStatus.h>
#include <new>

using lsr::Engine;
const size_t MAX_ENGINES = 2U;

typedef lsr::Pool<lsr::Engine, MAX_ENGINES> EnginePool;
static EnginePool g_enginePool;

extern "C"
{

LSREngine lsrCreate(const LSRDatabase db)
{
    LSREngine engine = NULL;
    LSRError error = LSR_NO_ERROR;
    void* const mem = g_enginePool.allocate(error);
    if (NULL != mem)
    {
        const lsr::DDHType* const ddh = (static_cast<const lsr::DDHType* const>(db));
        engine = new(mem)lsr::Engine(ddh);
    }
    return engine;
}

void lsrDelete(const LSREngine engine)
{
    if (NULL != engine)
    {
        static_cast<lsr::Engine*>(engine)->~Engine();
        static_cast<void>(g_enginePool.deallocate(engine));
    }
}

LSRBoolean lsrRender(const LSREngine e)
{
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(e);
    ASSERT(pEngine != NULL);
    return pEngine->render() ? static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRBoolean lsrVerify(const LSREngine e)
{
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(e);
    ASSERT(pEngine != NULL);
    return pEngine->verify() ? static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRBoolean lsrSetBoolean(const LSREngine e,
                       const LSRFUDataId fuDataId,
                       const LSRBoolean value)
{
    ASSERT(e != NULL);
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(e);

    lsr::Number tmpValue(value == LSR_TRUE);
    const lsr::DataStatus status = lsr::DataStatus::VALID;

    return pEngine->setData(lsr::DynamicData(fuDataId), tmpValue, status) ?
        static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRBoolean lsrSetInteger(const LSREngine engine,
                       const LSRFUDataId fuDataId,
                       const LSRBoolean value)
{
    ASSERT(engine != NULL);
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(engine);

    lsr::Number tmpValue(static_cast<U32>(value), lsr::DATATYPE_INTEGER);
    const lsr::DataStatus status = lsr::DataStatus::VALID;

    return pEngine->setData(lsr::DynamicData(fuDataId), tmpValue, status) ?
        static_cast<LSRBoolean>(LSR_TRUE) : static_cast<LSRBoolean>(LSR_FALSE);
}

LSRDataStatus lsrGetBoolean(const LSREngine engine, const LSRFUDataId fuDataId, LSRBoolean* value)
{
    ASSERT(engine != NULL);
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(engine);
    lsr::Number tmpValue;
    lsr::DataStatus status = pEngine->getData(lsr::DynamicData(fuDataId), tmpValue);
    if (tmpValue.getType() == lsr::DATATYPE_BOOLEAN)
    {
        if (value != NULL)
        {
            *value = tmpValue.getBool() ? LSR_TRUE : LSR_FALSE;
        }
    }
    else
    {
        status = lsr::DataStatus::INCONSISTENT;
    }
    return static_cast<LSRDataStatus>(status.getValue());
}

LSRDataStatus lsrGetInteger(const LSREngine engine, const LSRFUDataId fuDataId, int32_t* value)
{
    ASSERT(engine != NULL);
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(engine);
    lsr::Number tmpValue;
    lsr::DataStatus status = pEngine->getData(lsr::DynamicData(fuDataId), tmpValue);
    if (tmpValue.getType() == lsr::DATATYPE_INTEGER)
    {
        if (value != NULL)
        {
            *value = static_cast<int32_t>(tmpValue.getU32());
        }
    }
    else
    {
        status = lsr::DataStatus::INCONSISTENT;
    }
    return static_cast<LSRDataStatus>(status.getValue());
}

LSRError lsrGetError(const LSREngine e)
{
    lsr::Engine* const pEngine = static_cast<lsr::Engine* const>(e);
    return (NULL != pEngine) ? pEngine->getError() : LSR_UNKNOWN_ERROR;
}

} // extern "C"
