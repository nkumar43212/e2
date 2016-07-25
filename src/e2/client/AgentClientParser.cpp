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

void
handle_place_service (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    std::vector<std::string> element_list;
    int n_elements = argc - 2;
    for (int i = 0; i < n_elements; i++) {
        element_list.push_back(argv[i+2]);
    }
    
    clientp->placeService(argv[1], argv[2], argv[3], argv[4], argv[5]);
}

void
handle_deplace_service (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    std::vector<std::string> element_list;
    int n_elements = argc - 2;
    for (int i = 0; i < n_elements; i++) {
        element_list.push_back(argv[i+2]);
    }
    
    clientp->deplaceService(argv[1], argv[2], argv[3], argv[4]);
}

void
handle_add_service (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    
    clientp->addService(argv[1], atoi(argv[2]));
}

void
handle_delete_service (int argc, const char *argv[])
{
    std::string e2_name("e2");
    
    E2Client *clientp = E2Client::create(grpc::CreateChannel(AGENT_SERVER_IP_PORT, grpc::InsecureCredentials()),
                                         e2_name, 0, parser->getLogDir());
    
    clientp->deleteService(argv[1]);
}

void
handle_basic_test (int argc, const char *argv[])
{
    // Create elements
    argc = 3;
    argv[0] = "add-element", argv[1] = "access1", argv[2] = "0.0.0.0";
    handle_add_element(argc, argv);
    
    argc = 3;
    argv[0] = "add-element", argv[1] = "access2", argv[2] = "0.0.0.0";
    handle_add_element(argc, argv);
    
    argc = 3;
    argv[0] = "add-element", argv[1] = "edge1", argv[2] = "0.0.0.0";
    handle_add_element(argc, argv);
    
    argc = 3;
    argv[0] = "add-element", argv[1] = "edge2", argv[2] = "0.0.0.0";
    handle_add_element(argc, argv);
    
    argc = 4;
    argv[0] = "add-fabric-link", argv[1] = "f1", argv[2] = "access1", argv[3] = "edge1";
    handle_add_fabric_link(argc, argv);
    
    argc = 4;
    argv[0] = "add-fabric-link", argv[1] = "f1", argv[2] = "access1", argv[3] = "edge2";
    handle_add_fabric_link(argc, argv);
  
    argc = 4;
    argv[0] = "add-fabric-link", argv[1] = "f1", argv[2] = "access2", argv[3] = "edge1";
    handle_add_fabric_link(argc, argv);
    
    argc = 4;
    argv[0] = "add-fabric-link", argv[1] = "f1", argv[2] = "access2", argv[3] = "edge2";
    handle_add_fabric_link(argc, argv);
    
    argc = 2;
    argv[0] = "add-service", argv[1] = "s1";
    handle_add_service(argc, argv);
    
    argc = 2;
    argv[0] = "add-service", argv[1] = "s2";
    handle_add_service(argc, argv);
    
    argc = 6;
    argv[0] = "place-service", argv[1] = "s1", argv[2] = "edge1", argv[3] = "edge2", argv[4] = "access1", argv[5] = "xe-0/0/0";
    handle_place_service(argc, argv);
    
    argc = 6;
    argv[0] = "place-service", argv[1] = "s2", argv[2] = "edge1", argv[3] = "edge2", argv[4] = "access2", argv[5] = "xe-0/0/0";
    handle_place_service(argc, argv);
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
    
    {
        .e_cmd     = std::string("add-service"),
        .e_argc    = 3,
        .e_help    = std::string("Add a service to E2"),
        .e_usage   = std::string("add-service <name> <vlan>"),
        .e_handler = handle_add_service
    },
    
    {
        .e_cmd     = std::string("delete-service"),
        .e_argc    = 2,
        .e_help    = std::string("Delete a service to E2"),
        .e_usage   = std::string("delete-service <name>"),
        .e_handler = handle_delete_service
    },
    
    {
        .e_cmd     = std::string("place-service"),
        .e_argc    = 6,
        .e_help    = std::string("Place a service to E2"),
        .e_usage   = std::string("place-service <name> <element1> <element2> <access_element> <access_port>"),
        .e_handler = handle_place_service
    },
    
    {
        .e_cmd     = std::string("deplace-service"),
        .e_argc    = 5,
        .e_help    = std::string("Displace Place a service to E2"),
        .e_usage   = std::string("deplace-service <name> <element1> <element2> <access_element>"),
        .e_handler = handle_deplace_service
    },
    
    {
        .e_cmd     = std::string("basic-test"),
        .e_argc    = 1,
        .e_help    = std::string("Basic Test"),
        .e_usage   = std::string("basic-test"),
        .e_handler = handle_basic_test
    },
    
};

uint32_t agent_client_commands_count =
sizeof(agent_client_commands)/sizeof(entry_t);