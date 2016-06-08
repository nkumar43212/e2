//
//  ElementDb.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include <stdio.h>
#include "Element.hpp"
#include <map>

// Store all the elements
std::map<std::string, Element *> element_db;

Element *
Element::find (const std::string &name, const std::string &mgmt_ip)
{
    std::string key;
    Element::makeKey(key, name, mgmt_ip);
    
    if (element_db.count(key) == 0) {
        return NULL;
    }
    
    return element_db[key];
}

status_t
Element::add (const std::string &name, const std::string &mgmt_ip, Element *element)
{
    std::string key;
    Element::makeKey(key, name, mgmt_ip);
    
    if (element_db.count(key) != 0) {
        return EFAIL;
    }
    
    element_db[key] = element;
    return EOK;
}

void
Element::remove (const std::string &name, const std::string &mgmt_ip)
{
    std::string key;
    Element::makeKey(key, name, mgmt_ip);
    
    ElementDbIterator itr = element_db.find(key);
    if (itr != element_db.end()) {
        element_db.erase(itr);
    }
}

void
Element::print ()
{
    for (ElementDbIterator itr = element_db.begin(); itr != element_db.end(); itr++) {
        itr->second->description();
    }
}

void
Element::makeKey(std::string &key, const std::string &name, const std::string &mgmt_ip)
{
    key = name + ":" + mgmt_ip;
}

ElementDbIterator
Element::findFirst (void)
{
    return element_db.begin();
}

ElementDbIterator
Element::findLast(void)
{
    return element_db.end();
}

