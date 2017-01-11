#include "catch.hpp"

#include "Messaging/Request.hpp"

using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Request::Unique createRequest(Content::Unique content) {
    return Request::makeUnique("sender", ActionType::Get, "resource", std::move(content));
  }

}

TEST_CASE("Request can be constructed", "[Request]") {

  auto request = createRequest(nullptr);

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
    auto content = Content::makeUnique();
    auto contentPtr = content.get();
    auto response = createRequest(std::move(content));
    REQUIRE(response->getContent() == contentPtr);
  }

}