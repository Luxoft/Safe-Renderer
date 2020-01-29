/******************************************************************************
**
**   File:        main.cpp
**   Description: lsr_simu executable
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

#include "HMIProject.h"
#include "Engine.h"
#include "FUBridge.h"
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
    void makeAbsolutePath(std::string& fileName, const std::string& filePath)
    {
        if (fileName.length() == 0)
        {
            // Do nothing
        }
        else if (fileName.length() > 2 && (fileName[0] == '\\' || fileName[1] == ':'))
        {
            // This path is already absolute.
        }
        else
        {
            fileName.insert(0, filePath);
        }
    }

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
        lsr::Engine engine(Telltales::getDDH());
        lsr::Engine::Error err = engine.getError();
        // Database errors are fatal (may yield undefined behaviour)
        if (!err.isError())
        {
            lsr::FUBridge bridge(Telltales::getDDH(),
                configuration.tcpConfig.port,
                configuration.tcpConfig.hostname,
                engine);

            while (!isErrorCritical(err) && engine.handleWindowEvents() == false)
            {
                static_cast<void>(bridge.handleIncomingData(30)); //receive from Editor
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
