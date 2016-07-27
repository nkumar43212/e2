//
//  Customer.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/20/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Customer.hpp"
#include "Element.hpp"
#include "FabricLink.hpp"
#include "IndexManager.h"
#include "E2Server.hpp"

std::string CustomerStatusStrings[] = {
    "Null",
    "Init",
    "Connected",
    "Operational",
    "Down"
};

CustomerDatabase customer_db;
IdManager        customer_id_mgr;

status_t
Customer::add (const std::string& name, CustomerProfile& profile, Logger *logger)
{
    status_t status;
    
    // Allocate a new customer ID.
    id_idx_t customer_id = customer_id_mgr.allocate();
    if (customer_id == customer_id_mgr.getNullIdentifier()) {
        return ENOMEM;
    }
    
    // Allocate the customer object
    Customer *cp = new Customer(name, profile, customer_id, logger);
    if (!cp) {
        status = ENOMEM;
        goto error;
    }
    
    // Make a note
    cp->traceLog("Allocated customer, id = " + std::to_string(customer_id));
    cp->traceLog("Customer Profile:Vlan:" + std::to_string(profile.getVlanId()));
    customer_db[name] = cp;
    return EOK;
    
error:
    customer_id_mgr.deallocate(customer_id);
    return status;
}


void
Customer::remove(const std::string& name)
{
    CustomerDatabaseIterator itr = customer_db.find(name);
    if (itr == customer_db.end()) {
        return;
    }
    
    itr->second->traceLog("Remove");
    customer_id_mgr.deallocate(itr->second->getId());
    delete itr->second;
    customer_db.erase(itr);
}

Customer *
Customer::find(const std::string& name)
{
    CustomerDatabaseIterator itr = customer_db.find(name);
    
    return itr != customer_db.end() ? itr->second : nullptr;
}

bool
Customer::isPresent(const std::string& name)
{
    return (find(name) != nullptr) ? true : false;
}

status_t
Customer::activate(const std::string& access, const std::string &service)
{
    traceLog("Activate on Access = " + access + ", service = " + service);
    
    // Locate the fabric link that connects these two end points
    FabricLink *fp = FabricLink::findMap(access, service);
    if (!fp) {
        traceLog("Failed to find fabric link");
        return ENOENT;
    }
    
    // Allocate a context
    id_idx_t circuit_id = fp->allocateCircuitId();
    CustomerContext context(circuit_id);
    _placement[fp->getName()] = context;
    traceLog("Allocated circuit id = " + std::to_string(circuit_id));
    
    // Provision Context on Access
    Element *element = Element::find(access);
    if (!element) {
        deactivate();
        return ENOENT;
    }
    element->addCustomerFabric(context.getVlanId(), service);
    
    // Provision Context on Service
    element = Element::find(service);
    if (!element) {
        deactivate();
        return ENOENT;
    }
    element->addCustomerFabric(context.getVlanId(), access);
    
    return EOK;
}

void
Customer::deactivate ()
{
}

void
Customer::traceLog(std::string msg)
{
    std::string cmsg = "Customer<" + getName() + ">:" + msg;
    _logger->log(cmsg);
}
 