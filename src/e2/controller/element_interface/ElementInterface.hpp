//
//  ElementInterface.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ElementInterface_hpp
#define ElementInterface_hpp

#include <stdio.h>
#include <string>

class ElementInterface {
    std::string _name;
    time_t      _timev;
    
public:
    ElementInterface (std::string name)
    {
        _name = name;
        time(&_timev);
    }
    
    ~ElementInterface()
    {
    }

    // Accessors
    std::string getName()         { return _name;  }
    time_t      getCreateTime()   { return _timev; }
};

#endif /* ElementInterface_hpp */
