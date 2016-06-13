//
//  Service.cpp
//  e2
//
//  Created by NITIN KUMAR on 6/9/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#include "Service.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <grpc++/grpc++.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/io/zero_copy_stream.h>
#include "Logger.hpp"
#include "Element.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;


void *proc(void *args);

Service *
subscribe (std::string path_name, ServiceCallback cb, Element *elementp)
{
    Service *servicep = new Service(path_name, NULL, elementp);
    if (!servicep) {
        return nullptr;
    }

    return servicep;
}

Service::~Service()
{
    subscriptionStop();
}

void
Service::subscriptionStart (std::string name, ServiceCallback cb, Element *element)
{
    // Create a client
    ServiceContext *context = new ServiceContext(cb, element, this);
    
    pthread_create(_tid, NULL, proc, (void *) context);
}

void
Service::subscriptionStop ()
{
    // Cancel the subscription
    ClientContext context_cancel;
    CancelSubscriptionRequest cancel_request;
    CancelSubscriptionReply cancel_reply;
    cancel_request.set_subscription_id(_subscription_id);
    stub_->cancelTelemetrySubscription(&context_cancel, cancel_request, &cancel_reply);
    pthread_cancel(*_tid);
}

void *
proc (void *args)
{
    ServiceContext *contextp = (ServiceContext *) args;
    Element *element = contextp->_element;
    Service *service = contextp->_service;
    
    // Create a reader
    SubscriptionRequest request;
    ClientContext context;
    std::multimap<grpc::string_ref, grpc::string_ref> server_metadata;
    std::multimap<grpc::string_ref, grpc::string_ref>::iterator metadata_itr;
    std::unique_ptr<ClientReader<OpenConfigData>> reader(service->stub_->telemetrySubscribe(&context, request));
    
    // Get the subscription ID from the response
    // Wait for the initial meta data to come back
    reader->WaitForInitialMetadata();
    server_metadata = context.GetServerInitialMetadata();
    metadata_itr = server_metadata.find("init-response");
    std::string tmp = metadata_itr->second.data();
    
    // Use Textformat Printer APIs to convert to right format
    google::protobuf::TextFormat::Parser parser;
    SubscriptionReply reply;
    SubscriptionResponse *response;
    parser.ParseFromString(tmp, &reply);
    response = reply.mutable_response();
    service->setSubscriptionId(response->subscription_id());
    
    // Create the read channel
    OpenConfigData kv;
    while (reader->Read(&kv)) {
        for (int i = 0; i < kv.kv_size(); i++) {
            const KeyValue &kv_data = kv.kv(i);
            ServiceCallbackKeyValue key_value(kv_data.key(), kv_data.str_value());
            contextp->_cb(element, &key_value);
        }
    }
    
    // We are done.
    return NULL;
}

