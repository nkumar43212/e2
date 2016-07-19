//
//  service_test.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/14/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "gtest/gtest.h"
#include "Service.hpp"
#include "service_test.hpp"

TEST_F(ServiceTest, basic1) {
    Service *service;
    Element *element;
    std::string path("/components");
    
    service = Service::createSubscription(path, element);
    EXPECT_TRUE(service != nullptr);
}

TEST_F(ServiceTest, basic2) {
    Service *service;
    Element *element;
    std::string path("/components");
    
    // Create subscription
    service = Service::createSubscription(path, element);
    
    // Add an interest
    ServiceInterest *interest = new ServiceInterest(ServiceTest::ServiceCallback, element, "test-interest");
    service->addInterest(interest);
    
    // Is the interest present ?
    bool is_present = service->searchInterest(interest);
    EXPECT_TRUE(is_present);
}