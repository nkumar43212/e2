//
//  ElementInterfaceSubscription.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/5/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "Element.hpp"
#include "Service.hpp"

void
Element::interfacesCallback (Element *elementp, ServiceCallbackKeyValue *kv)
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
    ElementInterface *ifp = new ElementInterface(if_name,
                                                 elementp->_interface_id_manager.allocate());
    if (ifp) {
        elementp->addInterface(ifp);
    }
}

