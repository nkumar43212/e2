//
//  ServicePS.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/25/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "ServicePS.hpp"

ServiceOrder *
ServiceOrderPS::create (uint32_t unit, std::string description_str)
{
    ServiceOrderParameterList list;
    
    // Build the parameter list
    ServiceOrderParameter interface_name("name", "ps" + std::to_string(unit));
    ServiceOrderParameter description("description", description_str);
    list.push_back(interface_name);
    list.push_back(description);
    
    ServiceOrder *order = new ServiceOrder(list);
    if (!order) {
        return nullptr;
    }
    
    return order;
}