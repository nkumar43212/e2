//
//  CustomerProfile.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/21/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef CustomerProfile_hpp
#define CustomerProfile_hpp

#include <iostream>
#include <stdio.h>


class CustomerProfile {
    u_int32_t _vlan_id;
    
public:
    CustomerProfile () : _vlan_id(0)
    {
    }
    
    CustomerProfile (u_int32_t vlan_id) : _vlan_id(vlan_id)
    {
    }
    
    void description()
    {
    }
};

#endif /* CustomerProfile_hpp */
