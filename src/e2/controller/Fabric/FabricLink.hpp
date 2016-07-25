//
//  FabricLink.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef FabricLink_hpp
#define FabricLink_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "E2Types.h"
#include "IndexManager.h"

class FabricLink;
typedef std::map<std::string, FabricLink *>::iterator FabricMapIterator;

class FabricLink {
    std::string _name;
    std::string _ep1;
    std::string _ep2;
    IdManager   _circuit_manager;
    
    // Provision LAGs on the fabric link
    status_t    addLagBundle(const std::string& element_name);
    void        removeLagBundle(const std::string& element_name);

public:
    FabricLink()
    {
    }
    FabricLink(const std::string name, const std::string ep1, const std::string ep2)
    : _name(name), _ep1(ep1), _ep2(ep2)
    {
    }
    
    // Accessors
    std::string getName()       { return _name; }
    std::string getEndPoint1()  { return _ep1;  }
    std::string getEndPoint2()  { return _ep2;  }
    
    // Manage map database
    static FabricLink *findMap(const std::string& name);
    static FabricLink *findMap(const std::string& ep1, const std::string ep2);
    static status_t    addMap(FabricLink *);
    static void        removeMap(FabricLink *);
    static             FabricMapIterator findFirst(void);
    static             FabricMapIterator findLast(void);
    
    // Get a list of operational state values for this element
    void               getOperationalState(ElementOpstateList &list);

    // Manage link
    status_t           activate();
    void               deactivate();
    
    // Manage circuit IDs on a link
    id_idx_t           allocateCircuitId()              { return _circuit_manager.allocate(); }
    void               deallocateCircuitId(id_idx_t id) { _circuit_manager.deallocate(id);    }
};

#endif /* FabricLink_hpp */
