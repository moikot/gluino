// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESOURCE_RESPONSE_HANDLER_HPP
#define MESSAGING_RESOURCE_RESPONSE_HANDLER_HPP

#include "Response.hpp"

#include <functional>

namespace Messaging {

  class ResourceResponseHandler {
    TYPE_PTRS_ABSTRACT(ResourceResponseHandler)
    virtual ~ResourceResponseHandler() = default;
    virtual std::string getRequestType() const = 0;
    virtual std::string getContentType() const = 0;
    virtual void processResponse(const Response& response) const = 0;
  };

  template<class T>
  class ResourceResponseHandlerTyped : public ResourceResponseHandler {
    TYPE_PTRS(ResourceResponseHandlerTyped)
    public:
      ResourceResponseHandlerTyped(
        std::string requestType,
        std::function<void(const T&)> onResponse) :
        requestType(requestType),
        onResponse(onResponse) {
      }

      virtual std::string getRequestType() const override {
        return requestType;
      }

      virtual std::string getContentType() const override {
        return T::TypeId();
      }

      virtual void processResponse(const Response& response) const override {
        onResponse(static_cast<const T&>(response.getContent()));
      }

    private:
      const std::string requestType;
      const std::function<void(const T&)> onResponse;
  };

}

#endif /* end of include guard: MESSAGING_RESOURCE_RESPONSE_HANDLER_HPP */
