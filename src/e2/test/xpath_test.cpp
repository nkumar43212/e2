//
//  xpath_test.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "gtest/gtest.h"
#include "xpath_test.hpp"
#include "Xpath.h"

TEST_F(XpathTest, basic1) {
    std::string path("/components/component[name=\'Routing Engine0\']/properties/property");
    std::string name;
    bool found = xpath_get_name_token(path, name);
    EXPECT_TRUE(found);
    EXPECT_TRUE(name == "Routing Engine0");
}
