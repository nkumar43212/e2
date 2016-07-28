//
//  Customer.hpp
//  e2
//
//  Created by NITIN KUMAR on 7/20/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef Customer_hpp
#define Customer_hpp

#include <stdio.h>
#include <iostream>
#include <map>
#include "CustomerProfile.hpp"
#include "CustomerContext.hpp"
#include "E2Types.h"
#include "Logger.hpp"

class Customer;
typedef std::map<std::string, Customer *>      CustomerDatabase;
typedef std::map<std::string, CustomerContext> CustomerPlacements;
typedef CustomerDatabase::iterator             CustomerDatabaseIterator;
typedef enum {
    CustomerStatusNull        = 0,
    CustomerStatusInit        = 1,
    CustomerStatusConnected   = 2,
    CustomerStatusOperational = 3,
    CustomerStatusDown        = 4
} CustomerStatus;
extern std::string CustomerStatusStrings[];

class Customer {
    std::string      _name;
    CustomerProfile  _profile;
    uint32_t         _id;
    CustomerStatus   _status;
    Logger *         _logger;
    
    // Placement contexts
    CustomerPlacements _placement;
    
public:
    Customer()
    {
        _status = CustomerStatusNull;
    }
    
    Customer(const std::string& name, CustomerProfile profile, uint32_t id, Logger *logger) :
        _name(name), _profile(profile), _id(id), _logger(logger)
    {
        _status = CustomerStatusNull;
    }
    
    // Accessors
    std::string getName ()            { return _name;                          }
    std::string getOperationalState() { return CustomerStatusStrings[_status]; }
    bool        isActive()            { return true;                           }
    uint32_t    getId()               { return _id;                            }
    uint32_t    getVlanId()           { return _profile.getVlanId();           }
    
    // Manage the customer databse
    static status_t  add(const std::string& name,
                         CustomerProfile& profile,
                         Logger *logger);
    static void      remove(const std::string& name);
    static bool      isPresent(const std::string& name);
    static Customer* find(const std::string& name);
    
    // Attrributes on a customer profile
    
    // Debug/Log Interface
    void traceLog(std::string msg);
    
    // Describe
    void description ()
    {
        std::cout << "Name   = " << getName() << "\n";
        std::cout << "ID     = " << getId()   << "\n";
        std::cout << "Status = " << getOperationalState() << "\n";
        std::cout << "Profile= \n";
        _profile.description();
    }
};
typedef std::map<std::string, Customer> CustomerList;

#endif /* Customer_hpp */
