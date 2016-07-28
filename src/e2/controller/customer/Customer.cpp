//
//  Customer.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/20/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Customer.hpp"
#include "Element.hpp"
#include "FabricAdjacency.hpp"
#include "IndexManager.h"
#include "E2Server.hpp"
#include "Fabric.hpp"

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

void
Customer::traceLog(std::string msg)
{
    std::string cmsg = "Customer<" + getName() + ">:" + msg;
    _logger->log(cmsg);
}
 