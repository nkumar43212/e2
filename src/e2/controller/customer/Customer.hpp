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
#include "E2Types.h"

class Customer;
typedef std::map<std::string, Customer *> CustomerDatabase;
typedef CustomerDatabase::iterator        CustomerDatabaseIterator;

class Customer {
    std::string     _name;
    CustomerProfile _profile;
    
public:
    Customer()
    {
    }
    
    Customer(const std::string& name, CustomerProfile profile) : _name(name), _profile(profile)
    {
    }
    
    // Accessors
    std::string getName ()            { return _name;  }
    std::string getOperationalState() { return "good"; }
    
    // Manage the customer databse
    static status_t add(const std::string& name, CustomerProfile& profile);
    static void     remove(const std::string& name);
    static bool     isPresent(const std::string& name);
    
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
