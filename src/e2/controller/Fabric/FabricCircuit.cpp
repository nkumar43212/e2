//
//  FabricCircuit.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/27/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include <stdio.h>
#include "Fabric.hpp"
#include "FabricLink.hpp"
#include "Element.hpp"
#include "IndexManager.h"
#include "ServiceVlan.hpp"
#include "ServiceCC.hpp"

status_t
FabricLink::addCircuit (id_idx_t circuit_id)
{
    // Both sides of the link
    Element *e1, *e2;
    e1 = Element::find(getEndPoint1());
    e2 = Element::find(getEndPoint2());
    
    // On both sides of the link, create a pseudo fabric interface
    std::string fabric_if_name = "FAB:" + std::to_string(circuit_id);
    id_idx_t vlan_id = allocateCircuitId();
    
    ElementInterface *fabric_if = new ElementInterface(fabric_if_name, e1->allocateInterfaceIndex(), true);
    e1->addInterface(fabric_if);
    ServiceOrder *order = ServiceOrderVlan::create(fabric_if_name, vlan_id);
    e1->addServiceOrder(order);
    
    fabric_if = new ElementInterface(fabric_if_name, e2->allocateInterfaceIndex(), true);
    e2->addInterface(fabric_if);
    e2->addServiceOrder(order);
    
    // Create the cross connect between the customer and the fabric interface
    order = ServiceOrderCC::create(e1->getCustomerContextName(circuit_id), fabric_if_name);
    e1->addServiceOrder(order);
    
    order = ServiceOrderCC::create(e2->getCustomerContextName(circuit_id), fabric_if_name);
    e2->addServiceOrder(order);
    
    return EOK;
}

void
FabricLink::deleteCircuit (uint32_t circuit_id)
{
}