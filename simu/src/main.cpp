/******************************************************************************
**
**   File:        main.cpp
**   Description: psc_simu executable
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

#include "FrameHandler.h"
#include "DataHandler.h"
#include "DisplayManager.h"
#include "Database.h"
#include "FUBridge.h"
#include "OdiTypes.h"
#include "DDHType.h"
#include "PSCErrorCollector.h"
#include <pgw.h>
#include <pgl.h>
#include <stdlib.h>
#include <stdio.h>
#include <getopt.h>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

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
        printf("Luxoft Populus SC simulation engine\n");
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

    // Find ddhbin, imgbin filenames from Engine configuration file
    void parseConfig(std::istream& cfgfile, std::string& ddhbin, std::string& imgbin)
    {
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

            if (id == "ddhbin")
            {
                ddhbin = val;
            }
            else if (id == "imgbin")
            {
                imgbin = val;
            }
        }
    }

    // opens the database files from the file system and stores them in ddhbin, imgbin
    bool openDatabase(std::ifstream& cfgFile, const std::string& fileName, std::string& ddhbin, std::string& imgbin)
    {
        std::string ddhBinFile = "<ddhbin>";
        std::string imgBinFile = "<imgbin>";
        parseConfig(cfgFile, ddhBinFile, imgBinFile);

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
}

int main(int argc, char* argv[])
{
    const int port = 29101;
    std::string fileName = "default.cfg";
    parseOptions(argc, argv, fileName);

    std::ifstream cfgFile(fileName.c_str());
    if (!cfgFile)
    {
        std::cerr << "Config file not found: " << fileName << std::endl;
        return 1;
    }
    std::string ddhbin;
    std::string imgbin;
    if (openDatabase(cfgFile, fileName, ddhbin, imgbin))
    {
        pglInit();
        const psc::ResourceBuffer ddh(ddhbin.c_str(), ddhbin.size());
        const psc::ResourceBuffer img(imgbin.c_str(), imgbin.size());
        psc::Database db(ddh, img);
        psc::PSCErrorCollector err = db.getError();
        psc::DataHandler dataHandler(db);
        psc::FUBridge bridge(db.getDdh()->GetFUDatabase(), port, dataHandler);
        psc::DisplayManager dsp;
        psc::FrameHandler frameHandler(db, dataHandler, dsp);
        if (!frameHandler.start())
        {
            err = PSC_UNKNOWN_ERROR;
        }

        while (PSC_NO_ERROR == err.get() && frameHandler.handleWindowEvents() == false)
        {
            err = bridge.handleIncomingData(30); //receive from Editor
            const U32 monotonicTime = pgwGetMonotonicTime();
            frameHandler.update(monotonicTime);
            frameHandler.render();
            err = frameHandler.getError();
            if(!frameHandler.verify())
            {
                // error handling
            }
        }
        std::cerr << "Engine terminated with error code: " << err.get() << std::endl;
        return err.get();
    }
    return 0;
}
