//
//  Element.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

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
    status_t status;
    
    // Subscribe to the inventory service
    _inventory_subscription = new Service("/chassis", inventoryCallback, this);
    if (_inventory_subscription) {
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
    _status = ELementStatusInit;
}

void
Element::inventoryCallback (Element *elementp, ServiceCallbackKeyValue *kv)
{
    // We are only interested in collecting list of interfaces at this time
    if (kv->key != "/chassis") {
        return;
    }
    
    // Absorb this interface
    ElementInterface * ifp = new ElementInterface(kv->str_value);
    elementp->updateInterface(ifp);
}


