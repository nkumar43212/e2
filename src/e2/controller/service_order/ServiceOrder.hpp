//
//  ServiceOrder.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ServiceOrder_hpp
#define ServiceOrder_hpp

#include <iostream>
#include <stdio.h>
#include <vector>
#include "Logger.hpp"

class ServiceOrderParameter {
    std::string _name;
    std::string _value;
    
public:
    ServiceOrderParameter()
    {
    }
    
    ServiceOrderParameter(const std::string name, const std::string value) : _name(name), _value(value)
    {
    }
    
    std::string getName()  { return _name; }
    std::string getValue() { return _value; }
    
    };

typedef std::vector<ServiceOrderParameter> ServiceOrderParameterList;
class ServiceOrder {
     ServiceOrderParameterList _list;
    
public:
    ServiceOrder(ServiceOrderParameterList list) : _list(list)
    {
    }
    void traceLog(Logger *logger, std::string log_prefix = "");
};


#endif /* ServiceOrder_hpp */
