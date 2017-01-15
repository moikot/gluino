// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_QUEUE_RESOURCE_CLIENT_HPP
#define MESSAGING_QUEUE_RESOURCE_CLIENT_HPP

#include "QueueClient.hpp"

namespace Messaging {

template <typename T>
class QueueResourceClient {
  TYPE_PTRS(QueueResourceClient)
  typedef typename T::Unique TUnique;
  public:
    explicit QueueResourceClient(QueueClient::Shared queueClient);

    StatusResult::Unique getResource();
    StatusResult::Unique createResource(TUnique resource);
    StatusResult::Unique updateResource(TUnique resource);
    StatusResult::Unique deleteResource();

    void setOnGetStatusResponse(std::function<void(const StatusResult&)> onGetStatusResponse) {
      onGetStatusResponseHandler = onGetStatusResponse;
    }
    void setOnGetObjectResponse(std::function<void(const T&)> onGetObjectResponse) {
      onGetObjectResponseHandler = onGetObjectResponse;
    }
    void setOnCreateResponse(std::function<void(const Response&)> onCreateResponse) {
      onCreateResponseHandler = onCreateResponse;
    }
    void setOnUpdateResponse(std::function<void(const Response&)> onUpdateResponse) {
      onUpdateResponseHandler = onUpdateResponse;
    }
    void setOnDeleteResponse(std::function<void(const Response&)> onDeleteResponse) {
      onDeleteResponseHandler = onDeleteResponse;
    }

    void setOnCreateNotification(std::function<void(const T&)> onCreateNotification) {
      onCreateNotificationHandler = onCreateNotification;
    }
    void setOnUpdateNotification(std::function<void(const T&)> onUpdateNotification) {
      onUpdateNotificationHandler = onUpdateNotification;
    }
    void setOnDeleteNotification(std::function<void()> onDeleteNotification) {
      onDeleteNotificationHandler = onDeleteNotification;
    }

  private:
    QueueClient::Shared queueClient;
    std::string typeId;
    std::function<void(const StatusResult&)> onGetStatusResponseHandler;
    std::function<void(const T&)> onGetObjectResponseHandler;
    std::function<void(const Response&)> onCreateResponseHandler;
    std::function<void(const Response&)> onUpdateResponseHandler;
    std::function<void(const Response&)> onDeleteResponseHandler;
    std::function<void(const T&)> onCreateNotificationHandler;
    std::function<void(const T&)> onUpdateNotificationHandler;
    std::function<void()> onDeleteNotificationHandler;

    void onResponse(const Response& response);
    void onNotification(const Notification& notification);
};

template <typename T>
QueueResourceClient<T>::QueueResourceClient(QueueClient::Shared queueClient) :
  queueClient(queueClient), typeId(T::TypeId) {

  queueClient->setOnResponse(
    std::bind(&QueueResourceClient<T>::onResponse, this, std::placeholders::_1));
  queueClient->setOnNotification(
    std::bind(&QueueResourceClient<T>::onNotification, this, std::placeholders::_1));
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::getResource() {
  return queueClient->sendRequest(Action::Get, typeId, nullptr);
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::createResource(TUnique resource) {
  return queueClient->sendRequest(Action::Create, typeId, resource);
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::updateResource(TUnique resource) {
  return queueClient->sendRequest(Action::Update, typeId, resource);
}

template <typename T>
StatusResult::Unique
QueueResourceClient<T>::deleteResource() {
  return queueClient->sendRequest(Action::Delete, typeId, nullptr);
}

template <typename T>
void
QueueResourceClient<T>::onResponse(const Response& response) {
  auto Action = response.getAction();
  if (Action == Action::Get) {
    auto status = StatusResult::cast(&response.getResult());
    if (status && onGetStatusResponseHandler) {
      onGetStatusResponseHandler(*status);
    }
    else {
      auto objectResult = ObjectResult::cast(&response.getResult());
      if (objectResult) {
        auto object = T::cast(&objectResult->getObject());
        if (object) {
          onGetObjectResponseHandler(*object);
        }
        else {
          Logger::error("Unexpected type of object '" + std::string(objectResult->getObject().getTypeId()) + "'.");
        }
      }
      else {
        Logger::error("Unknown type of result '" + std::string(response.getResult().getTypeId()) + "'.");
      }
    }
  }
  else if (Action == Action::Create) {
    if (onCreateResponseHandler)
      onCreateResponseHandler(response);
  }
  else if (Action == Action::Update) {
    if (onUpdateResponseHandler)
      onUpdateResponseHandler(response);
  }
  else if (Action == Action::Delete) {
    if (onDeleteResponseHandler)
      onDeleteResponseHandler(response);
  }
}

template <typename T>
void
QueueResourceClient<T>::onNotification(const Notification& notification) {
  if (notification.getAction() == Action::Create) {
    if (onCreateNotificationHandler) {
      auto object = T::cast(notification.getContent());
      if (object)
        onCreateNotificationHandler(*object);
      else
        Logger::error("Expeceted content of '" + std::string(T::TypeId) + "' type.");
    }
  }
  else if (notification.getAction() == Action::Update) {
    if (onUpdateNotificationHandler) {
      auto object = T::cast(notification.getContent());
      if (object)
        onUpdateNotificationHandler(*object);
      else
        Logger::error("Expeceted content of '" + std::string(T::TypeId) + "' type.");
    }
  }
  else if (notification.getAction() == Action::Delete) {
    if (onDeleteNotificationHandler)
      onDeleteNotificationHandler();
  }
}

}

#endif /* end of include guard: MESSAGING_QUEUE_RESOURCE_CLIENT_HPP */
