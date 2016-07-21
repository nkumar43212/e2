// Generated by the gRPC protobuf plugin.
// If you make any local change, they will be lost.
// source: e2_api.proto
#ifndef GRPC_e2_5fapi_2eproto__INCLUDED
#define GRPC_e2_5fapi_2eproto__INCLUDED

#include "e2_api.pb.h"

#include <grpc++/support/async_stream.h>
#include <grpc++/impl/rpc_method.h>
#include <grpc++/impl/proto_utils.h>
#include <grpc++/impl/service_type.h>
#include <grpc++/support/async_unary_call.h>
#include <grpc++/support/status.h>
#include <grpc++/support/stub_options.h>
#include <grpc++/support/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class RpcService;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace E2 {

class E2 GRPC_FINAL {
 public:
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    virtual ::grpc::Status addElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncaddElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncaddElementRaw(context, request, cq));
    }
    virtual ::grpc::Status removeElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncremoveElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncremoveElementRaw(context, request, cq));
    }
    virtual ::grpc::Status getElements(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::NetworkElementOpStateList* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::NetworkElementOpStateList>> AsyncgetElements(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::NetworkElementOpStateList>>(AsyncgetElementsRaw(context, request, cq));
    }
    virtual ::grpc::Status addFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncaddFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncaddFabricLinkRaw(context, request, cq));
    }
    virtual ::grpc::Status removeFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncremoveFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncremoveFabricLinkRaw(context, request, cq));
    }
    virtual ::grpc::Status addServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncaddServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncaddServiceEndpointRaw(context, request, cq));
    }
    virtual ::grpc::Status removeServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncremoveServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncremoveServiceEndpointRaw(context, request, cq));
    }
    virtual ::grpc::Status activateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncactivateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncactivateServiceRaw(context, request, cq));
    }
    virtual ::grpc::Status deactivateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::E2::ConfigurationReply* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>> AsyncdeactivateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>>(AsyncdeactivateServiceRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncaddElementRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncremoveElementRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::NetworkElementOpStateList>* AsyncgetElementsRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncaddFabricLinkRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncremoveFabricLinkRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncaddServiceEndpointRaw(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncremoveServiceEndpointRaw(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncactivateServiceRaw(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::E2::ConfigurationReply>* AsyncdeactivateServiceRaw(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub GRPC_FINAL : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::Channel>& channel);
    ::grpc::Status addElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncaddElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncaddElementRaw(context, request, cq));
    }
    ::grpc::Status removeElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncremoveElement(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncremoveElementRaw(context, request, cq));
    }
    ::grpc::Status getElements(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::NetworkElementOpStateList* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::NetworkElementOpStateList>> AsyncgetElements(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::NetworkElementOpStateList>>(AsyncgetElementsRaw(context, request, cq));
    }
    ::grpc::Status addFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncaddFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncaddFabricLinkRaw(context, request, cq));
    }
    ::grpc::Status removeFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncremoveFabricLink(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncremoveFabricLinkRaw(context, request, cq));
    }
    ::grpc::Status addServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncaddServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncaddServiceEndpointRaw(context, request, cq));
    }
    ::grpc::Status removeServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncremoveServiceEndpoint(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncremoveServiceEndpointRaw(context, request, cq));
    }
    ::grpc::Status activateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncactivateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncactivateServiceRaw(context, request, cq));
    }
    ::grpc::Status deactivateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::E2::ConfigurationReply* response) GRPC_OVERRIDE;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>> AsyncdeactivateService(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>>(AsyncdeactivateServiceRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::Channel> channel_;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncaddElementRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncremoveElementRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::NetworkElementOpStateList>* AsyncgetElementsRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncaddFabricLinkRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncremoveFabricLinkRaw(::grpc::ClientContext* context, const ::E2::ConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncaddServiceEndpointRaw(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncremoveServiceEndpointRaw(::grpc::ClientContext* context, const ::E2::ServiceConfigurationRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncactivateServiceRaw(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    ::grpc::ClientAsyncResponseReader< ::E2::ConfigurationReply>* AsyncdeactivateServiceRaw(::grpc::ClientContext* context, const ::E2::ServicePlacementRequest& request, ::grpc::CompletionQueue* cq) GRPC_OVERRIDE;
    const ::grpc::RpcMethod rpcmethod_addElement_;
    const ::grpc::RpcMethod rpcmethod_removeElement_;
    const ::grpc::RpcMethod rpcmethod_getElements_;
    const ::grpc::RpcMethod rpcmethod_addFabricLink_;
    const ::grpc::RpcMethod rpcmethod_removeFabricLink_;
    const ::grpc::RpcMethod rpcmethod_addServiceEndpoint_;
    const ::grpc::RpcMethod rpcmethod_removeServiceEndpoint_;
    const ::grpc::RpcMethod rpcmethod_activateService_;
    const ::grpc::RpcMethod rpcmethod_deactivateService_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::Channel>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::SynchronousService {
   public:
    Service() : service_(nullptr) {}
    virtual ~Service();
    virtual ::grpc::Status addElement(::grpc::ServerContext* context, const ::E2::ConfigurationRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status removeElement(::grpc::ServerContext* context, const ::E2::ConfigurationRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status getElements(::grpc::ServerContext* context, const ::E2::ConfigurationRequest* request, ::E2::NetworkElementOpStateList* response);
    virtual ::grpc::Status addFabricLink(::grpc::ServerContext* context, const ::E2::ConfigurationRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status removeFabricLink(::grpc::ServerContext* context, const ::E2::ConfigurationRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status addServiceEndpoint(::grpc::ServerContext* context, const ::E2::ServiceConfigurationRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status removeServiceEndpoint(::grpc::ServerContext* context, const ::E2::ServiceConfigurationRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status activateService(::grpc::ServerContext* context, const ::E2::ServicePlacementRequest* request, ::E2::ConfigurationReply* response);
    virtual ::grpc::Status deactivateService(::grpc::ServerContext* context, const ::E2::ServicePlacementRequest* request, ::E2::ConfigurationReply* response);
    ::grpc::RpcService* service() GRPC_OVERRIDE GRPC_FINAL;
   private:
    ::grpc::RpcService* service_;
  };
  class AsyncService GRPC_FINAL : public ::grpc::AsynchronousService {
   public:
    explicit AsyncService();
    ~AsyncService() {};
    void RequestaddElement(::grpc::ServerContext* context, ::E2::ConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestremoveElement(::grpc::ServerContext* context, ::E2::ConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestgetElements(::grpc::ServerContext* context, ::E2::ConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::NetworkElementOpStateList>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestaddFabricLink(::grpc::ServerContext* context, ::E2::ConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestremoveFabricLink(::grpc::ServerContext* context, ::E2::ConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestaddServiceEndpoint(::grpc::ServerContext* context, ::E2::ServiceConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestremoveServiceEndpoint(::grpc::ServerContext* context, ::E2::ServiceConfigurationRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestactivateService(::grpc::ServerContext* context, ::E2::ServicePlacementRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
    void RequestdeactivateService(::grpc::ServerContext* context, ::E2::ServicePlacementRequest* request, ::grpc::ServerAsyncResponseWriter< ::E2::ConfigurationReply>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag);
  };
};

}  // namespace E2


#endif  // GRPC_e2_5fapi_2eproto__INCLUDED
