//
//  AgentClientParser.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/7/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <unistd.h>
#include <atomic>
#include "E2Client.hpp"
#include "AgentClientParser.hpp"

// Subscription ID
uint32_t global_id;

// The global parser object
extern AgentParser *parser;

// Id for multiple subscription
std::atomic_int some_id(0);

void
handle_subscribe (int argc, const char *argv[])
{
}

// Add new commands here
entry_t agent_client_commands [] = {
    {
        .e_cmd     = std::string("subscribe"),
        .e_argc    = 4,
        .e_help    = std::string("Subscribe to a jvision sensor by specifying a list of paths"),
        .e_usage   = std::string("subscribe <subscription-name> <sample-frequency> <path>+"),
        .e_handler = handle_subscribe
    },
};

uint32_t agent_client_commands_count =
sizeof(agent_client_commands)/sizeof(entry_t);