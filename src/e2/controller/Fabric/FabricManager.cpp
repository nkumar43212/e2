//
//  FabricManager.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "FabricLink.hpp"
#include <map>

// Store all the FabricLinks
std::map<std::string, FabricLink *> fabric_map;

FabricLink *
FabricLink::findMap (const std::string &name)
{
    std::string key = name;
    
    if (fabric_map.count(key) == 0) {
        return NULL;
    }
    
    return fabric_map[key];
}

FabricLink *
FabricLink::findMap (const std::string &ep1, const std::string ep2)
{
    for (FabricMapIterator itr = fabric_map.begin(); itr != fabric_map.end(); itr++) {
        if ((itr->second->getEndPoint1() == ep1) && (itr->second->getEndPoint2() == ep2)) {
            return itr->second;
        }
    }
    
    return nullptr;
}

status_t
FabricLink::addMap (FabricLink *link)
{
    if (fabric_map.count(link->getName()) != 0) {
        return EFAIL;
    }
    
    fabric_map[link->getName()] = link;
    return EOK;
}

void
FabricLink::removeMap (FabricLink *link)
{
    FabricMapIterator itr = fabric_map.find(link->getName());
    if (itr != fabric_map.end()) {
        fabric_map.erase(itr);
    }
}

FabricMapIterator
FabricLink::findFirst (void)
{
    return fabric_map.begin();
}

FabricMapIterator
FabricLink::findLast(void)
{
    return fabric_map.end();
}

