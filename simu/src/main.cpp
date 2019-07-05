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

#include "FrameHandler.h"
#include "DataHandler.h"
#include "DisplayManager.h"
#include "Database.h"
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

struct DBConfig
{
    std::string ddhbin;
    std::string imgbin;

    DBConfig()
    :   ddhbin(""), imgbin("")
    {}
};

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
    DBConfig dbConfig;
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

    bool parseDBConfiguration(std::ifstream& cfgFile, DBConfig& config)
    {
        if (!parseConfig(cfgFile, "ddhbin", config.ddhbin))
        {
            return false;
        }

        if (!parseConfig(cfgFile, "imgbin", config.imgbin))
        {
            return false;
        }
        std::cout << "DB configuration: ddhbin: " << config.ddhbin << std::endl;
        std::cout << "DB configuration: imgbin: " << config.imgbin << std::endl;

        return true;
    }

    bool parseTCPConfiguration(std::ifstream& cfgFile, TCPConfig& config)
    {
        bool res = false;

        std::string tmp = "";
        if (!parseConfig(cfgFile, "port", tmp))
        {
            std::cerr << "Can't get \"port\" field." << std::endl;
            return false;
        }

        config.port = atoi(tmp.c_str());
        if (parseConfig(cfgFile, "hostname", tmp))
        {
            config.hostname = tmp;
            res = true;
        }

        std::cout << "TCP configuration: " << config.hostname << ":" <<
           config.port << std::endl;

        return res;
    }

    bool parseRenderConfiguration(std::ifstream& cfgFile, RenderConfig& config)
    {
        bool res = false;

        std::string tmp = "";
        if (parseConfig(cfgFile, "win_device", tmp))
        {
            config.fbDevice = atoi(tmp.c_str());
            res = true;
        }

        std::cout << "Render configuration: win_device: " << config.fbDevice << std::endl;

        return res;
    }

    bool parseVideoCheckerConfiguration(std::ifstream& cfgFile, VideoCheckerConfig& config)
    {
        bool res = false;

        std::string tmp = "";
        if (parseConfig(cfgFile, "check_device", tmp))
        {
            config.checkDev = tmp;
            res = true;
        }

        std::cout << "VideoChecker configuration: device to check: " << config.checkDev << std::endl;

        return res;
    }

    bool parseConfiguration(std::ifstream& cfgFile, LSRConfiguration& config)
    {
        if (!parseDBConfiguration(cfgFile, config.dbConfig))
        {
            return false;
        }

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

    // opens the database files from the file system and stores them in ddhbin, imgbin
    bool openDatabase(const DBConfig& config, const std::string& fileName, std::string& ddhbin, std::string& imgbin)
    {
        std::string ddhBinFile = config.ddhbin;
        std::string imgBinFile = config.imgbin;

    #ifdef WIN32
        size_t offset = fileName.find_last_of("\\/");
    #else
        size_t offset = fileName.find_last_of(L'/');
    #endif

        std::string filePath;
        if (offset != std::string::npos)
        {
            filePath = fileName.substr(0, offset + 1); // Include the \ at the end
        }

        makeAbsolutePath(ddhBinFile, filePath);
        makeAbsolutePath(imgBinFile, filePath);

        std::ifstream ddhifs(ddhBinFile.c_str(), std::ios::binary);
        if (!ddhifs)
        {
            std::cerr << "Could not open DDHBIN:" << ddhBinFile << std::endl;
        }
        std::ifstream imgifs(imgBinFile.c_str(), std::ios::binary);
        if (!imgifs)
        {
            std::cerr << "Could not open IMGBIN:" << imgBinFile << std::endl;
        }
        bool ret = false;
        if (ddhifs && imgifs)
        {
            ddhbin.assign((std::istreambuf_iterator<char>(ddhifs)), (std::istreambuf_iterator<char>()));
            imgbin.assign((std::istreambuf_iterator<char>(imgifs)), (std::istreambuf_iterator<char>()));
            ret = true;
        }
        return ret;
    }

    bool isErrorCritical(const LSRError& error)
    {
        bool res = false;
        switch (error)
        {
        case LSR_NO_ERROR:
        case LSR_DATASTATUS_NOT_AVAIABLE:
        case LSR_DATASTATUS_INCONSISTENT:
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
    std::string fileName = "default.cfg";
    parseOptions(argc, argv, fileName);

    std::ifstream cfgFile(fileName.c_str());
    if (!cfgFile)
    {
        std::cerr << "Configuration file not found: " << fileName << std::endl;
        return 1;
    }

    LSRConfiguration configuration;
    if (!parseConfiguration(cfgFile, configuration))
    {
        std::cerr << "Can't parse configuration file." << std::endl;
        return 1;
    }

    std::string ddhbin = "";
    std::string imgbin = "";
    if (openDatabase(configuration.dbConfig, fileName, ddhbin, imgbin))
    {
        struct gil_config_t config;
        config.renderDevice = configuration.renderConfig.fbDevice;
        strncpy(config.checkDevice,
                configuration.vcConfig.checkDev.c_str(),
                std::min(sizeof(config.checkDevice), configuration.vcConfig.checkDev.size()));

        gilInit(&config);
        const lsr::ResourceBuffer ddh(ddhbin.c_str(), ddhbin.size());
        const lsr::ResourceBuffer img(imgbin.c_str(), imgbin.size());
        lsr::Database db(ddh, img);
        lsr::LSRErrorCollector err = db.getError();
        lsr::DataHandler dataHandler(db);
        lsr::FUBridge bridge(db.getDdh()->GetFUDatabase(),
                             configuration.tcpConfig.port,
                             configuration.tcpConfig.hostname,
                             dataHandler);
        lsr::DisplayManager dsp;
        lsr::FrameHandler frameHandler(db, dataHandler, dsp);
        if (!frameHandler.start())
        {
            err = LSR_UNKNOWN_ERROR;
        }

        while (!isErrorCritical(err.get()) && frameHandler.handleWindowEvents() == false)
        {
            err = bridge.handleIncomingData(30); //receive from Editor
            const U32 monotonicTime = pilGetMonotonicTime();
            frameHandler.update(monotonicTime);
            frameHandler.render();
            err = frameHandler.getError();
            if(!frameHandler.verify())
            {
                // error handling
            }
        }
        gilUninit();
        std::cerr << "Engine terminated with error code: " << err.get() << std::endl;
        return err.get();
    }
    return 0;
}
