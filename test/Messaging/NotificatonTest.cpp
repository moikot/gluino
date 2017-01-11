#include "catch.hpp"

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

TEST_CASE("Notification can be constructed", "[Notification]") {

  auto notification = createNotification(nullptr);

  SECTION("sender retained") {
    REQUIRE(notification->getSender()  == "sender");
  }

  SECTION("receiver retained") {
    REQUIRE(notification->getReceiver() == "receiver");
  }

  SECTION("action type retained") {
    REQUIRE(notification->getActionType() == ActionType::Get);
  }

  SECTION("resource retained") {
    REQUIRE(notification->getResource() == "resource");
  }

  SECTION("content retained") {
    auto content = Content::makeShared();
    auto notification = createNotification(content);
    REQUIRE(notification->getContent() == content.get());
  }

}