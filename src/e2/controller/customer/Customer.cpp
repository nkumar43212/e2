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

CustomerDatabase customer_db;

status_t
Customer::add (const std::string& name, CustomerProfile& profile)
{
    Customer *cp = new Customer(name, profile);
    if (!cp) {
        return ENOMEM;
    }
    
    customer_db[name] = cp;
    return EOK;
}


void
Customer::remove(const std::string& name)
{
    CustomerDatabaseIterator itr = customer_db.find(name);

    if (itr != customer_db.end()) {
        delete itr->second;
        customer_db.erase(itr);
    }
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
    CustomerDatabaseIterator itr = customer_db.find(name);
    
    return itr != customer_db.end() ? true : false;
}

status_t
Customer::activate(const std::string& access, const std::string &service)
{
    // Locate the fabric link that connects these two end points
    FabricLink *fp = FabricLink::findMap(access, service);
    if (!fp) {
        return ENOENT;
    }
    
    // Allocate a context
    id_idx_t circuit_id = fp->allocateCircuitId();
    CustomerContext context(circuit_id);
    _placement[fp->getName()] = context;
    
    // Provision this context on both sides
    Element *element = Element::find(access);
    if (!element) {
        deactivate();
        return ENOENT;
    }
    element->addCustomerFabric(context.getVlanId(), service);
    
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
 