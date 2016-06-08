//
//  main.cpp
//  client
//
//  Created by NITIN KUMAR on 6/7/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <iostream>
#include <sys/stat.h>
#include <iostream>
#include <cstdlib>
#include "E2Client.hpp"
#include "AgentClientParser.hpp"

// :-/ globals
extern uint32_t global_id;
AgentParser *parser;

int main(int argc, const char * argv[])
{
    std::string logfile_dir;
    
    // Get the Looging dir
    if (argc > 1) {
        logfile_dir = argv[1];
        // Add a '/' in the end of directory name given
        if (logfile_dir.back() != '/') {
            logfile_dir.push_back('/');
        }
    } else {
        // Validate if logger file was specified
        char *env_rp = std::getenv("ROOTPATH");
        if (env_rp != NULL) {
            // if ROOTPATH env variable is set, set default log path
            logfile_dir = (std::string)env_rp + "/logs/";
        } else {
            std::cerr << "Please setup ROOTPATH environment variable or run as"
            << "\"client_binary logfile_dir\"" << std::endl;
            exit(0);
        }
    }
    
    // Validate if directory
    struct stat sb;
    if (!(stat(logfile_dir.c_str(), &sb) == 0 && S_ISDIR(sb.st_mode))) {
        std::cout << "Either ROOTPATH set or argument passed is not a "
        << "valid directory = " << logfile_dir << std::endl;
        exit(0);
    }
    
    // Run a simple command line loop to test all
    parser = new AgentParser(logfile_dir);
    parser->parseLoop();
    
    return 0;
}
