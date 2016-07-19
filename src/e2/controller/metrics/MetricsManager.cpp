//
//  MetricsManager.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "MetricsManager.hpp"

void
MetricsManager::add(const std::string &name, Metrics& metric)
{
    MetricsListIterator itr = _list.find(name);
    
    if (itr == _list.end()) {
        _list[name] = metric;
        return;
    }
    
    itr->second.update(metric.getCurrentValue());
}

void
MetricsManager::remove(const std::string &name)
{
}

MetricsListIterator
MetricsManager::getBegin()
{
    return _list.begin();
}

MetricsListIterator
MetricsManager::getEnd()
{
    return _list.end();
}

bool
MetricsManager::isGreen(const std::string& name)
{
    // Go through all the metrics and evaluate all the matching metrics
    for (MetricsListIterator itr = getBegin(); itr != getEnd(); itr++) {
        if (itr->first.find(name) == std::string::npos) {
            continue;
        }
        if (!itr->second.isGreen()) {
            return false;
        }
    }
    
    return true;
}