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

class ServiceCallbackKeyValue {
public:
    std::string key;
    std::string str_value;
    ServiceCallbackKeyValue(std::string k, std::string v) : key(k), str_value(v)
    {
    }
};

typedef void (*ServiceCallback)(Element *, ServiceCallbackKeyValue *);

class Service {
    std::string     _name;
    ServiceCallback _cb;
    Element *       _arg;
    pthread_t       *_tid;
    uint32_t         _subscription_id;
    
public:
    // Accessors
    uint32_t     getSubscriptionId()            { return _subscription_id; }
    void         setSubscriptionId(uint32_t id) { _subscription_id = id;   }
    std::string  getName()                      { return _name;            }
    
    std::unique_ptr<OpenConfigTelemetry::Stub> stub_;
    static Service * subscribe(std::string name, ServiceCallback cb, Element *element);
    Service (std::string path_name, ServiceCallback cb, Element *element) :
        _name(path_name), _cb(cb), _arg(element),
        stub_(OpenConfigTelemetry::NewStub(grpc::CreateChannel(element->getTelemetryIp(),
                                                               grpc::InsecureCredentials())))
    {
        subscriptionStart(path_name, cb, element);
    }
    ~Service();
    void subscriptionStart(std::string name, ServiceCallback cb, Element *element);
    void subscriptionStop();
};

class ServiceContext {
    
public:
    ServiceCallback _cb;
    Service *_service;
    Element *_element;
    
    ServiceContext(ServiceCallback cb, Element *element, Service *service) : _cb(cb), _service(service), _element(element)
    {
    }
};
#endif /* Service_hpp */
