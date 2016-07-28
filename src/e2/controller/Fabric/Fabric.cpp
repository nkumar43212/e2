//
//  Fabric.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/27/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "Fabric.hpp"
#include "FabricAdjacency.hpp"
#include <map>

// Store all the FabricAdjacencys
std::map<std::string, FabricAdjacency *> fabric_map;

FabricAdjacency *
Fabric::findMap (const std::string &name)
{
    std::string key = name;
    
    if (fabric_map.count(key) == 0) {
        return NULL;
    }
    
    return fabric_map[key];
}

FabricAdjacency *
Fabric::findMap (const std::string &ep1, const std::string ep2)
{
    for (FabricMapIterator itr = fabric_map.begin(); itr != fabric_map.end(); itr++) {
        if ((itr->second->getEndPoint1() == ep1) && (itr->second->getEndPoint2() == ep2)) {
            return itr->second;
        }
    }
    
    return nullptr;
}

status_t
Fabric::addMap (FabricAdjacency *link)
{
    if (fabric_map.count(link->getName()) != 0) {
        return EFAIL;
    }
    
    fabric_map[link->getName()] = link;
    return EOK;
}

void
Fabric::removeMap (FabricAdjacency *link)
{
    FabricMapIterator itr = fabric_map.find(link->getName());
    if (itr != fabric_map.end()) {
        fabric_map.erase(itr);
    }
}

FabricMapIterator
Fabric::findFirst (void)
{
    return fabric_map.begin();
}

FabricMapIterator
Fabric::findLast(void)
{
    return fabric_map.end();
}
