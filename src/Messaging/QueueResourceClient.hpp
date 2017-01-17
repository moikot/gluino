// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CLIENT_HPP
#define MESSAGING_QUEUE_RESOURCE_CLIENT_HPP

#include "QueueClient.hpp"
#include "ResourceResponseHandler.hpp"
#include "ResourceEventHandler.hpp"

#include <vector>

namespace Messaging {

class QueueResourceClient {
  TYPE_PTRS(QueueResourceClient)
  public:
    QueueResourceClient(std::string resource, QueueClient& queueClient);

    Core::StatusResult::Unique sendRequest(std::string requestType);
    Core::StatusResult::Unique sendRequest(std::string requestType, Core::IEntity::Unique content);

    void addOnResponse(std::string requestType, std::function<void()> onResponse) {
      responseHandlers.push_back(ResourceResponseHandlerVoid::makeUnique(requestType, onResponse));
    }

    template<class T>
    void addOnResponse(std::string requestType, std::function<void(const T&)> onResponse) {
      responseHandlers.push_back(ResourceResponseHandlerTyped<T>::makeUnique(requestType, onResponse));
    }

    void addOnEvent(std::string eventType, std::function<void()> onEvent) {
      eventHandlers.push_back(ResourceEventHandlerVoid::makeUnique(eventType, onEvent));
    }

    template<class T>
    void addOnEvent(std::string eventType, std::function<void(const T&)> onEvent) {
      eventHandlers.push_back(ResourceEventHandlerTyped<T>::makeUnique(eventType, onEvent));
    }

  private:
    const std::string resource;
    QueueClient& queueClient;
    std::vector<ResourceResponseHandler::Unique> responseHandlers;
    std::vector<ResourceEventHandler::Unique> eventHandlers;

    void onResponse(const Response& response);
    void onEvent(const Event& response);
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CLIENT_HPP */
