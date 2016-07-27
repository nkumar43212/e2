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
#include "ServicePS.hpp"
#include "ServiceLag.hpp"

uint32_t
Element::getCustomerCount()
{
    return (uint32_t) _customer_list.size();
}

status_t
Element::addCustomer(std::string name)
{
    // If this is not a service element, bail
    if (getPersona() != ElementPersonaService) {
        traceLog("Element Type is not Service:" + std::to_string(getPersona()));
        return EFAIL;
    }
    
    // If already added, skip
    if (_customer_list.count(name) != 0) {
        return EOK;
    }
    
    // Create a Pseudo Service Interface
    Customer *cp = Customer::find(name);
    if (!cp) {
        return ENOENT;
    }
    ServiceOrder *ps_order = ServiceOrderPS::create(cp->getId(), "pseudo service interface:" + cp->getName());
    addServiceOrder(ps_order);
    
    // We are good
    _customer_list[name] = ElementStatusInit;
    return EOK;
}

status_t
Element::addCustomer(std::string name, const std::vector<std::string> port_list)
{
    // If this is not access element, bail
    if (getPersona() != ElementPersonaAccess) {
        traceLog("Element Type is not Access:" + std::to_string(getPersona()));
        return EFAIL;
    }
    
    // If already added, skip
    if (_customer_list.count(name) != 0) {
        return EOK;
    }
    
    // Create a LAG that represents the customer side
    std::string lag_name = "AE:Client:" + name;
    ServiceOrder *lag_order = ServiceOrderLag::create(lag_name);
    addServiceOrder(lag_order);
    delete lag_order;
    
    // Add all the elements in this port list
    for (std::vector<std::string>::const_iterator itr = port_list.begin(); itr != port_list.end(); itr++) {
        ServiceOrder *lag_order = ServiceOrderLag::create(lag_name, *itr);
        addServiceOrder(lag_order);
        delete lag_order;
    }
    
    // Create the customer vlan on the client interface
    Customer *cp = Customer::find(name);
    ServiceOrder *vlan_order = ServiceOrderVlan::create(lag_name, cp->getVlanId());
    addServiceOrder(vlan_order);
    
    // We are good
    _customer_list[name] = ElementStatusInit;
    return EOK;
}

void
Element::removeCustomer(std::string name)
{
    if (_customer_list.count(name) == 0) {
        return;
    }
    
    Customer *cp = Customer::find(name);
    if (!cp) {
        return;
    }
    
    // Depending on the personality of the element remove the customer context
    ServiceOrder *order;
    if (isService()) {
        order = ServiceOrderPS::create(cp->getId(), "pseudo service interface:" + cp->getName());
    } else {
        order = ServiceOrderLag::create("AE:Client:" + cp->getName());
        // De-member the lag interface
    }
    removeServiceOrder(order);
    delete order;
    
    _customer_list.erase(name);
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
        
        // Does the peer element figure in the name of the LAG
        std::size_t found = itr->second->getName().find(peer_element);
        if (found == std::string::npos) {
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