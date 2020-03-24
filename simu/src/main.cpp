/******************************************************************************
**
**   File:        main.cpp
**   Description: lsr_simu executable
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

#include "HMIProject.h"
#include "Engine.h"
#include "FUBridge.h"
#include "DataHandler.h"
#include "OdiTypes.h"
#include "DDHType.h"
#include "LSRErrorCollector.h"
#include <pil.h>
#include <gil.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

#include <algorithm>

#include <imx6_rendering_configuration.h>


namespace fu
{
    static const U32 FUTELLTALES_BREAKON = 0x002a0001U;  // FU:42 DataId:1
    static const U32 FUTELLTALES_BREAKOFF = 0x002a0002U;  // FU:42 DataId:2
    static const U32 FUTELLTALES_AIRBAG = 0x002a0003U;  // FU:42 DataId:3

    // must be sorted by FUDataId
    static const lsr::DataHandler::DataEntryType dataIdList[] = {
        { FUTELLTALES_BREAKON, lsr::DATATYPE_BOOLEAN, 0U },
        { FUTELLTALES_BREAKOFF, lsr::DATATYPE_BOOLEAN, 0U },
        { FUTELLTALES_AIRBAG, lsr::DATATYPE_BOOLEAN, 0U },
    };
}

struct TCPConfig
{
    int port;
    std::string hostname;

    TCPConfig()
    : port(0), hostname("")
    {}
};

struct VideoCheckerConfig
{
    std::string checkDev;

    VideoCheckerConfig()
    : checkDev("")
    {}
};

struct RenderConfig
{
    int fbDevice;

    RenderConfig()
    : fbDevice(0)
    {}
};

struct LSRConfiguration
{
    TCPConfig tcpConfig;
    VideoCheckerConfig vcConfig;
    RenderConfig renderConfig;
};

namespace
{
    // Usage message and config options enum
    void usage(char* name)
    {
        printf("Luxoft Safe Renderer simulation engine\n");
        //printf("Version: %s.%s.%s\n", VersionInfo::GetMajorVersion(), VersionInfo::GetMinorVersion(), VersionInfo::GetPatchVersion());
        //printf("Git revision: %s\n", VersionInfo::GetGitVersion());
        printf("usage:\n");
        printf("    %s [-v] [-h] <configfile>\n", name);

        exit(0);
    }

    // Parse command line options
    void parseOptions(int argc, char* argv[], std::string& fileName)
    {
        char const * const options = "vhr:";
        struct option long_options[] =
        {
            { "version", no_argument, 0, 'v' },
            { "help", no_argument, 0, 'h' },
            { 0, 0, 0, 0 }
        };

        while (1)
        {
            int option_index = 0;
            int c = getopt_long(argc, argv, options, long_options, &option_index);

            if (c == -1)
            {
                break;
            }

            switch (c)
            {
            case 'p':
                break;
            case 'v': // print usage message
            case 'h':
            default:
               usage(argv[0]);
               break;
            }
        }

        if (argc - optind >= 2)
        {
            printf("\nerror: too many parameters\n\n");
            usage(argv[0]);
        }

        if (optind < argc)
        {
            fileName = argv[argc - 1];
        }
    }

    bool parseConfig(std::istream& cfgfile, std::string valueToSearch, std::string& value)
    {
        bool res = false;
        for (std::string line; std::getline(cfgfile, line);)
        {
            std::istringstream iss(line);
            std::string id, eq, val;

            if (!(iss >> id))
            {
                // error ?
            }
            else if (id[0] == '#')
            {
                continue;
            }
            else if (!(iss >> eq >> val >> std::ws) || eq != "=" || iss.get() != EOF)
            {
                // error ?
            }

            if (id == valueToSearch)
            {
                value = val;
                res = true;
                break;
            }
        }

        if (!res)
        {
            std::cerr << "Can't get \"" << valueToSearch << "\" field." << std::endl;
        }

        return res;
    }

    bool parseTCPConfiguration(std::ifstream& cfgFile, TCPConfig& config)
    {
        std::string tmp = "";
        config.port = 29101;
        config.hostname = "127.0.0.1";
        if (parseConfig(cfgFile, "port", tmp))
        {
            config.port = atoi(tmp.c_str());
        }

        if (parseConfig(cfgFile, "hostname", tmp))
        {
            config.hostname = tmp;
        }

        std::cout << "TCP configuration: " << config.hostname << ":" <<
           config.port << std::endl;

        return true;
    }

    bool parseRenderConfiguration(std::ifstream& cfgFile, RenderConfig& config)
    {
        std::string tmp = "";
        if (parseConfig(cfgFile, "win_device", tmp))
        {
            config.fbDevice = atoi(tmp.c_str());
        }

        std::cout << "Render configuration: win_device: " << config.fbDevice << std::endl;

        return true;
    }

    bool parseVideoCheckerConfiguration(std::ifstream& cfgFile, VideoCheckerConfig& config)
    {
        std::string tmp = "";
        if (parseConfig(cfgFile, "check_device", tmp))
        {
            config.checkDev = tmp;
        }

        std::cout << "VideoChecker configuration: device to check: " << config.checkDev << std::endl;

        return true;
    }

    bool parseConfiguration(std::ifstream& cfgFile, LSRConfiguration& config)
    {
        if (!parseTCPConfiguration(cfgFile, config.tcpConfig))
        {
            return false;
        }

        if (!parseRenderConfiguration(cfgFile, config.renderConfig))
        {
            return false;
        }

        if (!parseVideoCheckerConfiguration(cfgFile, config.vcConfig))
        {
            return false;
        }

        return true;
    }

    bool isErrorCritical(const lsr::Engine::Error& error)
    {
        bool res = false;
        switch (error.getValue())
        {
        case LSR_NO_ENGINE_ERROR:
        case LSR_ERR_DATASTATUS_NOT_AVAILABLE:
        case LSR_ERR_DATASTATUS_INCONSISTENT:
        {
            res = false;
            break;
        }
        default:
        {
            res = true;
            break;
        }
        }

        return res;
    }

    /**
     * Updates the HMI elements according to the stored values in the data handler
     */
    void updateHMI(Telltales::HMI& hmi, const lsr::DataHandler& dh)
    {
        lsr::Number airbagValue;
        lsr::Number breakOnValue;
        lsr::Number breakOffValue;
        const lsr::DataStatus airbagStatus = dh.getNumber(lsr::DynamicData(fu::FUTELLTALES_AIRBAG), airbagValue);
        const lsr::DataStatus breakOnStatus = dh.getNumber(lsr::DynamicData(fu::FUTELLTALES_AIRBAG), breakOnValue);
        const lsr::DataStatus breakOffStatus = dh.getNumber(lsr::DynamicData(fu::FUTELLTALES_AIRBAG), breakOffValue);
        // setup the reference images
        if (airbagStatus == lsr::DataStatus::VALID)
        {
            hmi.getReferencePanel_Airbag().setVisible(airbagValue.getBool());
        }
        else
        {
            hmi.getReferencePanel_Airbag().setVisible(true);
        }

        if ((breakOnStatus == lsr::DataStatus::VALID) && (breakOffStatus == lsr::DataStatus::VALID))
        {
            const bool vis = breakOnValue.getBool() || !breakOffValue.getBool();
            hmi.getReferencePanel_Break().setVisible(vis);
        }
        else
        {
            hmi.getReferencePanel_Break().setVisible(true);
        }

        // setup the bitmaps for drawing (fallback rendering is used)
        hmi.getContentPanel_Airbag().setVisible(hmi.getReferencePanel_Airbag().getVerificationErrors() > 10U);
        hmi.getContentPanel_Break().setVisible(hmi.getReferencePanel_Break().getVerificationErrors() > 5U);
    }
}

