//
//  E2ServerProtos.h
//  e2
//
//  Created by NITIN KUMAR on 6/7/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef E2ServerProtos_h
#define E2ServerProtos_h

#include "e2_api.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerWriter;
using grpc::Status;

using E2::E2;
using E2::NetworkElement;
using E2::NetworkElementType;
using E2::NetworkElementList;
using E2::NetworkElementOpState;
using E2::NetworkElementOpStateList;
using E2::NetworkElementProperty;

using E2::ConfigurationReply;
using E2::ServicePlacementRequest;
using E2::ServiceEndpoint;
using E2::ServiceEndpointList;

using E2::FabricLinkList;



#endif /* E2ServerProtos_h */
