//
//  Xpath.cpp
//  e2
//
//  Created by NITIN KUMAR on 7/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "Xpath.h"

// Return the value of the name at the desired location
//"/components/component[name=\'Routing Engine0\']/properties/property[name=\'cpu-utilization-idle\']/state/value"
bool
xpath_get_name_token (const std::string& path, std::string& name, uint32_t location)
{
    std::string keyword("name=\'");
                        
    // Search for the first occurence
    std::size_t pos = path.find(keyword);
    if (pos == std::string::npos) {
        return false;
    }
    
    // Beginning of name
    name = path.substr(pos + keyword.length());
    pos  = name.find("']");
    if (pos == std::string::npos) {
        return false;
    }
    name.erase(pos);
    return true;
}
