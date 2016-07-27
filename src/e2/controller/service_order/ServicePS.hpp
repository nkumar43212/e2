//
//  ServicePS.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/25/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ServicePS_hpp
#define ServicePS_hpp

#include <stdio.h>
#include "ServiceOrder.hpp"

class ServiceOrderPS : public ServiceOrder {
public:
    static ServiceOrder *create(uint32_t unit, std::string description);
};

#endif /* ServicePS_hpp */
