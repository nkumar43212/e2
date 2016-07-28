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

status_t
Element::bindCustomer(std::string name, std::vector<std::string> port_list)
{
    // If already added, skip
    if (_customer_list.count(name) != 0) {
        return EOK;
    }
    
    if (getPersona() == ElementPersonaService) {
        bindCustomerService(name);
    } else {
        bindCustomerAccess(name, port_list);
    }
    
    // We are good
    _customer_list[name] = ElementStatusInit;
    return EOK;
}

void
Element::unBindCustomer(std::string name)
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
        order = ServiceOrderPS::create(getServiceInterfaceNamePrefix(), cp->getId(),
                                       "pseudo service interface:" + cp->getName());
    } else {
        order = ServiceOrderLag::create("AE:Client:" + cp->getName());
        // De-member the lag interface
    }
    removeServiceOrder(order);
    delete order;
    
    _customer_list.erase(name);
}

status_t
Element::bindCustomerService(std::string name)
{
    // Create a Pseudo Service Interface
    Customer *cp = Customer::find(name);
    if (!cp) {
        return ENOENT;
    }
    ServiceOrder *ps_order = ServiceOrderPS::create(getServiceInterfaceNamePrefix(), cp->getId(),
                                                    "pseudo service interface:" + cp->getName());
    addServiceOrder(ps_order);
    return EOK;
}

status_t
Element::bindCustomerAccess(std::string name, const std::vector<std::string> port_list)
{
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
    return EOK;
}

uint32_t
Element::getCustomerCount()
{
    return (uint32_t) _customer_list.size();
}

std::string
Element::getCustomerContextName (uint32_t customer_id)
{
    std::string name_prefix;
    
    name_prefix = getPersona() == ElementPersonaAccess ? getAccessInterfaceNamePrefix() : getServiceInterfaceNamePrefix();
    return name_prefix + std::to_string(customer_id);
}
