//
//  main.cpp
//
//
//  Created by NITIN KUMAR on 5/13/16.
//  Copyright © 2016 Andrzej Szyszko. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "gtest/gtest.h"

int main(int argc, const char * argv[])
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}