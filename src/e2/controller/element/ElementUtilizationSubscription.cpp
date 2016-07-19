//
//  ElementUtilizationSubscription.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>

#include "Element.hpp"
#include "Service.hpp"
#include "Xpath.h"

void
Element::utilizationCallback (Element *elementp, ServiceCallbackKeyValue *kv)
{
    // See any metric is interested to pick up this stat.
    std::string metric("memory-dram-used\']/state/value");
    if (kv->key.find(metric) == std::string::npos) {
        return;
    }
    
    // Extract the component reporting this metric
    std::string component;
    bool found = xpath_get_name_token(kv->key, component);
    if (!found) {
        return;
    }
    
    // Update the metrics value
    elementp->updateMetric(component, atoi(kv->str_value.c_str()));
}