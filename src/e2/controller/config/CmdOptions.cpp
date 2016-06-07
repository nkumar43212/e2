//
//  CmdOptions.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <iostream>
#include <unistd.h>
#include "CmdOptions.hpp"

void
CmdOptions::setLogFile (std::string logfile)
{
    std::string *str = new std::string(logfile);
    _logfile = (char *) str->c_str();
}

void
CmdOptions::setFileMode (bool mode)
{
    _file_mode = mode;
}

void
CmdOptions::setFileName (std::string file)
{
    std::string *str = new std::string(file);
    _system_file_name = (char *) str->c_str();
}

void
CmdOptions::setNullMode (bool mode)
{
    _null_mode = mode;
}

void
CmdOptions::setProcMode (bool mode)
{
    _proc_mode = mode;
}

void
CmdOptions::setINIConfigFile (std::string ini_config_file)
{
    std::string *str = new std::string(ini_config_file);
    _ini_config_file = (char *) str->c_str();
}

void
CmdOptions::printUsage (void)
{
    std::cout << "Usage: agent_server [-u/-h] [-n] [-p] [-f] <filename> "
    "[-l] <logfile> "
    "[-c] <ini config file>" << std::endl;
    std::cout << " -u/-h  : usage" << std::endl;
    std::cout << "    -n  : null mode" << std::endl;
    std::cout << "    -f  : file mode" << std::endl;
    std::cout << "    -p  : proc mode" << std::endl;
    std::cout << "    -l  : log file" << std::endl;
    std::cout << "    -c  : ini config file" << std::endl;
}

void
CmdOptions::resetArgs (void)
{
    optind = 1;
}

bool
CmdOptions::parseArgs (int argc, const char *argv[])
{
    int c;
    while ((c =  getopt(argc, (char **) argv, "uhnpf:l:c:")) != -1) {
        switch (c) {
            case 'u':
            case 'h':
                printUsage();
                resetArgs();
                return false;
                
            case 'n':
                setNullMode(true);
                break;
                
            case 'p':
                setProcMode(true);
                break;
                
            case 'f': {
                setFileName(std::string(optarg));
                setFileMode(true);
                break;
            }
                
            case 'l': {
                setLogFile(std::string(optarg));
                break;
            }
                
            case 'c': {
                setINIConfigFile(std::string(optarg));
                break;
            }
                
            case '?':
                if ((optopt == 'c') || optopt == 'l' || optopt == 'f') {
                    std::cout << "Option -" << char(optopt) <<
                    " requires an argument." << std::endl;
                } else if (isprint (optopt)) {
                    std::cout << "Unknown Option" << std::endl;
                } else {
                    std::cout << "Unknown option character `\\x%x'." << optopt
                    << std::endl;
                }
                resetArgs();
                return false;
        }
    }
    
    if (optind < argc) {
        resetArgs();
        return false;
    }
    
    // Return the status correctly
    resetArgs();
    return true;
}

