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
#include "PilOdiComSession.h"
#include "pil.h"

#include <ddh_defs.h>
#include <Number.h>
#include <DataStatus.h>
#include <new>

using lsr::Engine;
const size_t MAX_ENGINES = 2;

enum
{
    MAX_FUS = 10
};
typedef lsr::PilOdiComSession<MessageTypes::LAST - 1, MAX_FUS> ComSession;

class LSREngineImpl
{
public:
    LSREngineImpl(const lsr::Database& db, PILMailbox mailbox)
        : session(mailbox, true)
        , engine(db, session)
    {
        pilMailboxInit(mailbox);
    }
    ComSession session;
    Engine engine;
};

typedef lsr::Pool<LSREngineImpl, MAX_ENGINES> EnginePool;
static EnginePool g_enginePool;

lsr::DynamicDataTypeEnumeration dataTypeFromLSR(LSRDataTypeEnum type)
{
    lsr::DynamicDataTypeEnumeration res = lsr::DATATYPE_SPEED;
    switch(type)
    {
    case LSR_DATA_TYPE_INTEGER:
    {
        res = lsr::DATATYPE_INTEGER;
        break;
    }
    case LSR_DATA_TYPE_DECIMAL:
    {
        res = lsr::DATATYPE_DECIMAL;
        break;
    }
    case LSR_DATA_TYPE_BITMAP_ID:
    {
        res = lsr::DATATYPE_BITMAP_ID;
        break;
    }
    case LSR_DATA_TYPE_DECIMAL_SHORT:
    {
        res = lsr::DATATYPE_DECIMAL_SHORT;
        break;
    }
    case LSR_DATA_TYPE_BOOLEAN:
    {
        res = lsr::DATATYPE_BOOLEAN;
        break;
    }
    default:
    {
        ASSERT(res != lsr::DATATYPE_SPEED);
        break;
    }
    }

    return res;
}

lsr::DataStatus dataStatusFromLSR(LSRDataStatusEnum status)
{
    lsr::DataStatus res;
    switch(status)
    {
    case LSR_DATA_STATUS_NOT_AVAILABLE:
    {
        res = lsr::DataStatus(lsr::DataStatus::NOT_AVAILABLE);
        break;
    }
    case LSR_DATA_STATUS_VALID:
    {
        res = lsr::DataStatus(lsr::DataStatus::VALID);
        break;
    }
    case LSR_DATA_STATUS_INVALID:
    {
        res = lsr::DataStatus(lsr::DataStatus::INVALID);
        break;
    }
    case LSR_DATA_STATUS_INCONSISTENT:
    default:
    {
        res = lsr::DataStatus(lsr::DataStatus::INCONSISTENT);
        break;
    }
    }

    return res;
}

extern "C"
{

LSREngine lsrCreate(const LSRDatabase* db, LSRError* error)
{
    LSREngine engine = NULL;
    *error = LSR_NO_ERROR;
    void* mem = g_enginePool.allocate(*error);
    if (NULL != mem)
    {
        lsr::ResourceBuffer ddhbin(db->ddhbin, db->ddhbinSize);
        lsr::ResourceBuffer imgbin(db->imgbin, db->imgbinSize);
        lsr::Database dbObj(ddhbin, imgbin);
        *error = dbObj.getError();
        if (LSR_NO_ERROR == *error)
        {
            PILMailbox mailbox = 0;
            LSREngineImpl* engineObj = new(mem)LSREngineImpl(dbObj, mailbox);
            engine = engineObj;
        }
    }
    return engine;
}

LSRError lsrDelete(LSREngine engine)
{
    LSRError error = LSR_NO_ERROR;
    if (NULL != engine)
    {
        static_cast<LSREngineImpl*>(engine)->~LSREngineImpl();
        error = g_enginePool.deallocate(engine);
    }
    return error;
}

LSRBoolean lsrRender(LSREngine e)
{
    LSREngineImpl* engine = static_cast<LSREngineImpl*>(e);
    ASSERT(engine != NULL);
    return engine->engine.render() ? LSR_TRUE : LSR_FALSE;
}

LSRBoolean lsrVerify(LSREngine e)
{
    LSREngineImpl* engine = static_cast<LSREngineImpl*>(e);
    ASSERT(engine != NULL);
    return engine->engine.verify() ? LSR_TRUE : LSR_FALSE;
}

LSRBoolean lsrSetValue(LSREngine e,
                       LSRFUClassId fuId,
                       LSRDataId dataId,
                       LSRDataValue value,
                       LSRDataTypeEnum dataType,
                       LSRDataStatusEnum dataStatus)
{
    LSREngineImpl* engine = static_cast<LSREngineImpl*>(e);
    ASSERT(engine != NULL);

    lsr::Number tmpValue(static_cast<U32>(value), dataTypeFromLSR(dataType));
    lsr::DataStatus status = dataStatusFromLSR(dataStatus);

    return engine->engine.setData(fuId, dataId, tmpValue, status) ?
        LSR_TRUE : LSR_FALSE;
}

LSRError lsrGetError(LSREngine e)
{
    LSREngineImpl* engine = static_cast<LSREngineImpl*>(e);
    ASSERT(engine != NULL);
    return engine->engine.getError();
}

} // extern "C"

