#ifndef LUXOFTSAFERENDERER_IDATAHANDLER_H
#define LUXOFTSAFERENDERER_IDATAHANDLER_H

/******************************************************************************
**
**   File:        IDataHandler.h
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

#include "Number.h"
#include "DataStatus.h"

#include <LsrTypes.h>
#include <DynamicDataType.h>
#include <DynamicIndicationIdType.h>

namespace lsr
{

class IDataHandler
{
public:
    /**
     * Interface for listeners that subscribe to changes on the data
     * entries received by the DataHandler.
     * Listener is used for subscriptions to single data entries
     * but also for global notification.
     */
    class IListener
    {
    public:
        virtual void onDataChange() = 0;

        virtual ~IListener() {}
    };

    /**
     * Registers subscription for data entry identified by @c lsr::DynamicDataType.
     *
     * @param[in] fuClassId the identifier of the FU
     * @param[in] dataId    the identifier of the data
     * @param[in] pListener the Listener to subscribe
     *
     * @return @c true if the DataHandler managed to get storage for the data subscription,
     *         @c false otherwise.
     */
    virtual bool subscribeData(FUClassId fuClassId,
                               DataId dataId,
                               IDataHandler::IListener* pListener) = 0;

    /**
     * Registers a listener that will be notified whenever an indication or data changes.
     *
     * @param[in] fuClassId    the identifier of the FU
     * @param[in] indicationId the identifier of the indication
     * @param[in] pListener    the Listener
     *
     * @return @c true if the DataHandler managed to get storage for the data subscription,
     *         @c false otherwise.
     */
    virtual bool subscribeIndication(FUClassId fuClassId,
                                     IndicationId indicationId,
                                     IDataHandler::IListener* pListener) = 0;

    /**
     * Unsubscribes data and unregisters a listener so that it no longer
     * will be notified when a data value changes
     *
     * @param[in] fuClassId the identifier of the FU
     * @param[in] dataId    the identifier of the data
     * @param[in] pListener the listener to remove
     */
    virtual void unsubscribeData(FUClassId fuClassId,
                                 DataId dataId,
                                 IDataHandler::IListener* pListener) = 0;

    /**
     * Unsubscribes and unregisters a listener so that it no longer
     * will be notified when a data value changes
     *
     * @param[in] fuClassId    the identifier of the FU
     * @param[in] indicationId the identifier of the indication
     * @param[in] pListener    the listener to remove
     */
    virtual void unsubscribeIndication(FUClassId fuClassId,
                                       IndicationId indicationId,
                                       IDataHandler::IListener* pListener) = 0;

    /**
     * Returns the data, identified by @c fuClassId and @c dataId.
     * Value is calculated in accordance with the data type.
     *
     * @param[in]  fuClassId the identifier of the FU
     * @param[in]  dataId    the identifier of the data
     * @param[out] value     the output value.
     *
     * @return status of @c value, see @c DataStatus.
     */
    virtual DataStatus getNumber(FUClassId fuClassId,
                                 DataId dataId,
                                 Number &value) const = 0;

    /**
     * Returns value of the indication identified by @c fuClassId and @c indicationId.
     *
     * @param[in]  fuClassId    the identifier of the FU
     * @param[in]  indicationId the identifier of the indication
     * @param[out] value        the value of indication in Boolean type
     *
     * @return status of @c value, see @c DataStatus.
     */
    virtual DataStatus getIndication(FUClassId fuClassId,
                                     IndicationId indicationId,
                                     bool& value) const = 0;

    /**
     * Sets a data entry in the data handler
     * @param[in]  fuClassId    the identifier of the FU
     * @param[in]  dataId    the identifier of the data
     * @param[in]  value     the value which shall be set
     * @param[in]  status    the status which shall be applied to the data
     * @return true if the data was set, false on error
     */
    virtual bool setData(FUClassId fuClassId, DataId dataId, const Number& value, DataStatus status) = 0;

    virtual ~IDataHandler() {}
};

} // namespace lsr

#endif // LUXOFTSAFERENDERER_IDATAHANDLER_H
