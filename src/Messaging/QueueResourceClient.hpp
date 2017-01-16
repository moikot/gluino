// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CLIENT_HPP
#define MESSAGING_QUEUE_RESOURCE_CLIENT_HPP

#include "QueueClient.hpp"

namespace Messaging {

class QueueResourceClient {
  TYPE_PTRS(QueueResourceClient)
  public:
    QueueResourceClient(std::string resource, QueueClient& queueClient);

    Core::StatusResult::Unique sendRequest(std::string requestType);
    Core::StatusResult::Unique sendRequest(std::string requestType, Core::IEntity::Unique content);

    void addOnResponse(std::string requestType, std::function<void()> onResponse);

    template<class T>
    void addOnResponse(std::string requestType, std::function<void(const T&)> onResponse);

    void addOnEvent(std::string eventType, std::function<void()> onEvent);

    template<class T>
    void addOnEvent(std::string eventType, std::function<void(const T&)> onEvent);

  private:
    const std::string resource;
    QueueClient& queueClient;

    class IResourceResponseHandler {
      TYPE_PTRS_ABSTRACT(IResourceResponseHandler)
      virtual std::string getRequestType() = 0;
      virtual std::string getContentType() = 0;
      virtual void processResponse(const Response& response) = 0;
    };

    class ResourceResponseHandlerVoid : public IResourceResponseHandler {
      TYPE_PTRS(ResourceResponseHandlerVoid)
      public:
        ResourceResponseHandlerVoid(
          std::string requestType,
          std::function<void()> onResponse) :
          requestType(requestType),
          onResponse(onResponse) {
        }

        virtual std::string getRequestType() override {
          return requestType;
        }

        virtual std::string getContentType() override {
          return "";
        }

        virtual void processResponse(const Response& response) override {
          onResponse();
        }

      private:
        std::string requestType;
        std::function<void()> onResponse;
    };

    template<class T>
    class ResourceResponseHandler : public IResourceResponseHandler {
      TYPE_PTRS(ResourceResponseHandler)
      public:
        ResourceResponseHandler(
          std::string requestType,
          std::function<void(const T&)> onResponse) :
          requestType(requestType),
          onResponse(onResponse) {
        }

        virtual std::string getRequestType() override {
          return requestType;
        }

        virtual std::string getContentType() override {
          return T::getType();
        }

        virtual void processResponse(const Response& response) override {
          onResponse(response.getContent());
        }

      private:
        std::string requestType;
        std::function<void(const T&)> onResponse;
    };

    class IResourceEventHandler {
      TYPE_PTRS_ABSTRACT(IResourceEventHandler)
      virtual std::string getEventType() = 0;
      virtual std::string getContentType() = 0;
      virtual void onEvent(const Event& response) = 0;
    };

    void onResponse(const Response& response);
    void onEvent(const Event& response);
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CLIENT_HPP */
