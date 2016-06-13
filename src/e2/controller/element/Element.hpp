//
//  Element.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/8/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef Element_hpp
#define Element_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <map>
#include <vector>

#include "E2Types.h"
#include "ElementInterface.hpp"
#include "Connection.hpp"

// Types
class Element;
class Service;
class ServiceCallbackKeyValue;
typedef std::map<std::string, Element *>::iterator ElementDbIterator;
typedef std::map<std::string, ElementInterface *> InterfaceList;
typedef std::map<std::string, ElementInterface *>::iterator InterfaceListIterator;

// Status
typedef enum {
    ELementStatusInit        = 0,
    ElementStatusConnected   = 1,
    ElementStatusOperational = 2,
    ElementStatusDown        = 3
} ElementStatus;
extern std::string ElementStatusStrings[];

// Representation of a networking node in the domain managed by the E2 controller
class Element {
    // Identifiers
    std::string _name;
    uint64_t    _id;
    
    // Connectivity
    std::string _mgmt_ip;
    
    // Where is the element in its lifecycle
    ElementStatus _status;
    
    // List of Interfaces on this element
    InterfaceList _interface_list;
    
    // List of Connections with the network element
    Service *_inventory_subscription;
    
public:
    // Object life cycle
    Element (const std::string &name, uint64_t id, std::string mgmt_ip) : _name(name), _id(id), _mgmt_ip(mgmt_ip)
    {
        _status = ELementStatusInit;
    }
    
    ~Element ()
    {
    }
    
    // Accessors
    std::string getName()        { return _name;    }
    uint64_t    getId()          { return _id;      }
    std::string getMgmtIp()      { return _mgmt_ip; }
    std::string getTelemetryIp() { return _mgmt_ip + ":" + std::to_string(50051); }
    std::string getStatusStr()   { return ElementStatusStrings[_status]; }
    
    // Lookup
    static void              makeKey(std::string &key, const std::string &name, const std::string &mgmt_ip);
    static Element *         find(const std::string &name, const std::string &mgmt_ip);
    static status_t          add(const std::string &name, const std::string &mgmt_ip, Element *element);
    static void              remove(const std::string &name, const std::string &mgmt_ip);
    static ElementDbIterator findFirst(void);
    static ElementDbIterator findLast(void);
    static void              print();
    
    // Activate an element so that is available to E2
    status_t     activate();
    void         deactivate();
    static void  inventoryCallback(Element *elementp, ServiceCallbackKeyValue *kv);
    
    // Update Interface List
    void         updateInterface(ElementInterface *interface)
    {
        ElementInterface *ifp = NULL;
        
        // What do we have ?
        InterfaceListIterator itr = _interface_list.find(interface->getName());
        if (itr != _interface_list.end()) {
            ifp = itr->second;
        }
        
        _interface_list[interface->getName()] = interface;
        if (ifp) {
            delete ifp;
        }
    }

    // Pretty print contents
    void        description()
    {
        std::cout << "Element:\n";
        std::cout << "  Name  = " << _name << "\n";
        std::cout << "  ID    = " << _id   << "\n";
        std::cout << "  IP    = " << _mgmt_ip << "\n";
        std::cout << "  State = " << getStatusStr() << "\n";
        std::cout << "  Interfaces:\n";
        for (InterfaceListIterator itr = _interface_list.begin(); itr != _interface_list.end(); itr++) {
            std::cout << "     " << itr->first << "\n";
        }
    }
};



#endif /* Element_hpp */
