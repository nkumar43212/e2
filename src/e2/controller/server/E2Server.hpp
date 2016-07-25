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
    
    // Internal helper routine
    void deactivateService(const ServicePlacementRequest * request);
    
public:
    E2Server(Logger *logger) : _logger(logger)
    {
    }

    // The Interface
    Status addElement(ServerContext* context,
                      const ConfigurationRequest * request,
                      ConfigurationReply * reply) override;
    Status removeElement(ServerContext* context,
                         const ConfigurationRequest * request,
                         ConfigurationReply * reply) override;
    Status getElements(ServerContext* context,
                       const ConfigurationRequest * request,
                       NetworkElementOpStateList * reply) override;
    Status addFabricLink(ServerContext* context,
                         const ConfigurationRequest * request,
                         ConfigurationReply * reply) override;
    Status addServiceEndpoint(ServerContext* context,
                              const ServiceConfigurationRequest * request,
                              ConfigurationReply * reply) override;
    Status removeServiceEndpoint(ServerContext* context,
                                 const ServiceConfigurationRequest * request,
                                 ConfigurationReply * reply) override;
    Status activateService(ServerContext* context,
                           const ServicePlacementRequest * request,
                           ConfigurationReply * reply) override;
    Status deactivateService(ServerContext* context,
                             const ServicePlacementRequest * request,
                             ConfigurationReply * reply) override;
    
    // Trace/Debug Interface
    void        enableLog();
    void        disableLog();
    void        traceLog(const std::string msg);
};

#endif /* E2Server_hpp */
