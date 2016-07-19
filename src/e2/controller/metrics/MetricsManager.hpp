//
//  MetricsManager.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef MetricsManager_hpp
#define MetricsManager_hpp

#include <stdio.h>
#include "Metrics.hpp"

class MetricsManager {
    // All the metrics being tracked by the manager
    MetricsList   _list;
    
public:
    // Manage the content
    void add(const std::string &name, Metrics& metric);
    void remove(const std::string &name);
   
    // Iterate through the metrics
    MetricsListIterator getBegin();
    MetricsListIterator getEnd();
    
    // Query
    bool isGreen(const std::string &name);
};


#endif /* MetricsManager_hpp */
