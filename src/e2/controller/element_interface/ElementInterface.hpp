//
//  ElementInterface.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ElementInterface_hpp
#define ElementInterface_hpp

#include <iostream>
#include <stdio.h>
#include <string>
#include "IndexManager.h"

class ElementInterface {
    std::string _name;
    uint32_t    _index;
    time_t      _timev;
    bool        _fabric;
    IdManager   _id_manager;
    
public:
    ElementInterface (std::string name, uint32_t index, bool fabric = false)
    {
        _name = name;
        _index = index;
        _fabric = fabric;
        time(&_timev);
    }
    
    ~ElementInterface()
    {
    }

    // Accessors
    std::string getName()                    { return _name;       }
    uint32_t    getIndex()                   { return _index;      }
    time_t      getCreateTime()              { return _timev;      }
    bool        isFabric()                   { return _fabric;     }
   
    // Allocate indices in the scope of this interface
    id_idx_t    allocateIndex()              { return _id_manager.allocate(); }
    void        deallocateIndex(id_idx_t id) { _id_manager.deallocate(id);   }
    
    // Pretty print
    
    void description()
    {
        std::string str = isFabric() ? "(F)" : "";
        
        std::cout << "Name = " << getName() + str << "\n";
        std::cout << "  Id = " << getIndex() << "\n";
        std::cout << "  Init Time = " << getCreateTime() << "\n";
    }
};

#endif /* ElementInterface_hpp */
