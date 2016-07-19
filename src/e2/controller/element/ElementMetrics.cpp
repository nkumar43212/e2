//
//  ElementMetrics.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/7/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "Element.hpp"

void
Element::updateMetric(const std::string name, uint64_t value)
{
    Metrics m(name, value);
    _metrics_list.add(name, m);
}
