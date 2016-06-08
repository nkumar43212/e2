//
//  Element.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Element.hpp"

status_t
Element::activate()
{
    status_t status;
    
    status = add(_name, _mgmt_ip, this);
    if (status != EOK) {
        return status;
    }
    
    _status = ElementStatusOperational;
    return EOK;
}

void
Element::deactivate()
{
    remove(_name, _mgmt_ip);
    _status = ELementStatusInit;
}


