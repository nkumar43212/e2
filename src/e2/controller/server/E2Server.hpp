//
//  E2Server.hpp
//  e2
//
//  Created by NITIN KUMAR on 6/6/16.
//  Copyright © 2016 Juniper Networks. All rights reserved.
//

#ifndef E2Server_hpp
#define E2Server_hpp

#include <stdio.h>
#include <mutex>
#include <grpc++/grpc++.h>
#include "E2ServerProtos.h"
#include "Logger.hpp"


class E2Server final : public E2::E2::Service {
    Logger *_logger;
    
    void     deactivateService(const ServiceBinding * request);

    // Trace/Debug Interface
    void        enableLog();
    void        disableLog();
    void        traceLog(const std::string msg);
    void        traceLogRPC(const std::string rpc_name);

public:
    E2Server(Logger *logger) : _logger(logger)
    {
    }
    
    Logger *getLogger()      { return _logger; }

    // The Interface
    Status addElement(ServerContext* context,
                      const NetworkElementList * request,
                      ConfigurationReply * reply) override;
    Status removeElement(ServerContext* context,
                         const NetworkElementList * request,
                         ConfigurationReply * reply) override;
    Status getElements(ServerContext* context,
                       const NetworkElement * request,
                       NetworkElementOpStateList * reply) override;
    Status addFabricAdjacency(ServerContext* context,
                         const FabricAdjacencyList * request,
                         ConfigurationReply * reply) override;
    Status addServiceEndpoint(ServerContext* context,
                              const ServiceEndpointList * request,
                              ConfigurationReply * reply) override;
    Status removeServiceEndpoint(ServerContext* context,
                                 const ServiceEndpointList * request,
                                 ConfigurationReply * reply) override;
    Status activateService(ServerContext* context,
                           const ServiceBinding * request,
                           ConfigurationReply * reply) override;
    Status deactivateService(ServerContext* context,
                             const ServiceBinding * request,
                             ConfigurationReply * reply) override;
};

#endif /* E2Server_hpp */
