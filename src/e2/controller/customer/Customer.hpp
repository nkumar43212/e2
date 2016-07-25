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

class Customer;
typedef std::map<std::string, Customer *>      CustomerDatabase;
typedef std::map<std::string, CustomerContext> CustomerPlacements;
typedef CustomerDatabase::iterator             CustomerDatabaseIterator;

class Customer {
    std::string      _name;
    CustomerProfile  _profile;
    
    // Placement contexts
    CustomerPlacements _placement;
    
public:
    Customer()
    {
    }
    
    Customer(const std::string& name, CustomerProfile profile) : _name(name), _profile(profile)
    {
    }
    
    // Accessors
    std::string getName ()            { return _name;              }
    std::string getOperationalState() { return "good";             }
    bool        isActive()            { return true;               }
    
    // Manage the customer databse
    static status_t  add(const std::string& name, CustomerProfile& profile);
    static void      remove(const std::string& name);
    static bool      isPresent(const std::string& name);
    static Customer* find(const std::string& name);
    
    // Activate a customer
    status_t         activate(const std::string& access, const std::string& service);
    void             deactivate();
    
    // Attrributes on a customer profile
    
    // Describe
    void description ()
    {
        std::cout << "Name = " << getName() << "\n";
        std::cout << "Profile= \n";
        _profile.description();
    }
};
typedef std::map<std::string, Customer> CustomerList;

#endif /* Customer_hpp */
