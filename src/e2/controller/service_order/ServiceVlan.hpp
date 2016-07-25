//
//  ServiceVlan.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/21/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ServiceVlan_hpp
#define ServiceVlan_hpp

#include <stdio.h>
#include "ServiceOrder.hpp"

class ServiceOrderVlan : public ServiceOrder {
public:
    static ServiceOrder *create(const std::string& name, uint32_t vlan_id);
};

#endif /* ServiceVlan_hpp */
