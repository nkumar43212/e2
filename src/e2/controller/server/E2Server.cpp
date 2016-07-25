//
//  E2Server.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "E2Server.hpp"
#include "Element.hpp"
#include "FabricLink.hpp"

Status
E2Server::addElement (ServerContext* context,
                      const ConfigurationRequest * request,
                      ConfigurationReply * reply)

{
    Element *elementp = NULL;
    std::string    err_str;
    status_t       status;
    E2::ReturnCode err_code;
    
    // Create a new element
    elementp = new Element(request->element().name(), 0, request->element().mgmt_ip(), _logger);
    if (!elementp) {
        err_str  = std::string("Memory Allocation Failure");
        err_code = E2::MEMORY_ERROR;
        goto error;
    }
    
    // Activate it
    status = elementp->activate();
    if (status != EOK) {
        err_str  = std::string("Activation Failure:") + std::to_string(status);
        err_code = E2::ACTIVATE_ERROR;
        goto error;
    }
    
    reply->set_code(E2::SUCCESS);
    return Status::OK;

error:
    reply->set_code(err_code);
    reply->set_code_str(err_str);
    if (elementp) {
        delete elementp;
    }
    return Status::OK;
}

Status
E2Server::removeElement (ServerContext* context,
                         const ConfigurationRequest * request,
                         ConfigurationReply * reply)

{
    Element *elementp = Element::find(request->element().name(), request->element().mgmt_ip());
   
    if (!elementp) {
        reply->set_code(E2::ELEMENT_NOT_FOUND_ERROR);
        reply->set_code_str("Failed to find element");
        return Status::OK;
    }
    
    elementp->deactivate();
    delete elementp;
    reply->set_code(E2::SUCCESS);
    return Status::OK;
}

Status
E2Server::getElements (ServerContext* context,
                       const ConfigurationRequest * request,
                       NetworkElementOpStateList * reply)
{
    // Retrieve the end node elements
    for (ElementDbIterator itr = Element::findFirst(); itr != Element::findLast(); itr++) {
        // Get the operational state for this element
        ElementOpstateList element_opstate;
        itr->second->getOperationalState(element_opstate);
        
        // Copy it over into the reply
        NetworkElementOpState *opstate = reply->add_opstate();
        NetworkElement *element = opstate->mutable_element();
        element->set_mgmt_ip(itr->second->getMgmtIp());
        element->set_name(itr->second->getName());
        for (ElementOpstateListIterator itr1 = element_opstate.begin(); itr1 != element_opstate.end(); itr1++) {
            NetworkElementProperty *property = opstate->add_properties();
            property->set_name(itr1->first);
            property->set_str_value(itr1->second);
        }
    }
    
    // Retrieve the fabric links
    for (FabricMapIterator itr = FabricLink::findFirst(); itr != FabricLink::findLast(); itr++) {
        // Get the operational state for this element
        ElementOpstateList element_opstate;
        itr->second->getOperationalState(element_opstate);
        
        // Copy it over into the reply
        NetworkElementOpState *opstate = reply->add_opstate();
        NetworkElement *element = opstate->mutable_element();
        element->set_name(itr->second->getName());
        for (ElementOpstateListIterator itr1 = element_opstate.begin(); itr1 != element_opstate.end(); itr1++) {
            NetworkElementProperty *property = opstate->add_properties();
            property->set_name(itr1->first);
            property->set_str_value(itr1->second);
        }
    }
    
    return Status::OK;
}

Status
E2Server::addFabricLink(ServerContext* context,
                        const ConfigurationRequest * request,
                        ConfigurationReply * reply)
{
    std::string    err_str;
    status_t       status;
    E2::ReturnCode err_code;
    
    FabricLink *linkp = new FabricLink(request->element().name(), request->element().endpoint_1(), request->element().endpoint_2());
    if (!linkp) {
        err_str  = std::string("Memory Allocation Failure");
        err_code = E2::MEMORY_ERROR;
        goto error;

    }
    
    status = linkp->activate();
    if (status != EOK) {
        err_str  = std::string("Activation Failure:") + std::to_string(status);
        err_code = E2::ACTIVATE_ERROR;
        goto error;
    }
    
    traceLog("Added Fabric Link" + request->element().name() + ":" + request->element().endpoint_1() + "<->" + request->element().endpoint_2());
    reply->set_code(E2::SUCCESS);
    return Status::OK;

error:
    reply->set_code(err_code);
    reply->set_code_str(err_str);
    if (linkp) {
        delete linkp;
    }
    
    return Status::OK;
}

Status
E2Server::addServiceEndpoint (ServerContext* context,
                              const ServiceConfigurationRequest * request,
                              ConfigurationReply * reply)
{
    std::string    err_str;
    status_t       status = EOK;
    E2::ReturnCode err_code;
    
    // Go through all the services that have been sent in this request
    const ServiceEndpointList &services = request->services();
    for (int i = 0; i < services.list_size(); i++) {
        const E2::ServiceEndpoint &ep = services.list(i);
        
        // Absorb this customer
        CustomerProfile profile(ep.vlan_identifier());
        status = Customer::add(ep.name(), profile);
        if (status != EOK) {
        }
        traceLog("Add Service Endpoint:" + ep.name());
    }
    
    reply->set_code(E2::SUCCESS);
    return Status::OK;

error:
    reply->set_code(err_code);
    reply->set_code_str(err_str);
    return Status::OK;
}

