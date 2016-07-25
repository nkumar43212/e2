//
//  CustomerContext.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/22/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef CustomerContext_hpp
#define CustomerContext_hpp

#include <iostream>
#include <stdio.h>

class CustomerContext {
    bool     _is_valid;
    uint32_t _vlan;

public:
    CustomerContext(uint32_t vlan_id) : _vlan(vlan_id), _is_valid(true)
    {
    }
    CustomerContext()
    {
        _is_valid = false;
    }
    
    bool     isValid()     { return _is_valid; }
    uint32_t getVlanId()   { return _vlan;     }
    
    void description()
    {
        if (isValid()) {
            std::cout << "Context = vlan" << getVlanId() << "\n";
        }
    }
};

#endif /* CustomerContext_hpp */
