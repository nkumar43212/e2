//
//  ServiceOrder.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "ServiceOrder.hpp"

void
ServiceOrder::traceLog (Logger *logger, std::string log_prefix)
{
    for (ServiceOrderParameterList::iterator itr = _list.begin(); itr != _list.end(); itr++) {
        logger->log(log_prefix + (*itr).getName() + ":" + (*itr).getValue());
    }
}