//
//  ServiceCC.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/27/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "ServiceCC.hpp"

ServiceOrder *
ServiceOrderCC::create (std::string if1, std::string if2)
{
    ServiceOrderParameterList list;
    
    // Build the parameter list
    ServiceOrderParameter interface_name1("name-1", if1);
    ServiceOrderParameter interface_name2("name-2", if2);
    list.push_back(interface_name1);
    list.push_back(interface_name2);
    
    ServiceOrder *order = new ServiceOrder(list);
    if (!order) {
        return nullptr;
    }
    
    return order;
}