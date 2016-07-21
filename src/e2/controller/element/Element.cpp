//
//  Element.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <string>
#include <sstream>
#include "Element.hpp"
#include "Service.hpp"
#include "ElementSubscriptions.hpp"

std::string ElementStatusStrings[] = {
    "Init",
    "Connected",
    "Operational",
    "Down"
};


status_t
Element::activate()
{
    status_t    status;
    
    // Create all subscriptions
    for (int i = 0; i < subscription_count; i++) {
        Service *service = Service::createSubscription(subscription_paths[i], this);
        _subscriptions[subscription_paths[i]] = service;
    }
    
    // Add all interests in the above services
    for (int i = 0; i < interest_count; i++) {
        SubscriptionInterest_t *ptr = &interest_list[i];
       
        // Find the service of interest
        for (std::map<std::string, Service *>::iterator itr = _subscriptions.begin(); itr != _subscriptions.end(); itr++) {
            if (itr->first != ptr->subscription_name) {
                continue;
            }
            Service *service = itr->second;
            ServiceInterest *interest = new ServiceInterest(ptr->callback, this);
            service->addInterest(interest);
        }
    }
    
    // Add the element to our store
    status = add(_name, _mgmt_ip, this);
    if (status != EOK) {
        return status;
    }
    
    // The element is operational
    _status = ElementStatusOperational;
    return EOK;
}

void
Element::deactivate()
{
    for (std::map<std::string, Service *>::iterator itr = _subscriptions.begin(); itr != _subscriptions.end(); itr++) {
        delete itr->second;
    }
    remove(_name, _mgmt_ip);
    _status = ElementStatusInit;
}

void
Element::getOperationalState (ElementOpstateList &opstate)
{
    // Connectivity details
    opstate["element/name"] = _name;
    opstate["element/mgmt"] = _mgmt_ip;
    
    // When did we last hear from the element
    std::stringstream ss;
    ss << _last_update_time;
    opstate["opstate/last_update_time"] = ss.str();
    
    // List of Interfaces
    opstate["opstate/interface/count"]  = std::to_string(getInterfaceCount());
    for (InterfaceListIterator itr = _interface_list.begin(); itr != _interface_list.end(); itr++) {
        opstate["opstate/interface/" + std::to_string(itr->second->getIndex())] = itr->second->getName();
    }
    
    // List of metrics
    for (MetricsListIterator itr = _metrics_list.getBegin(); itr != _metrics_list.getEnd(); itr++) {
        opstate["metrics/" + itr->first] = std::to_string(itr->second.getCurrentValue());
    }
    
    // List of customers
    opstate["opstate/customer/count"] = std::to_string(getCustomerCount());
    for (ElementCustomerListIterator itr = _customer_list.begin(); itr != _customer_list.end(); itr++) {
        opstate["opstate/customer/" + itr->first] = ElementStatusStrings[itr->second];
    }
}


void
Element::addInterface(ElementInterface *interface)
{
    InterfaceListIterator itr = _interface_list.find(interface->getName());
    
    // If interface already exists, preserve that
    if (itr != _interface_list.end()) {
        return;
    }
    
    // Add the new element
    _interface_list[interface->getName()] = interface;
    ++_interface_count;
}

void
Element::removeInterface(std::string name)
{
    InterfaceListIterator itr = _interface_list.find(name);
    
    if (itr != _interface_list.end()) {
        delete itr->second;
        _interface_list.erase(itr);
        --_interface_count;
    }
}

bool
Element::isPresentInterface(std::string name)
{
    return _interface_list.find(name) != _interface_list.end();
}

u_int32_t
Element::getInterfaceCount ()
{
    return _interface_count;
}

id_idx_t
Element::allocateInterfaceIndex ()
{
    return _interface_id_manager.allocate();
}


