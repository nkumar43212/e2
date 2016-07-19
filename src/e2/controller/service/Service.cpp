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

Service *
Service::createSubscription (std::string subscription_path, Element *element)
{
    // Create the handle
    Service *servicep = new Service(subscription_path, element);
    if (!servicep) {
        return nullptr;
    }
    
    // Start the subscription
    servicep->subscriptionStart();
    
    return servicep;
}

Service::~Service()
{
    subscriptionStop();
}

void
Service::subscriptionStart ()
{
    // In a test environment, don't subscribe as there is no remote server
    if (isUnitTest()) {
        return;
    }
    
    // Create a client
    ServiceContext *context = new ServiceContext(&_interests, this);
    pthread_create(&_tid, NULL, Service::proc, (void *) context);
}

void
Service::subscriptionStop ()
{
    if (isUnitTest()) {
        return;
    }
    
    // Cancel the subscription
    ClientContext context_cancel;
    CancelSubscriptionRequest cancel_request;
    CancelSubscriptionReply cancel_reply;
    cancel_request.set_subscription_id(_subscription_id);
    stub_->cancelTelemetrySubscription(&context_cancel, cancel_request, &cancel_reply);
    pthread_cancel(_tid);
}

void *
Service::proc (void *p_args)
{
    ServiceContext       *contextp = (ServiceContext *) p_args;
    ServiceInterestList  *interests = contextp->_interests;
    Service *service = contextp->_service;
    
    // Create a reader
    SubscriptionRequest request;
    Path *path;
    path = request.add_path_list();
    path->set_path(service->getName());
    path->set_sample_frequency(5000);
    
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
            for (ServiceInterestListIterator itr = interests->begin(); itr != interests->end(); itr++) {
                Element *element = (*itr)->_element;
                (*itr)->_cb(element, &key_value);
            }
        }
    }

    // We are done.
    return NULL;
}