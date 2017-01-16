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

    template<class T>
    void addOnResponse(std::string requestType, std::function<void(const T&)> onResponse);

    void addOnEvent(std::string eventType, std::function<void()> onEvent);

    template<class T>
    void addOnEvent(std::string eventType, std::function<void(const T&)> onEvent);

  private:
    const std::string resource;
    QueueClient& queueClient;

    void onResponse(const Response& response);
    void onEvent(const Event& response);
};

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CLIENT_HPP */
