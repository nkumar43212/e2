//
//  E2Server.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "E2Server.hpp"
#include "Element.hpp"

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
    elementp = new Element(request->element().name(), 0, request->element().mgmt_ip());
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
    ElementDbIterator itr;
    
    for (itr = Element::findFirst(); itr != Element::findLast(); itr++) {
        // NetworkElementOpState *opstate = reply->add_opstate();
    }
    
    return Status::OK;
}