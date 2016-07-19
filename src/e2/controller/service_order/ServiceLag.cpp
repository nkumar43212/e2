//
//  ServiceLag.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "ServiceLag.hpp"

ServiceOrder *
ServiceOrderLag::create (const std::string name)
{
    ServiceOrderParameterList list;
    
    // Build the parameter list
    ServiceOrderParameter interface_name("name", name);
    ServiceOrderParameter monit_protocol("protocol", "true");
    list.push_back(interface_name);
    list.push_back(monit_protocol);
    
    ServiceOrder *order = new ServiceOrder(list);
    if (!order) {
        return nullptr;
    }
    
    return order;
}