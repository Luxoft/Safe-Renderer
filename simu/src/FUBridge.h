#ifndef _PILBRIDGE_H_
#define _PILBRIDGE_H_

/******************************************************************************
**
**   File:        FUBridge.h
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

#include "ODIComSession.h"
#include <IMsgReceiver.h>
#include "pil.h"
#include <map>

namespace lsr
{
class Engine;
struct DDHType;

/**
 * Provides a connection to non-asil functional units (like the FU Simulator in Populus Editor)
 *
 * Runs a TCP/IP server for connecting non-asil FUs or the FU Simulator in Populus Editor.
 * It filters messages which are not receivable by the LSR Engine (e.g. list data, events, indications)
 * It also generates data request messages, which are expected by non-asil FUs before they send any data.
 */
class FUBridge : public IMsgReceiver
{
public:
    /**
     * Creates the FUBridge and starts the Server
     * @param ddh database which contains information about the FUs which are used by the Engine
     * @param port server port (TCP/IP)
     * @param hostname server ip (TCP/IP)
     * @param dataHandler Reference to the dataHandler which shall receive the data
     */
    FUBridge(const DDHType* ddh, int port, const std::string& hostname, Engine& dataHandler);
    ~FUBridge();

    /**
     * Receives messages from the socket.
     * The method waits for timeout milliseconds if no new data is available.
     * @param timeout timeout in milliseconds
     */
    LSRError handleIncomingData(uint32_t timeout);

private:
    // IMsgReceiver
    virtual LSRError onMessage(IMsgTransmitter* const pMsgTransmitter, const U8 messageType, InputStream& stream) P_OVERRIDE;
    virtual void onConnect(IMsgTransmitter* const pMsgTransmitter) P_OVERRIDE;
    virtual void onDisconnect(IMsgTransmitter* const pMsgTransmitter) P_OVERRIDE;

    LSRError onRegistration(IMsgTransmitter*, InputStream& stream);
    LSRError onODI(IMsgTransmitter*, InputStream& stream);
    LSRError onODIDynamicData(InputStream& stream);
    LSRError subscribeAll();
    void refresh();

    ODIComSession m_session;
    Engine& m_dataHandler;
    const DDHType* m_ddh;
    IMsgTransmitter *m_transmitter;
};

}

#endif // _PILBRIDGE_H_
