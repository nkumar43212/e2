//
//  ElementServiceOrder.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "Element.hpp"

status_t
Element::addServiceOrder(ServiceOrder *order)
{
    // Call the provisioning system to punch in the order
    return EOK;
}

status_t
Element::removeServiceOrder(ServiceOrder *order)
{
    // Call the provisioning system to punch in the order
    return EOK;
}

void
Element::serviceOrderCallback (Element *elementp, ServiceCallbackKeyValue *kv)
{
}

