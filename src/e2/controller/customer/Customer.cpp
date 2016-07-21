//
//  Customer.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/20/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Customer.hpp"

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

bool
Customer::isPresent(const std::string& name)
{
    CustomerDatabaseIterator itr = customer_db.find(name);
    
    return itr != customer_db.end() ? true : false;
}
 