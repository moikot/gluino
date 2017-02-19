#include "Utils/Testing.hpp"

#include "Core/Casting.hpp"
#include "Core/Status.hpp"
#include "Messaging/Response.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("Response can be constructed", "[Response]") {
  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();

  auto response = std::make_unique<Response>("receiver", "get", "resource", std::move(content));

  SECTION("type is correct") {
    REQUIRE(response->getTypeId() == "response");
  }

  SECTION("receiver retained") {
	REQUIRE(response->getReceiver() == "receiver");
  }

  SECTION("request type retained") {
    REQUIRE(response->getRequestType() == "get");
  }

  SECTION("resource retained") {
    REQUIRE(response->getResource() == "resource");
  }

  SECTION("content retained") {
    REQUIRE(&response->getContent() == contentPtr);
  }
}

TEST_CASE("Receiver can be changed", "[Request]") {
	auto response = std::make_unique<Response>("receiver", "get", "resource", std::make_unique<Content>());

	response->setReceiver("new_receiver");

	REQUIRE(response->getReceiver() == "new_receiver");
}