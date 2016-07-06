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

class ElementInterface {
    std::string _name;
    uint32_t    _index;
    time_t      _timev;
    
public:
    ElementInterface (std::string name, uint32_t index)
    {
        _name = name;
        _index = index;
        time(&_timev);
    }
    
    ~ElementInterface()
    {
    }

    // Accessors
    std::string getName()         { return _name;  }
    uint32_t    getIndex()        { return _index; }
    time_t      getCreateTime()   { return _timev; }
    
    // Pretty print
    void description()
    {
        std::cout << "Name = " << getName() << "\n";
        std::cout << "  Id = " << getIndex() << "\n";
        std::cout << "  Init Time = " << getCreateTime() << "\n";
    }
};

#endif /* ElementInterface_hpp */
