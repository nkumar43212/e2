//
//  Config.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include <string>
#include "Config.hpp"
#include "INIReader.h"

CmdOptions *
Config::createConfig (int argc, const char *argv[])
{
    // Allocate the options
    CmdOptions *opts = new CmdOptions;
    if (!opts) {
        return NULL;
    }
    
    // Parse any command line options
    if (!opts->parseArgs (argc, argv)) {
        goto error;
    }
    
    // If there is no init configuration file, we are done
    char *ini_config_file;
    if (!(ini_config_file = opts->getIniConfigFile())) {
        return opts;
    }
    
    // Parse the init file
    if (!parseConfig(ini_config_file, opts)) {
        std::cerr << "INI config file parse failed" << std::endl;
        goto error;
    }
  
    return opts;
    
error:
    delete opts;
    return NULL;
}

bool
Config::parseConfig(const char *config_filename,
                    CmdOptions *opts)
{
    INIReader reader(config_filename);
    
    // Did it parse OK ?
    if (reader.ParseError() < 0) {
        std::cout << "Can't load INI file = " << config_filename << std::endl;
        return false;
    }
    
    // See if the log file name is given. If the log file already present in command line, then don't
    // override
    if (opts->getLogFile() != std::string("")) {
        std::string path  = reader.Get(INI_SECTION_LOGGING, "log_file_path", Config::getDefaultLogPath());
        std::string fname = reader.Get(INI_SECTION_LOGGING, "log_file_name", Config::getDefaultLogFileName());
        opts->setFileName(path + "/" + fname);
    }
    
    // Server Connectivity options
    std::string ip_addr = reader.Get(INI_SECTION_CONN, "server_ip", Config::getDefaultIpAddress());
    opts->setServerIpAddress(ip_addr);
    u_int16_t   port    = reader.GetInteger(INI_SECTION_CONN, "server_port", Config::getDefaultPort());
    opts->setServerPort(port);

    return true;
}
