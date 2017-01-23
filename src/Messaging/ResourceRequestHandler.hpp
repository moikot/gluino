// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESOURCE_REQUEST_HANDLER_HPP
#define MESSAGING_RESOURCE_REQUEST_HANDLER_HPP

#include "Request.hpp"

#include <functional>

namespace Messaging {

  struct ResourceRequestHandler {
    TYPE_PTRS_ABSTRACT(ResourceRequestHandler)
    virtual ~ResourceRequestHandler() = default;
    virtual std::string getRequestType() const = 0;
    virtual std::string getContentType() const = 0;
    virtual Core::IEntity::Unique makeRequest(const Request& request) const = 0;
  };

  class ResourceRequestHandlerVoid : public ResourceRequestHandler {
    TYPE_PTRS(ResourceRequestHandlerVoid)
    public:
      ResourceRequestHandlerVoid(
        std::string requestType,
        std::function<Core::IEntity::Unique()> onRequest) :
        requestType(requestType),
        onRequest(onRequest) {
      }

      virtual std::string getRequestType() const override {
        return requestType;
      }

      virtual std::string getContentType() const override {
        return "";
      }

      virtual Core::IEntity::Unique makeRequest(const Request&) const override {
          return onRequest();
      }

    private:
      const std::string requestType;
      const std::function<Core::IEntity::Unique()> onRequest;
  };

  template<class T>
  class ResourceRequestHandlerTyped : public ResourceRequestHandler {
    TYPE_PTRS(ResourceRequestHandlerTyped)
    public:
      ResourceRequestHandlerTyped(
        std::string requestType,
        std::function<Core::IEntity::Unique(const T&)> onRequest) :
        requestType(requestType),
        onRequest(onRequest) {
      }

      virtual std::string getRequestType() const override {
        return requestType;
      }

      virtual std::string getContentType() const override {
        return T::TypeId();
      }

      virtual Core::IEntity::Unique makeRequest(const Request& request) const override {
        return onRequest(static_cast<const T&>(*request.getContent()));
      }

    private:
      const std::string requestType;
      const std::function<Core::IEntity::Unique(const T&)> onRequest;
  };

}


#endif /* end of include guard: MESSAGING_RESOURCE_REQUEST_HANDLER_HPP */
