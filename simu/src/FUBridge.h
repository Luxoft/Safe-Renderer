#ifndef _PGWBRIDGE_H_
#define _PGWBRIDGE_H_

/******************************************************************************
**
**   File:        FUBridge.h
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

#include "ODIComSession.h"
#include <IMsgReceiver.h>
#include "pgw.h"
#include <map>

namespace psc
{
class DataHandler;
struct FUDatabaseType;

/**
 * Provides a connection to non-asil functional units (like the FU Simulator in Populus Editor)
 *
 * Runs a TCP/IP server for connecting non-asil FUs or the FU Simulator in Populus Editor.
 * It filters messages which are not receivable by the PopulusSC Engine (e.g. list data, events, indications)
 * It also generates data request messages, which are expected by non-asil FUs before they send any data.
 */
class FUBridge : public IMsgReceiver
{
public:
    /**
     * Creates the FUBridge and starts the Server
     * @param ddh database which contains information about the FUs which are used by the Engine
     * @param port server port (TCP/IP)
     * @param dataHandler Reference to the dataHandler which shall receive the data
     */
    FUBridge(const FUDatabaseType* ddh, int port, DataHandler& dataHandler);
    ~FUBridge();

    /**
     * Receives messages from the socket.
     * The method waits for timeout milliseconds if no new data is available.
     * @param timeout timeout in milliseconds
     */
    PSCError handleIncomingData(uint32_t timeout);

private:
    // IMsgReceiver
    virtual PSCError onMessage(IMsgTransmitter* pMsgTransmitter, const U8 messageType, InputStream& stream) P_OVERRIDE;
    virtual void onConnect(IMsgTransmitter* pMsgTransmitter) P_OVERRIDE;
    virtual void onDisconnect(IMsgTransmitter* pMsgTransmitter) P_OVERRIDE;

    PSCError onRegistration(IMsgTransmitter*, InputStream& stream);
    PSCError onODI(IMsgTransmitter*, InputStream& stream);
    PSCError subscribeAll();
    void refresh();

    ODIComSession m_session;
    DataHandler& m_dataHandler;
    const FUDatabaseType* m_ddh;
    IMsgTransmitter *m_transmitter;
};

}

#endif // _PGWBRIDGE_H_
