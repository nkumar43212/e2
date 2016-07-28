//
//  ServiceCC.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/27/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ServiceCC_hpp
#define ServiceCC_hpp

#include <stdio.h>
#include "ServiceOrder.hpp"

class ServiceOrderCC : public ServiceOrder {
public:
    static ServiceOrder *create(std::string if1, std::string if2);
};

#endif /* ServiceCC_hpp */
