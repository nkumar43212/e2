//
//  fabric_test.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/18/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "gtest/gtest.h"
#include "Element.hpp"
#include "FabricLink.hpp"
#include "fabric_test.hpp"

TEST_F(FabricTest, methods) {
    FabricLink *link = new FabricLink("f1", "node1", "node2");

    EXPECT_STREQ(link->getName().c_str(), "f1");
    EXPECT_STREQ(link->getEndPoint1().c_str(), "node1");
    EXPECT_STREQ(link->getEndPoint2().c_str(), "node2");
    FabricLink::addMap(link);
    FabricLink *linkp = FabricLink::findMap("f1");
    EXPECT_TRUE(linkp == link);
    
    FabricLink *link1p = FabricLink::findMap("node1", "node2");
    EXPECT_TRUE(link1p == link);
    
    ElementOpstateList opstate;
    link1p->getOperationalState(opstate);
    for (ElementOpstateListIterator itr = opstate.begin(); itr != opstate.end(); itr++) {
        if (itr->first == "element/fabric/name") {
            EXPECT_STREQ(itr->second.c_str(), "f1");
        }
        if (itr->first == "element/fabric/link") {
            EXPECT_STREQ(itr->second.c_str(), "node1<->node2");
        }
    }
}

TEST_F(FabricTest, basic) {
    Element *e1 = new Element("node21", 1, "0.0.0.0");
    e1->activate();
    
    Element *e2 = new Element("node22", 1, "0.0.0.0");
    e2->activate();
    
    // Add the link
    FabricLink *link = new FabricLink("f2", "node21", "node22");
    status_t status = link->activate();
    EXPECT_TRUE(status == EOK);
    EXPECT_TRUE(e1->getInterfaceCount() == 1);
    //e1->description();
    
    // Remove the link
    link->deactivate();
    EXPECT_TRUE(e1->getInterfaceCount() == 0);
}

TEST_F(FabricTest, multiple) {
    // Create 10 left nodes, 10 right nodes
    for (int i = 0; i < 10; i++) {
        std::string ep1 = "_node_left_" + std::to_string(i);
        std::string ep2 = "_node_right_" + std::to_string(i);
       
        Element *e1 = new Element(ep1, 1, "0.0.0.0");
        e1->activate();
        Element *e2 = new Element(ep2, 1, "0.0.0.0");
        e2->activate();
    }
    
    // Now create a full mesh
    for (int i = 0; i < 10; i++) {
        std::string ep1 = "_node_left_" + std::to_string(i);
        
        for (int j = 0; j < 10; j++) {
            std::string ep2 = "_node_right_" + std::to_string(j);
            std::string f   = "fabric" + std::to_string(i + j * 10);
            
            FabricLink *link = new FabricLink(f, ep1, ep2);
            link->activate();
        }
    }
    
    // There should be 10 interfaces on every element
    for (int i = 0; i < 10; i++) {
        Element *e = Element::find("_node_left_" + std::to_string(i));
        EXPECT_TRUE(e != nullptr);
        if (e) {
            EXPECT_TRUE(e->getInterfaceCount() == 10);
            //e->description();
        }
    }
    
    // Remove all the links
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::string f   = "fabric" + std::to_string(i + j * 10);
            
            FabricLink *link = FabricLink::findMap(f);
            EXPECT_TRUE(link != nullptr);
            if (link) {
                link->deactivate();
            }
        }
    }
    
    // There should be 10 interfaces on every element
    for (int i = 0; i < 10; i++) {
        Element *e = Element::find("_node_left_" + std::to_string(i));
        EXPECT_TRUE(e != nullptr);
        if (e) {
            EXPECT_TRUE(e->getInterfaceCount() == 0);
            //e->description();
        }
    }
}
