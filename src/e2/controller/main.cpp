//
//  main.cpp
//  controller
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <iostream>
#include "Logger.hpp"
#include "CmdOptions.hpp"
#include "Config.hpp"

int main(int argc, const char * argv[])
{
    // Get all command line options
    CmdOptions *opts;
    opts = Config::createConfig(argc, argv);
    if (!opts) {
        std::cout << "Exiting: Failed to initialize configuration\n";
        exit(0);
    }
    
    // Start a logger
    Logger *logger = new Logger(opts->getLogFile());
    if (!logger) {
        std::cout << "Exiting: Failed to initialize logging subsystem\n";
        exit(0);
    }
    logger->enable();
    logger->log("hello");
    
    // Start the controller server
    return 0;
}