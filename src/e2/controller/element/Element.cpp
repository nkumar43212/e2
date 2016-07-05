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
    ServiceArgs *service_args = new ServiceArgs(inventoryCallback, this);
    
    // Subscribe to the inventory service
    _inventory_subscription = Service::createSubscription("/interfaces", service_args);
    if (!_inventory_subscription) {
        return EFAIL;
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
    delete _inventory_subscription;
    remove(_name, _mgmt_ip);
    _status = ElementStatusInit;
}

void
Element::inventoryCallback (Element *elementp, ServiceCallbackKeyValue *kv)
{
    // We heard back. So the element is alive
    time_t t;
    time(&t);
    elementp->setLastUpdateTime(t);
    
    // We are only interested in collecting list of interfaces at this time
    std::string name_str("]/name");
    if (kv->key.find(name_str) == std::string::npos) {
        return;
    }
    std::string if_name = kv->str_value;
    
    // If interface already present, we are done
    if (elementp->isPresentInterface(if_name)) {
        return;
    }
    
    // Absorb this interface
    ElementInterface *ifp = new ElementInterface(if_name);
    if (ifp) {
        elementp->addInterface(ifp);
    }
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
    int count = 0;
    for (InterfaceListIterator itr = _interface_list.begin(); itr != _interface_list.end(); itr++) {
        opstate["opstate/interface/" + std::to_string(count++)] = itr->second->getName();
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
}

void
Element::removeInterface(std::string name)
{
    InterfaceListIterator itr = _interface_list.find(name);
    
    if (itr != _interface_list.end()) {
        delete itr->second;
        _interface_list.erase(itr);
    }
}

bool
Element::isPresentInterface(std::string name)
{
    return _interface_list.find(name) != _interface_list.end();
}


