//
//  ElementTest.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/14/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "gtest/gtest.h"
#include "ElementTest.hpp"
#include "Element.hpp"
#include "Service.hpp"

TEST_F(ElementTest, single) {
    Element *elementp = new Element("test", 1, "0.0.0.0");
    
    EXPECT_TRUE(elementp != nullptr);
    EXPECT_TRUE(elementp->getStatus() == ElementStatusInit);
}

TEST_F(ElementTest, activate) {
    Element *elementp = new Element("test", 1, "0.0.0.0");
    EXPECT_TRUE(elementp != nullptr);
    
    elementp->activate();
    EXPECT_TRUE(elementp->getStatus() == ElementStatusOperational);
    
    Element *added_element = Element::find("test", "0.0.0.0");
    EXPECT_TRUE(added_element == elementp);
}

TEST_F(ElementTest, deactivate) {
    Element *elementp = new Element("test-1", 1, "0.0.0.0");
    EXPECT_TRUE(elementp != nullptr);
    
    elementp->activate();
    elementp->deactivate();
    EXPECT_TRUE(elementp->getStatus() == ElementStatusInit);
    
    Element *added_element = Element::find("test-1", "0.0.0.0");
    EXPECT_TRUE(added_element == nullptr);
}

TEST_F(ElementTest, inventory) {
    Element *elementp = new Element("test-1", 1, "0.0.0.0");
   
    elementp->activate();
    
    ServiceCallbackKeyValue kv("if1", "PORT");
    Element::inventoryCallback(elementp, &kv);
    ServiceCallbackKeyValue kv1("if2", "PORT");
    Element::inventoryCallback(elementp, &kv1);
    elementp->description();
}

TEST_F(ElementTest, inventory_1) {
    Element *elementp = new Element("test-1", 1, "0.0.0.0");
    
    elementp->activate();
    
    ServiceCallbackKeyValue kv("if1", "PORT");
    Element::inventoryCallback(elementp, &kv);
    ServiceCallbackKeyValue kv1("if2", "PORT");
    Element::inventoryCallback(elementp, &kv1);
    
    // Add an element again
    ServiceCallbackKeyValue kv2("if2", "PORT");
    Element::inventoryCallback(elementp, &kv2);
    
    elementp->description();
}

TEST_F(ElementTest, inventory_list) {
    Element *elementp = new Element("test-2", 1, "0.0.0.0");
    elementp->activate();
    ServiceCallbackKeyValue kv("if1", "PORT");
    Element::inventoryCallback(elementp, &kv);
    ServiceCallbackKeyValue kv1("if2", "PORT");
    Element::inventoryCallback(elementp, &kv1);

    // Find the above items
    ElementOpstateList list;
    elementp->getOperationalState(list);
    for (ElementOpstateListIterator itr1 = list.begin(); itr1 != list.end(); itr1++) {
        std::cout << itr1->first << " " << itr1->second << "\n";
    }
}





