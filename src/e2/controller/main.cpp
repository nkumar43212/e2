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
#include "E2Server.hpp"

void
RunServer (const Logger *logger,
           const std::string server_address)
{
    E2Server service(logger);
    ServerBuilder builder;
    
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);
    
    // Finally assemble the server.
    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    
    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int
main(int argc, const char * argv[])
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
    
    // Server connectivity
    std::string server_address(opts->getServerIpAddress());
    server_address += ":";
    server_address += std::to_string(opts->getServerPort());
 
    // Start the controller server
    RunServer(logger, server_address);
    return 0;
}