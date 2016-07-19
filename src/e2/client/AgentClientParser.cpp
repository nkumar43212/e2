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
handle_add_element (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    clientp->addElement(argv[1], argv[2]);
}

void
handle_delete_element (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    clientp->deleteElement(argv[1]);
}

void
handle_list_element (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    clientp->listElements();
}

void
handle_add_fabric_link (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    clientp->addFabricLink(argv[1], argv[2], argv[3]);
}

// Add new commands here
entry_t agent_client_commands [] = {
    {
        .e_cmd     = std::string("add-element"),
        .e_argc    = 3,
        .e_help    = std::string("Add an element to E2"),
        .e_usage   = std::string("add-element <name> <mgmt-ip>"),
        .e_handler = handle_add_element
    },
    {
        .e_cmd     = std::string("delete-element"),
        .e_argc    = 2,
        .e_help    = std::string("delete an element from E2"),
        .e_usage   = std::string("delete-element <name>"),
        .e_handler = handle_delete_element
    },
    {
        .e_cmd     = std::string("list-element"),
        .e_argc    = 1,
        .e_help    = std::string("list elements from E2"),
        .e_usage   = std::string("list-element"),
        .e_handler = handle_list_element
    },
    
    {
        .e_cmd     = std::string("add-fabric-link"),
        .e_argc    = 4,
        .e_help    = std::string("Add fabric link connectivity between two elements"),
        .e_usage   = std::string("add-fabric-link <name> <ep1> <ep2>"),
        .e_handler = handle_add_fabric_link
    },
    
};

uint32_t agent_client_commands_count =
sizeof(agent_client_commands)/sizeof(entry_t);