//
//  E2Client.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/7/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "E2Client.hpp"

E2Client *
E2Client::create (std::shared_ptr<Channel> channel,
                  std::string& name,
                  uint32_t id,
                  const std::string& logfile_dir)
{
    return new E2Client(channel, name, logfile_dir);
}

void
E2Client::addElement (std::string name, std::string mgmt_ip)
{
    // Send over the list request
    ClientContext        context;
    ConfigurationRequest request;
    NetworkElement       *element;
    ConfigurationReply   reply;
    
    element = request.mutable_element();
    element->set_name(name);
    element->set_mgmt_ip(mgmt_ip);
    stub_->addElement(&context, request, &reply);
}

void
E2Client::deleteElement(std::string name)
{
    // Send over the list request
    ClientContext        context;
    ConfigurationRequest request;
    NetworkElement       *element;
    ConfigurationReply   reply;
    
    element = request.mutable_element();
    element->set_name(name);
    stub_->removeElement(&context, request, &reply);
}

void
E2Client::listElements()
{
    // Send over the list request
    ClientContext        context;
    ConfigurationRequest request;
    ConfigurationReply   reply;
    NetworkElementOpStateList elementList;
    
    stub_->getElements(&context, request, &elementList);
    for (int i = 0; i < elementList.opstate_size(); i++) {
        const NetworkElementOpState& opstate = elementList.opstate(i);
        
        std::cout << "Element = " << opstate.element().name() << " [" << opstate.element().mgmt_ip() << "]\n";
        for (int j = 0; j < opstate.properties_size(); j++) {
            const NetworkElementProperty& property = opstate.properties(j);
            std::cout << "  " << property.name() << " = " << property.str_value() << "\n";
        }
    }
}

void
E2Client::addFabricLink (std::string name, std::string ep1, std::string ep2)
{
    // Send over the list request
    ClientContext        context;
    ConfigurationRequest request;
    NetworkElement       *element;
    ConfigurationReply   reply;
    
    element = request.mutable_element();
    element->set_name(name);
    element->set_mgmt_ip("");
    element->set_endpoint_1(ep1);
    element->set_endpoint_2(ep2);
    stub_->addFabricLink(&context, request, &reply);
}