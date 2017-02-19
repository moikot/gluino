#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Messaging/Event.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("Event can be constructed", "[Event]") {
  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();

  auto eventNoContent = std::make_unique<Event>("created", "resource");
  auto eventWithContent = std::make_unique<Event>("created", "resource", std::move(content));

  SECTION("type is correct") {
    REQUIRE(eventNoContent->getTypeId() == "event");
    REQUIRE(eventWithContent->getTypeId() == "event");
  }

  SECTION("event type retained") {
    REQUIRE(eventNoContent->getEventType() == "created");
    REQUIRE(eventWithContent->getEventType() == "created");
  }

  SECTION("resource retained") {
    REQUIRE(eventNoContent->getResource() == "resource");
    REQUIRE(eventWithContent->getResource() == "resource");
  }

  SECTION("content retained") {
    REQUIRE(eventWithContent->getContent() == contentPtr);
  }
}
