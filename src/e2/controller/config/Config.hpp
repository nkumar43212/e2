//
//  Config.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef Config_hpp
#define Config_hpp

#include <stdio.h>
#include "CmdOptions.hpp"

#define INI_SECTION_LOGGING    "logging"
#define INI_SECTION_CONN       "connection"

class Config {

public:
    Config (CmdOptions *opts)
    {
    }
    ~Config()
    {
    }
    
    static CmdOptions *createConfig(int argc, const char *argv[]);
    static bool        parseConfig(const char *config_filename, CmdOptions *opts);
    
    // Default values
    static std::string getDefaultLogPath ()          { return "";        }
    static std::string getDefaultLogFileName ()      { return "e2.log";  }
    static u_int16_t   getDefaultPort ()             { return 50051;     }
    static std::string getDefaultIpAddress ()        { return "0.0.0.0"; }
    
    // Configuration options
    char * getLogFileName ()
    {
        return nullptr;
    }
};
#endif /* Config_hpp */
