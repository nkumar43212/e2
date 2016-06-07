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
    
    // Configuration options
    char * getLogFileName ()
    {
        return nullptr;
    }
};
#endif /* Config_hpp */