int main(int argc, char* argv[])
{
    std::string fileName;
    parseOptions(argc, argv, fileName);

    std::ifstream cfgFile(fileName.c_str());
    if (!cfgFile && !fileName.empty())
    {
        std::cerr << "Configuration file not found: " << fileName << std::endl;
    }

    LSRConfiguration configuration;
    if (!parseConfiguration(cfgFile, configuration))
    {
        std::cerr << "Can't parse configuration file." << std::endl;
        return 1;
    }

    {
        struct gil_config_t config;
        config.renderDevice = configuration.renderConfig.fbDevice;
        strncpy(config.checkDevice,
                configuration.vcConfig.checkDev.c_str(),
                std::min(sizeof(config.checkDevice), configuration.vcConfig.checkDev.size()));

        gilInit(&config);
        Telltales::HMI hmi;
        lsr::Engine engine(Telltales::getDDH(), hmi);
        lsr::Engine::Error err = engine.getError();
        // Database errors are fatal (may yield undefined behaviour)
        if (!err.isError())
        {
            lsr::DataHandler dataHandler(fu::dataIdList, sizeof(fu::dataIdList) / sizeof(fu::dataIdList[0]));
            lsr::FUBridge bridge(dataHandler,
                configuration.tcpConfig.port,
                configuration.tcpConfig.hostname);

            while (!isErrorCritical(err) && engine.handleWindowEvents() == false)
            {
                static_cast<void>(bridge.handleIncomingData(30)); //receive from Editor
                updateHMI(hmi, dataHandler);
                engine.render();
                err = engine.getError();
                if (!engine.verify())
                {
                    // error handling
                }
            }
        }
        gilUninit();
        std::cerr << "Engine terminated with error code: " << err.getValue() << std::endl;
        return err.getValue();
    }
    return 0;
}
