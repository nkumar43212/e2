//
//  Metrics.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/16/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Metrics.hpp"

void
Metrics::update (uint64_t value)
{
    if (value >= _peak_value) {
        _peak_value = value;
    }
    
    if (value <= _min_value) {
        _min_value = value;
    }
    
    _current_value = value;
}

bool
Metrics::isGreen()
{
    return true;
}