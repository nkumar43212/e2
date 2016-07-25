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
#include "ServiceVlan.hpp"

uint32_t
Element::getCustomerCount()
{
    return (uint32_t) _customer_list.size();
}

status_t
Element::addCustomer(std::string name)
{
    // If already added, skip
    if (_customer_list.count(name) != 0) {
        return EOK;
    }
    
    // We are good
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

status_t
Element::addCustomerFabric (uint32_t circuit_id, std::string peer_element)
{
    // Iterate through all the LAG interfaces
    for (InterfaceListIterator itr = _interface_list.begin(); itr != _interface_list.end(); itr++) {
        // Skip non fabric interfaces
        if (!itr->second->isFabric()) {
            continue;
        }
        
        // Punch in the service order
        ServiceOrder *vlan_order = ServiceOrderVlan::create(itr->first, circuit_id);
        addServiceOrder(vlan_order);
        return EOK;
    }
    
    return ENOENT;
}

void
Element::deleteCustomerFabric (uint32_t circuit_id, std::string peer_element)
{
    // Iterate through all the LAG interfaces
    for (InterfaceListIterator itr = _interface_list.begin(); itr != _interface_list.end(); itr++) {
        // Skip non fabric interfaces
        if (!itr->second->isFabric()) {
            continue;
        }
        
        // Punch in the service order
        ServiceOrder *vlan_order = ServiceOrderVlan::create(itr->first, circuit_id);
        removeServiceOrder(vlan_order);
    }
}