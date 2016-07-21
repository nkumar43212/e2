//
//  ElementCustomer.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/21/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>

#include <stdio.h>
#include "Element.hpp"

uint32_t
Element::getCustomerCount()
{
    return (uint32_t) _customer_list.size();
}

status_t
Element::addCustomer(std::string name)
{
    if (_customer_list.count(name) != 0) {
        return EOK;
    }
    _customer_list[name] = ElementStatusInit;
    
    return EOK;
}

status_t
Element::addCustomer(std::string name, const std::vector<std::string> port_list)
{
    addCustomer(name);
    return EOK;
}

void
Element::removeCustomer(std::string name)
{
    if (_customer_list.count(name) != 0) {
        _customer_list.erase(name);
    }
}