Status
E2Server::removeServiceEndpoint (ServerContext* context,
                                 const ServiceConfigurationRequest * request,
                                 ConfigurationReply * reply)
{
    // Go through all the services that have been sent in this request
    const ServiceEndpointList &services = request->services();
    for (int i = 0; i < services.list_size(); i++) {
        const E2::ServiceEndpoint &ep = services.list(i);
        
        // Absorb this customer
        Customer::remove(ep.name());
        traceLog("Remove Service Endpoint:" + ep.name());
    }
    
    reply->set_code(E2::SUCCESS);
    return Status::OK;
}

Status
E2Server::activateService (ServerContext* context,
                           const ServicePlacementRequest *request,
                           ConfigurationReply * reply)
{
    std::string    err_str = "";
    status_t       status = EOK;
    Customer       *customer;
    
    // Make a note
    traceLog("ActivateService:ServiceName = " + request->service().name());
    traceLog("ActivateService:Access      = " + request->access_element().name());
    
    // Do we know about the service
    customer = Customer::find(request->service().name());
    if (!customer) {
        err_str  = "Service Not Found:" + request->service().name();
        reply->set_code(E2::SERVICE_NOT_FOUND_ERROR);
        reply->set_code_str(err_str);
        return Status::OK;
    }
    
    // Do we know about the access element
    Element *access_elementp = Element::find(request->access_element().name());
    if (!access_elementp) {
        reply->set_code(E2::ELEMENT_NOT_FOUND_ERROR);
        err_str = "Failed to find access element" + request->access_element().name();
        reply->set_code_str(err_str);
        return Status::OK;
    }
    
    // Do we know all the edge elements
    std::vector<Element *>edge_elements;
    const NetworkElementList& edge_list = request->edge_element_list();
    for (int i = 0; i < edge_list.list_size(); i++) {
        const NetworkElement &elt = edge_list.list(i);
        Element *element = Element::find(elt.name());
        if (!element) {
            reply->set_code(E2::ELEMENT_NOT_FOUND_ERROR);
            err_str = "Failed to find service element" + elt.name();
            reply->set_code_str(err_str);
            return Status::OK;
        }
        edge_elements.push_back(element);
        traceLog("ActivateService:Service      = " + elt.name());
    }
    
    // Activate the customer
    for (std::vector<Element *>::iterator itr = edge_elements.begin(); itr != edge_elements.end(); itr++) {
        status = customer->activate(request->access_element().name(), (*itr)->getName());
        if (status != EOK) {
            // Unwind
            err_str  = "Service Placement Error on Element:" + request->service().name() + "/" + (*itr)->getName();
            reply->set_code(E2::SERVICE_PLACEMENT_ERROR);
            reply->set_code_str(err_str);
            deactivateService(request);
            return Status::OK;
        }
    }
    
    // Place on the service edge
    Element *element;
    for (std::vector<Element *>::iterator itr = edge_elements.begin(); itr != edge_elements.end(); itr++) {
        element = *itr;
        status = element->addCustomer(request->service().name());
        if (status != EOK) {
            err_str  = "Service Placement Error on Element:" + request->service().name() + "/" + element->getName();
            reply->set_code(E2::SERVICE_PLACEMENT_ERROR);
            reply->set_code_str(err_str);
            deactivateService(request);
            return Status::OK;
        }
    }
    
    // Place on the access edge
    std::vector<std::string> port_list;
    for (int i = 0; i < request->access_port_list_size(); i++) {
        port_list.push_back(request->access_port_list(i));
    }
    status = access_elementp->addCustomer(request->service().name(), port_list);
    if (status != EOK) {
        err_str  = "Service Placement Error on Element:" + request->service().name() + "/" + access_elementp->getName();
        reply->set_code(E2::SERVICE_PLACEMENT_ERROR);
        reply->set_code_str(err_str);
        deactivateService(request);
        return Status::OK;
    }
    
    reply->set_code(E2::SUCCESS);
    return Status::OK;
}

Status
E2Server::deactivateService (ServerContext* context,
                             const ServicePlacementRequest *request,
                             ConfigurationReply * reply)
{
    deactivateService(request);
    reply->set_code(E2::SUCCESS);
    return Status::OK;
}

void
E2Server::deactivateService (const ServicePlacementRequest *request)
{
    traceLog("ActivateService:ServiceName = " + request->service().name());
    // Do we know about the service
    if (!Customer::isPresent(request->service().name())) {
        return;
    }
    
    // Do we know about the access element
    Element *access_elementp = Element::find(request->access_element().name());
    if (access_elementp) {
        access_elementp->removeCustomer(request->service().name());
    }
    
    // Do we know all the edge elements
    const NetworkElementList& edge_list = request->edge_element_list();
    for (int i = 0; i < edge_list.list_size(); i++) {
        const NetworkElement &elt = edge_list.list(i);
        Element *element = Element::find(elt.name());
        if (element) {
            element->removeCustomer(request->service().name());
        }
    }
}