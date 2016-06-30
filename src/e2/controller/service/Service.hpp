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

// When a service subscription is created, this is the set of arguments
// the caller needs to provide
class ServiceArgs {
public:
    typedef void (*ServiceCallback)(Element *, ServiceCallbackKeyValue *);
    ServiceCallback _cb;
    Element        *_element;
    ServiceArgs (ServiceCallback cb, Element *element) : _cb(cb), _element(element)
    {
    }
};

// Subscription service
class Service {
    std::string     _name;
    ServiceArgs *   _args;
    pthread_t       _tid;
    uint32_t        _subscription_id;
    
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
    
    // Create a service subscription
    static Service *createSubscription(std::string subscription_path, ServiceArgs *args);
    ~Service();
    
    Service (std::string path_name, ServiceArgs *args) : _name(path_name), _args(args)
    {
        if (args->_element->getTelemetryIp() != "0.0.0.0") {
            stub_ = OpenConfigTelemetry::NewStub(grpc::CreateChannel(args->_element->getTelemetryIp(), grpc::InsecureCredentials()));
        }
    }
    
    // Visibility
    void description ()
    {
    }
};

class ServiceContext {
public:
    ServiceArgs * _args;
    Service *    _service;
    
    ServiceContext(ServiceArgs * args, Service *service) : _args(args), _service(service)
    {
    }
};

#endif /* Service_hpp */
