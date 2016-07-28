//
//  Fabric.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/27/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef Fabric_hpp
#define Fabric_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "E2Types.h"
#include "IndexManager.h"

class FabricAdjacency;
typedef std::map<std::string, FabricAdjacency *>::iterator FabricMapIterator;

class Fabric {
    
    // Provision LAGs on the fabric link
    status_t    addLagBundle(const std::string& element_name);
    void        removeLagBundle(const std::string& element_name);
    
public:
    // Manage map database
    static FabricAdjacency *findMap(const std::string& name);
    static FabricAdjacency *findMap(const std::string& ep1, const std::string ep2);
    static status_t    addMap(FabricAdjacency *);
    static void        removeMap(FabricAdjacency *);
    static             FabricMapIterator findFirst(void);
    static             FabricMapIterator findLast(void);
    
    // Provision circuits on the fabric
    static status_t    bindCircuit(uint32_t circuit_id, FabricAdjacency& fabric_link);
    static void        unBindCircuit(uint32_t circuit_id);
};


#endif /* Fabric_hpp */
