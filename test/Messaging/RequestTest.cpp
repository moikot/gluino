#include "catch.hpp"

#include "Messaging/Request.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Request::Unique createRequest(IEntity::Shared content) {
    return Request::makeUnique("sender", ActionType::Get, "resource", content);
  }

}

TEST_CASE("Request can be constructed", "[Request]") {

  auto content = Content::makeShared();
  auto request = createRequest(content);

  SECTION("sender retained") {
    REQUIRE(request->getSender() == "sender");
  }

  SECTION("action type retained") {
    REQUIRE(request->getActionType() == ActionType::Get);
  }

  SECTION("resource retained") {
    REQUIRE(request->getResource() == "resource");
  }

  SECTION("result retained") {
    REQUIRE(request->getContent() == content.get());
  }

}
