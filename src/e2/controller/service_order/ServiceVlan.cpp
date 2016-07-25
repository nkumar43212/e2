//
//  ServiceVlan.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/21/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "ServiceVlan.hpp"

ServiceOrder *
ServiceOrderVlan::create(const std::string& name, uint32_t vlan_id)
{
    ServiceOrderParameterList list;
    ServiceOrderParameter interface_name("name", name);
    ServiceOrderParameter vlan("vlan", std::to_string(vlan_id));
    list.push_back(interface_name);
    list.push_back(vlan);
    
    ServiceOrder *order = new ServiceOrder(list);
    if (!order) {
        return nullptr;
    }

    return order;
}