// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_QUEUE_RESOURCE_CLIENT_HPP
#define CORE_QUEUE_RESOURCE_CLIENT_HPP

#include "QueueClient.hpp"

namespace Core {

template <typename T>
class QueueResourceClient {
  TYPE_PTRS(QueueResourceClient)
  typedef typename T::Unique TUnique;
  public:
    QueueResourceClient(QueueClient::Shared queueClient);

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

}

#include "QueueResourceClient.ipp"
#endif /* end of include guard: CORE_QUEUE_RESOURCE_CLIENT_HPP */
