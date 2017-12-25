#ifndef POPULUSSC_MOCKDATAHANDLER_H
#define POPULUSSC_MOCKDATAHANDLER_H

/******************************************************************************
**
**   File:        MockDataHandler.h
**   Description:
**
**   Copyright (C) 2017 Luxoft GmbH
**
**   This file is part of Safe Render.
**
**   Safe Render is free software: you can redistribute it and/or
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


#include <IDataHandler.h>
#include <Number.h>
#include <DynamicDataType.h>

#include <gmock/gmock.h>

class MockDataHandler: public psc::IDataHandler
{
public:
    MockDataHandler()
    {}

    MockDataHandler(psc::Number number)
        : m_commonNumber(number)
        , m_commonStatus(psc::DataStatus::VALID)
    {}

    MOCK_METHOD3(subscribeData, bool (FUClassId, DataId, psc::IDataHandler::IListener*));
    MOCK_METHOD3(subscribeIndication, bool (FUClassId, IndicationId, psc::IDataHandler::IListener*));
    MOCK_METHOD3(unsubscribeData, void (FUClassId, DataId, psc::IDataHandler::IListener*));
    MOCK_METHOD3(unsubscribeIndication, void (FUClassId, IndicationId, psc::IDataHandler::IListener*));
    MOCK_METHOD4(setData, bool(FUClassId, DataId, const psc::Number&, psc::DataStatus));

    void setNumber(const psc::Number& number)
    {
        m_commonNumber = number;
        m_commonStatus = psc::DataStatus::VALID;
    }

    void setNumber(const psc::Number& number,
                   FUClassId fuClassId,
                   DataId dataId,
                   psc::DataStatus status)
    {
        m_specNumber = number;
        m_specStatus = status;
        m_specFuId = fuClassId;
        m_specDataId = dataId;
    }

    void setOutDatedNumber(const psc::Number& number)
    {
        m_commonNumber = number;
        m_commonStatus = psc::DataStatus::NOT_AVAILABLE;
    }

    void setInvalidNumber(const psc::Number& number)
    {
        m_commonNumber = number;
        m_commonStatus = psc::DataStatus::INVALID;
    }

    virtual psc::DataStatus getNumber(FUClassId fuClassId,
                                      DataId dataId,
                                      psc::Number &value) const P_OVERRIDE
    {
        psc::DataStatus status;

        m_lastFuId = fuClassId;
        m_lastDataId = dataId;

        if (fuClassId == m_specFuId && dataId == m_specDataId)
        {
            value = m_specNumber;
            status = m_specStatus;
        }
        else
        {
            value = m_commonNumber;
            status = m_commonStatus;
        }

        return status;
    }

    virtual psc::DataStatus getIndication(FUClassId fuClassId,
                                          IndicationId indicationId,
                                          bool& value) const P_OVERRIDE
    {
        m_lastFuId = fuClassId;
        m_lastIndicationId = indicationId;
        value = true;

        return psc::DataStatus::VALID;
    }

    FUClassId getLastFuId() const
    {
        return m_lastFuId;
    }

    DataId getLastDataId() const
    {
        return m_lastDataId;
    }

    IndicationId getLastIndicationId() const
    {
        return m_lastIndicationId;
    }

private:
    mutable psc::Number m_commonNumber;
    mutable FUClassId m_lastFuId;
    mutable DataId m_lastDataId;
    mutable IndicationId m_lastIndicationId;
    mutable psc::DataStatus m_commonStatus;

    mutable psc::Number m_specNumber;
    mutable psc::DataStatus m_specStatus;
    mutable FUClassId m_specFuId;
    mutable DataId m_specDataId;
};


#endif // POPULUSSC_MOCKDATAHANDLER_H
