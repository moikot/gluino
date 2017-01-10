#include <gtest/gtest.h>

#include "Messaging/Notification.hpp"

using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Notification::Unique createNotification(Core::IEntity::Shared content) {
    return Notification::makeUnique("sender", "receiver", ActionType::Get, "resource", content);
  }

}

TEST(Notification, Sender_Retained) {
  auto notification = createNotification(nullptr);
  ASSERT_EQ(notification->getSender(), "sender");
}

TEST(Notification, Receiver_Retained) {
  auto notification = createNotification(nullptr);
  ASSERT_EQ(notification->getReceiver(), "receiver");
}

TEST(Notification, ActionType_Retained) {
  auto notification = createNotification(nullptr);
  ASSERT_EQ(notification->getActionType(), ActionType::Get);
}

TEST(Notification, Resource_Retained) {
  auto notification = createNotification(nullptr);
  ASSERT_EQ(notification->getResource(), "resource");
}

TEST(Notification, Content_Retained) {
  auto content = Content::makeShared();
  auto notification = createNotification(content);
  ASSERT_EQ(notification->getContent(), content.get());
}
