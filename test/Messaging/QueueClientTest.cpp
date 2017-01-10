#include <gtest/gtest.h>

#include "Messaging/QueueClient.hpp"
#include "MessageQueueMock.hpp"

using namespace Messaging;

TEST(QueueClient, Identifier_Retained) {
  MessageQueueMock messageQueue;
  auto client = QueueClient::makeUnique("id", messageQueue);
  ASSERT_EQ(client->getId(), "id");
}
