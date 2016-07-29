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
E2Client::addElement (std::string name, std::string mgmt_ip, uint8_t persona)
{
    // Send over the list request
    ClientContext        context;
    NetworkElementList   elements;
    NetworkElement       *element;
    ConfigurationReply   reply;
    
    element = elements.add_list();
    element->set_name(name);
    element->set_mgmt_ip(mgmt_ip);
    switch (persona) {
        case 0: element->set_persona(NetworkElementType::ACCESS_NODE); break;
        case 1: element->set_persona(NetworkElementType::SERVICE_NODE); break;
        case 2: element->set_persona(NetworkElementType::INTERNAL_NODE); break;
    }
    stub_->addElement(&context, elements, &reply);
}

void
E2Client::deleteElement(std::string name)
{
    // Send over the list request
    ClientContext        context;
    NetworkElementList   elements;
    NetworkElement       *element;
    ConfigurationReply   reply;
    
    element = elements.add_list();
    element->set_name(name);
    stub_->removeElement(&context, elements, &reply);
}

void
E2Client::listElements()
{
    // Send over the list request
    ClientContext        context;
    NetworkElement       element;
    ConfigurationReply   reply;
    NetworkElementOpStateList elementList;
    
    stub_->getElements(&context, element, &elementList);
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
E2Client::addFabricAdjacency (std::string name, std::string ep1, std::string ep2)
{
    // Send over the list request
    ClientContext        context;
    FabricAdjacencyList       fabric_list;
    FabricAdjacency           *element;
    ConfigurationReply   reply;
    
    element = fabric_list.add_list();
    element->set_name(name);
    element->set_endpoint_1(ep1);
    element->set_endpoint_2(ep2);
    stub_->addFabricAdjacency(&context, fabric_list, &reply);
}

void
E2Client::addService (std::string name, uint32_t vlan_identifier)
{
    // Send over the list request
    ClientContext               context;
    ConfigurationReply          reply;
    ServiceEndpointList         service_list;
    ServiceEndpoint *           servicep;
   
    servicep = service_list.add_list();
    servicep->set_name(name);
    servicep->set_vlan_identifier(vlan_identifier);
    stub_->addServiceEndpoint(&context, service_list, &reply);
}

void
E2Client::deleteService (std::string name)
{
    // Send over the list request
    ClientContext               context;
    ServiceEndpointList         service_list;
    ConfigurationReply          reply;
    ServiceEndpoint *           servicep;
    
    // Remove the service from the server
    servicep = service_list.add_list();
    servicep->set_name(name);
    stub_->removeServiceEndpoint(&context, service_list, &reply);
}

void
E2Client::addPhysicalAccess(std::string name, std::string element_name, std::string access_port)
{
    
}

void
E2Client::removePhysicalAccess(std::string name)
{
}

void
E2Client::placeService (std::string name,
                        std::string pe_1, std::string pe_2,
                        std::string access)
{
    // Send over the list request
    ClientContext               context;
    ServiceBinding              request;
    ConfigurationReply          reply;
    ServiceEndpoint *           servicep;
    NetworkElementList *        pe_elements;
    ServicePhysicalEndpoint *   accessp;
    
    // Name of the service
    servicep = request.mutable_service();
    servicep->set_name(name);
    
    // The elements where the service should be placed
    NetworkElement *elementp;
    pe_elements = request.mutable_edge_element_list();
    elementp    = pe_elements->add_list();
    elementp->set_name(pe_1);
    elementp    = pe_elements->add_list();
    elementp->set_name(pe_2);
    
    // Access attachment
    accessp    = request.mutable_access_element();
    accessp->set_name(access);
    stub_->activateService(&context, request, &reply);
}

void
E2Client::deplaceService (std::string name,
                        std::string pe_1, std::string pe_2,
                        std::string access)
{
    // Send over the list request
    ClientContext               context;
    ServiceBinding              request;
    ConfigurationReply          reply;
    ServiceEndpoint *           servicep;
    NetworkElementList *        pe_elements;
    ServicePhysicalEndpoint *   accessp;
    
    // Name of the service
    servicep = request.mutable_service();
    servicep->set_name(name);
    
    // The elements where the service should be placed
    NetworkElement *elementp;
    pe_elements = request.mutable_edge_element_list();
    elementp    = pe_elements->add_list();
    elementp->set_name(pe_1);
    elementp    = pe_elements->add_list();
    elementp->set_name(pe_2);
    
    // Access Element
    accessp    = request.mutable_access_element();
    accessp->set_name(access);
    stub_->deactivateService(&context, request, &reply);
}