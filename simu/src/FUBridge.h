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
**   This Source Code Form is subject to the terms of the Mozilla Public
**   License, v. 2.0. If a copy of the MPL was not distributed with this
**   file, You can obtain one at https://mozilla.org/MPL/2.0/.
**
**   SPDX-License-Identifier: MPL-2.0
**
******************************************************************************/

#include "ODIComSession.h"
#include <IMsgReceiver.h>
#include "pil.h"
#include <map>

namespace lsr
{
class DataHandler;

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
     * @param dataHandler Reference to the dataHandler which shall receive the data
     * @param port server port (TCP/IP)
     * @param hostname server ip (TCP/IP)
     */
    FUBridge(DataHandler& dataHandler, int port, const std::string& hostname);
    ~FUBridge();

    /**
     * Receives messages from the socket.
     * The method waits for timeout milliseconds if no new data is available.
     * @param timeout timeout in milliseconds
     */
    ComError handleIncomingData(uint32_t timeout);

private:
    // IMsgReceiver
    virtual ComError onMessage(IMsgTransmitter* const pMsgTransmitter, const U8 messageType, InputStream& stream) P_OVERRIDE;
    virtual void onConnect(IMsgTransmitter* const pMsgTransmitter) P_OVERRIDE;
    virtual void onDisconnect(IMsgTransmitter* const pMsgTransmitter) P_OVERRIDE;

    ComError onRegistration(IMsgTransmitter*, InputStream& stream);
    ComError onODI(IMsgTransmitter*, InputStream& stream);
    ComError onODIDynamicData(InputStream& stream);
    ComError subscribeAll();
    void refresh();

    ODIComSession m_session;
    DataHandler& m_dataHandler;
    IMsgTransmitter *m_transmitter;
};

}

#endif // _PILBRIDGE_H_
