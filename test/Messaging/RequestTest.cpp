#include "Utils/Testing.hpp" 

#include "Core/Memory.hpp"
#include "Messaging/Request.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("Request can be constructed", "[Request]") {
	auto content = std::make_unique<Content>();
	auto contentPtr = content.get();

	auto requestNoContent = std::make_unique<Request>("sender", "get", "resource");
	auto requestWithContent = std::make_unique<Request>("sender", "get", "resource", std::move(content));

	SECTION("type is correct") {
		REQUIRE(requestNoContent->getTypeId() == "request");
		REQUIRE(requestWithContent->getTypeId() == "request");
	}

	SECTION("sender retained") {
		REQUIRE(requestNoContent->getSender() == "sender");
		REQUIRE(requestWithContent->getSender() == "sender");
	}

	SECTION("requestWithContent type retained") {
		REQUIRE(requestNoContent->getRequestType() == "get");
		REQUIRE(requestWithContent->getRequestType() == "get");
	}

	SECTION("resource retained") {
		REQUIRE(requestNoContent->getResource() == "resource");
		REQUIRE(requestWithContent->getResource() == "resource");
	}

	SECTION("result retained") {
		REQUIRE(requestNoContent->getContent() == nullptr);
		REQUIRE(requestWithContent->getContent() == contentPtr);
	}
}

TEST_CASE("Sender can be changed", "[Request]") {
	auto request = std::make_unique<Request>("sender", "get", "resource");

	request->setSender("new_sender");

	REQUIRE(request->getSender() == "new_sender");
}