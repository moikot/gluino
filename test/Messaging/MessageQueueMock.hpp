#ifndef MESSAGE_QUEUE_MOCK_HPP
#define MESSAGE_QUEUE_MOCK_HPP

#include <gmock/gmock.h>

#include "Messaging/IMessageQueue.hpp"

class MessageQueueMock : public Messaging::IMessageQueue {
 public:
  MOCK_METHOD0(idle, void());
  MOCK_METHOD1(sendMessage, Core::StatusResult::Unique(Messaging::Message::Shared));
  MOCK_METHOD1(createClient, Messaging::QueueClient::Shared(std::string));
  MOCK_METHOD1(removeClient, void(Messaging::QueueClient::Shared));
  MOCK_METHOD1(createController, Messaging::QueueController::Shared(std::string));
  MOCK_METHOD1(removeController, void(Messaging::QueueController::Shared));
};

#endif /* end of include guard: MESSAGE_QUEUE_MOCK_HPP */
