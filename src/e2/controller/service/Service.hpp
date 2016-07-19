//
//  Service.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/9/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef Service_hpp
#define Service_hpp

#include <unistd.h>
#include <iostream>
#include <stdio.h>
#include <string>
#include "ServiceProtos.h"
#include "Element.hpp"

// Forwards
class ServiceInterest;
typedef std::vector<ServiceInterest *>ServiceInterestList;
typedef ServiceInterestList::iterator ServiceInterestListIterator;

// Subscription service
class Service {
    std::string          _name;
    ServiceInterestList  _interests;
    pthread_t            _tid;
    uint32_t             _subscription_id;
    bool                 _is_unit_test;
    
    // Helper routines
    void subscriptionStart();
    void subscriptionStop();
    bool validateSubscriptionPath();
    
    // Worker routine for the background thread that polls the subscription channel
    static void * proc(void *);
    
public:
    // The RPC stub invoked to communicate with device
    std::unique_ptr<OpenConfigTelemetry::Stub> stub_;
    
    // Accessors
    uint32_t     getSubscriptionId()            { return _subscription_id; }
    void         setSubscriptionId(uint32_t id) { _subscription_id = id;   }
    std::string  getName()                      { return _name;            }
    bool         isUnitTest()                   { return _is_unit_test;    }
    
    // Create a service subscription
    static Service *createSubscription(std::string subscription_path, Element *element);
   
    // Manage interests. An interest is chance to get a callback when a record on this
    // service channel is received
    void            addInterest(ServiceInterest *interest)
    {
        _interests.push_back(interest);
    }
    bool            searchInterest(ServiceInterest *interest)
    {
        for (ServiceInterestListIterator itr = _interests.begin(); itr != _interests.end(); itr++) {
            if ((*itr) == interest) {
                return true;
            }
        }
        return false;
    }
    
    ~Service();
    
    Service (std::string path_name, Element *element) : _name(path_name)
    {
        _is_unit_test = element->isUnitTest();
        if (!_is_unit_test) {
            stub_ = OpenConfigTelemetry::NewStub(grpc::CreateChannel(element->getTelemetryIp(), grpc::InsecureCredentials()));
        }
    }
    
    // Visibility
    void description ()
    {
    }
};

// When a subscription is created, the service calls back the client when a value
// is available.
class ServiceCallbackKeyValue {
public:
    std::string key;
    std::string str_value;
    ServiceCallbackKeyValue(std::string k, std::string v)
    {
        key = k;
        str_value = v;
    }
};

// After a service is created, interests can be created on the service.
// An interest registers a callback routine which is invoked when any data
// element is available on the service channel
class ServiceInterest {
public:
    typedef void (*ServiceCallback)(Element *, ServiceCallbackKeyValue *);
    ServiceCallback _cb;
    Element        *_element;
    std::string     _name;
    ServiceInterest(ServiceCallback cb, Element *element, std::string name = "") : _cb(cb), _element(element), _name(name)
    {
    }
};


// Wrapper class used to pass arguments to the subscription thread
class ServiceContext {
public:
    ServiceInterestList * _interests;
    Service *             _service;
    
    ServiceContext(ServiceInterestList *interests, Service *service) : _interests(interests), _service(service)
    {
    }
};

#endif /* Service_hpp */
