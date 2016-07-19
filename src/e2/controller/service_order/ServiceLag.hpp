//
//  ServiceLag.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ServiceLag_hpp
#define ServiceLag_hpp

#include <stdio.h>
#include "ServiceOrder.hpp"

class ServiceOrderLag : public ServiceOrder {
public:
    
    static ServiceOrder *create(const std::string name);
};


#endif /* ServiceLag_hpp */
