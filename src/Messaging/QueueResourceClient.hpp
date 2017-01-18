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
#include "Core/StatusResult.hpp"

#include <vector>

namespace Messaging {

class IMessageQueue;

class QueueResourceClient : public QueueClient {
  TYPE_PTRS(QueueResourceClient)
  public:
    QueueResourceClient(std::string clientId, std::string resource, IMessageQueue& messageQueue);

    std::string getClientId() const override { return clientId; }
    void onResponse(const Response& response) const override;
    void onEvent(const Event& event) const override;

    Core::StatusResult::Unique sendRequest(std::string requestType);
    Core::StatusResult::Unique sendRequest(std::string requestType, Core::IEntity::Shared content);

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
    const std::string clientId;
    const std::string resource;
    IMessageQueue& messageQueue;
    std::vector<ResourceResponseHandler::Unique> responseHandlers;
    std::vector<ResourceEventHandler::Unique> eventHandlers;
};

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CLIENT_HPP */
