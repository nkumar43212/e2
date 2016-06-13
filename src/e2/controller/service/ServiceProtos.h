//
//  ServiceProtos.h
//  e2
//
//  Created by NITIN KUMAR on 6/10/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef ServiceProtos_h
#define ServiceProtos_h

#include <iostream>
#include <string>
#include <grpc++/grpc++.h>
#include "agent.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::Status;

using Telemetry::OpenConfigTelemetry;

using Telemetry::CancelSubscriptionReply;
using Telemetry::CancelSubscriptionRequest;
using Telemetry::Collector;
using Telemetry::DataEncodingReply;
using Telemetry::DataEncodingRequest;
using Telemetry::GetOperationalStateReply;
using Telemetry::GetOperationalStateRequest;
using Telemetry::GetSubscriptionsReply;
using Telemetry::GetSubscriptionsRequest;
using Telemetry::KeyValue;
using Telemetry::OpenConfigData;
using Telemetry::Path;
using Telemetry::SubscriptionAdditionalConfig;
using Telemetry::SubscriptionInput;
using Telemetry::SubscriptionReply;
using Telemetry::SubscriptionRequest;
using Telemetry::SubscriptionResponse;
using Telemetry::ReturnCode;
using Telemetry::VerbosityLevel;
using Telemetry::EncodingType;



#endif /* ServiceProtos_h */
