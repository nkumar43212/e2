//
//  ErServerLog.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/25/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "E2Server.hpp"

void
E2Server::enableLog()
{
    _logger->enable();
}

void
E2Server::disableLog()
{
    _logger->disable();
}

void
E2Server::traceLog(const std::string msg)
{
    _logger->log(msg);
}

void
E2Server::traceLogRPC(const std::string rpc_name)
{
    _logger->log("\n\nRPC:" + rpc_name);
}