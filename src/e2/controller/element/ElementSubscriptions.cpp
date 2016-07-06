//
//  ElementSubscriptions.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/5/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <iostream>
#include "Service.hpp"
#include "ElementSubscriptions.hpp"

// Major subscriptions
std::string subscription_paths[] = {
    std::string("/interfaces"),
    std::string("/components")
};

int subscription_count = 2;

// Interests
SubscriptionInterest_t interest_list[] = {
    {
        .subscription_name = std::string("/interfaces"),
        .callback          = Element::interfacesCallback
    },
    
    {
        .subscription_name = std::string("/components"),
        .callback          = Element::inventoryCallback
    }
};
int interest_count = 2;