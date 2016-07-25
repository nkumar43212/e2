//
//  ElementLog.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/25/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "Element.hpp"

void
Element::enableLog()
{
    _logger->enable();
}

void
Element::disableLog()
{
    _logger->disable();
}

void
Element::traceLog (const std::string log_msg)
{
    std::string msg = getName() + ":" + log_msg;
    _logger->log(msg);
}


