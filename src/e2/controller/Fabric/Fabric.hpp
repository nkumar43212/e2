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

class FabricLink;
typedef std::map<std::string, FabricLink *>::iterator FabricMapIterator;

class Fabric {
    
    // Provision LAGs on the fabric link
    status_t    addLagBundle(const std::string& element_name);
    void        removeLagBundle(const std::string& element_name);
    
public:
    // Manage map database
    static FabricLink *findMap(const std::string& name);
    static FabricLink *findMap(const std::string& ep1, const std::string ep2);
    static status_t    addMap(FabricLink *);
    static void        removeMap(FabricLink *);
    static             FabricMapIterator findFirst(void);
    static             FabricMapIterator findLast(void);
    
    // Provision circuits on the fabric
    static status_t    bindCircuit(uint32_t circuit_id, FabricLink& fabric_link);
    static void        unBindCircuit(uint32_t circuit_id);
};


#endif /* Fabric_hpp */
