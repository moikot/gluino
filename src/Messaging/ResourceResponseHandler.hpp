// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESOURCE_RESPONSE_HANDLER_HPP
#define MESSAGING_RESOURCE_RESPONSE_HANDLER_HPP

#include "Response.hpp"
#include "Core/Traits.hpp"

#include <functional>

namespace Messaging {

  struct ResourceResponseHandler {
    virtual ~ResourceResponseHandler() = default;
    virtual std::string getRequestType() const = 0;
    virtual std::string getContentType() const = 0;
    virtual void processResponse(const Response& response) const = 0;
  };

  template<class T>
  class ResourceResponseHandlerImpl : public ResourceResponseHandler {
    typedef typename Core::function_traits<T> traits;
    public:
      ResourceResponseHandlerImpl(
        std::string requestType,
        T onResponse) :
        requestType(requestType),
        onResponse(onResponse) {
      }

      virtual std::string getRequestType() const override {
        return requestType;
      }

      virtual std::string getContentType() const override {
        return Core::base_type<typename traits::template arg<0>::type>::TypeId();
      }

      virtual void processResponse(const Response& response) const override {
        onResponse(static_cast<typename traits::template arg<0>::type>(response.getContent()));
      }

    private:
      const std::string requestType;
      const T onResponse;
  };

}

#endif /* end of include guard: MESSAGING_RESOURCE_RESPONSE_HANDLER_HPP */
