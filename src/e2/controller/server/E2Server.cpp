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
                      const NetworkElementList *request,
                      ConfigurationReply * reply)

{
    Element *elementp = NULL;
    std::string    err_str;
    status_t       status;
    E2::ReturnCode err_code;
    
    for (int i = 0; i < request->list_size(); i++) {
        const NetworkElement& element = request->list(i);
        
        // Make a note
        traceLogRPC("AddElement:" + element.name());
        
        // Map the persona value
        ElementPersona persona;
        switch (element.persona()) {
            case E2::NetworkElementType::ACCESS_NODE:  persona = ElementPersonaAccess; break;
            case E2::NetworkElementType::SERVICE_NODE: persona = ElementPersonaService; break;
            case E2::NetworkElementType::INTERNAL_NODE: persona = ElementPersonaInternal; break;
            default: persona = ElementPersonaNone;
        }
        
        // Create a new element
        elementp = new Element(element.name(), 0, element.mgmt_ip(), persona, _logger);
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
                         const NetworkElementList * request,
                         ConfigurationReply * reply)

{
    for (int i = 0; i < request->list_size(); i++) {
        const NetworkElement& element = request->list(i);
    
        // Make a note
        traceLogRPC("RemoveElement" + element.name());
        Element *elementp = Element::find(element.name(), element.mgmt_ip());
   
    
        if (!elementp) {
            reply->set_code(E2::ELEMENT_NOT_FOUND_ERROR);
            reply->set_code_str("Failed to find element");
            return Status::OK;
        }
    
        elementp->deactivate();
        delete elementp;
    }
    
    reply->set_code(E2::SUCCESS);
    return Status::OK;
}

Status
E2Server::getElements (ServerContext* context,
                       const NetworkElement * request,
                       NetworkElementOpStateList * reply)
{
    // Make a note
    traceLogRPC("GetElement");
    
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
                        const FabricLinkList * request,
                        ConfigurationReply * reply)
{
    std::string    err_str;
    status_t       status;
    E2::ReturnCode err_code;
    
    // Make a note
    traceLogRPC("AddFabricLink");
    
    for (int i = 0; i < request->list_size(); i++) {
        const E2::FabricLink& element = request->list(i);
        FabricLink *linkp = new FabricLink(element.name(), element.endpoint_1(), element.endpoint_2());
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
    
        traceLog("Added Fabric Link" + element.name() + ":" + element.endpoint_1() + "<->" + element.endpoint_2());
    }
    
    reply->set_code(E2::SUCCESS);
    return Status::OK;

error:
    reply->set_code(err_code);
    reply->set_code_str(err_str);
    return Status::OK;
}

Status
E2Server::addServiceEndpoint (ServerContext* context,
                              const ServiceEndpointList * request,
                              ConfigurationReply * reply)
{
    std::string    err_str;
    status_t       status = EOK;
    E2::ReturnCode err_code;
    
    // Make a note
    traceLogRPC("AddServiceEndPoint");
    
    // Go through all the services that have been sent in this request
    for (int i = 0; i < request->list_size(); i++) {
        const E2::ServiceEndpoint &ep = request->list(i);
        
        // Absorb this customer
        CustomerProfile profile(ep.vlan_identifier());
        status = Customer::add(ep.name(), profile, _logger);
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
                                 const ServiceEndpointList * request,
                                 ConfigurationReply * reply)
{
    // Make a note
    traceLogRPC("RemoveServiceEndPoint");
    
    // Go through all the services that have been sent in this request
    for (int i = 0; i < request->list_size(); i++) {
        const E2::ServiceEndpoint &ep = request->list(i);

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
    traceLogRPC("ActivateService");
    
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
    // Make a note
    traceLogRPC("TerminateService");
    
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