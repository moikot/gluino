// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP
#define MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP

#include "QueueController.hpp"
#include <vector>

namespace Messaging {

class IMessageQueue;

class QueueResourceController {
  TYPE_PTRS(QueueResourceController)
  public:
    QueueResourceController(std::string resource, QueueController& queueController);

    Core::StatusResult::Unique sendEvent(std::string eventType);
    Core::StatusResult::Unique sendEvent(std::string eventType, Core::IEntity::Unique content);

    void addOnRequest(std::string requestType, std::function<Core::IEntity::Unique()> onRequest) {
      handlers.push_back(ResourceRequestHandlerVoid::makeUnique(requestType, onRequest));
    }

    template<class T>
    void addOnRequest(std::string requestType, std::function<Core::IEntity::Unique(const T&)> onRequest) {
      handlers.push_back(ResourceRequestHandler<T>::makeUnique(requestType, onRequest));
    }

  private:
    const std::string resource;
    QueueController& queueController;

    class IResourceRequestHandler {
      TYPE_PTRS_ABSTRACT(IResourceRequestHandler)
      virtual std::string getRequestType() = 0;
      virtual std::string getContentType() = 0;
      virtual Core::IEntity::Unique makeRequest(const Request& request) = 0;
    };

    std::vector<IResourceRequestHandler::Unique> handlers;

    class ResourceRequestHandlerVoid : public IResourceRequestHandler {
      TYPE_PTRS(ResourceRequestHandlerVoid)
      public:
        ResourceRequestHandlerVoid(
          std::string requestType,
          std::function<Core::IEntity::Unique()> onRequest) :
          requestType(requestType),
          onRequest(onRequest) {
        }

        virtual std::string getRequestType() override {
          return requestType;
        }

        virtual std::string getContentType() override {
          return "";
        }

        virtual Core::IEntity::Unique makeRequest(const Request& request) override {
            return onRequest();
        }

      private:
        std::string requestType;
        std::function<Core::IEntity::Unique()> onRequest;
    };

    template<class T>
    class ResourceRequestHandler : public IResourceRequestHandler {
      TYPE_PTRS(ResourceRequestHandler)
      public:
        ResourceRequestHandler(
          std::string requestType,
          std::function<Core::IEntity::Unique(const T&)> onRequest) :
          requestType(requestType),
          onRequest(onRequest) {
        }

        virtual std::string getRequestType() override {
          return requestType;
        }

        virtual std::string getContentType() override {
          return T::getType();
        }

        virtual Core::IEntity::Unique makeRequest(const Request& request) override {
          return onRequest(request.getContent());
        }

      private:
        std::string requestType;
        std::function<Core::IEntity::Unique(const T&)> onRequest;
    };

    RequestHandler getRequestHandler(const Request& request);
    RequestHandler getResourceRequestHandler(std::string requestType, std::string contentType);
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CONTROLLER_HPP */
