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
#include "Metrics.hpp"
#include "MetricsManager.hpp"
#include "IndexManager.h"
#include "ServiceOrder.hpp"

// Types
class Element;
class Service;
class ServiceCallbackKeyValue;
typedef std::map<std::string, Element *>::iterator ElementDbIterator;
typedef std::map<std::string, ElementInterface *> InterfaceList;
typedef std::map<std::string, ElementInterface *>::iterator InterfaceListIterator;

// Status
typedef enum {
    ElementStatusInit        = 0,
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
    time_t      _last_update_time;
    bool        _is_unit_test;
    
    // Where is the element in its lifecycle
    ElementStatus _status;
    
    // List of Interfaces on this element
    IdManager     _interface_id_manager;
    u_int32_t     _interface_count;
    InterfaceList _interface_list;
    
    // List of Connections with the network element
    std::map<std::string, Service *> _subscriptions;
    
    // Metrics to measure this element.
    MetricsManager   _metrics_list;
    
public:
    // Object life cycle
    Element (const std::string &name, uint64_t id, std::string mgmt_ip) : _name(name), _id(id), _mgmt_ip(mgmt_ip)
    {
        _status = ElementStatusInit;
        _is_unit_test = (mgmt_ip == "0.0.0.0") ? true : false;
        _interface_count = 0;
    }
    
    ~Element ()
    {
    }
    
    // Accessors
    std::string getName()                     { return _name;    }
    uint64_t    getId()                       { return _id;      }
    std::string getMgmtIp()                   { return _mgmt_ip; }
    std::string getTelemetryIp()              { return _mgmt_ip + ":" + std::to_string(50051); }
    ElementStatus getStatus()                 { return _status;                                }
    std::string getStatusStr()                { return ElementStatusStrings[_status];          }
    time_t      getLastUpdateTime()           { return _last_update_time;                      }
    void        setLastUpdateTime(time_t val) { _last_update_time = val;                       }
    bool        isUnitTest()                  { return _is_unit_test;                          }
    
    // Lookup
    static void              makeKey(std::string &key, const std::string &name, const std::string &mgmt_ip);
    static Element *         find(const std::string &name, const std::string &mgmt_ip);
    static Element *         find(const std::string &name);
    static status_t          add(const std::string &name, const std::string &mgmt_ip, Element *element);
    static void              remove(const std::string &name, const std::string &mgmt_ip);
    static ElementDbIterator findFirst(void);
    static ElementDbIterator findLast(void);
    static void              print();
    
    // Get a list of operational state values for this element
    void         getOperationalState(ElementOpstateList &list);
    
    // Activate an element so that is available to E2
    status_t     activate();
    void         deactivate();
    bool         isActive();
    static void  inventoryCallback(Element *elementp, ServiceCallbackKeyValue *kv);
    static void  interfacesCallback(Element *elementp, ServiceCallbackKeyValue *kv);
    
    // Interface List Management
    id_idx_t     allocateInterfaceIndex();
    bool         isPresentInterface(std::string name);
    void         addInterface(ElementInterface *interface);
    void         removeInterface(std::string name);
    u_int32_t    getInterfaceCount();
    
    // Manage Metrics
    static void  utilizationCallback(Element *elementp, ServiceCallbackKeyValue *kv);
    void         addMetric(Metrics &metrics);
    void         removeMetric(Metrics &metrics);
    void         updateMetric(const std::string name, uint64_t value);
    
    // Add services on the element
    status_t     addServiceOrder(ServiceOrder *order);
    status_t     removeServiceOrder(ServiceOrder *order);
    static void  serviceOrderCallback(Element *elementp, ServiceCallbackKeyValue *kv);
    
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
            itr->second->description();
        }
    }
};



#endif /* Element_hpp */
