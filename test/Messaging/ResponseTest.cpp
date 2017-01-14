#include "catch.hpp"

#include "Core/StatusResult.hpp"
#include "Messaging/Response.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  Response::Unique createResponse(Core::StatusResult::Unique result) {
    return Response::makeUnique("sender", "receiver", ActionType::Get, "resource", std::move(result));
  }

}

TEST_CASE("Response can be constructed", "[Response]") {

  auto result = createResponse(nullptr);

  SECTION("sender retained") {
    REQUIRE(result->getSender() == "sender");
  }

  SECTION("receiver retained") {
    REQUIRE(result->getReceiver() == "receiver");
  }

  SECTION("action type retained") {
    REQUIRE(result->getActionType() == ActionType::Get);
  }

  SECTION("resource retained") {
    REQUIRE(result->getResource() == "resource");
  }

  SECTION("result retained") {
    auto result = StatusResult::OK();
    auto resultPtr = result.get();
    auto response = createResponse(std::move(result));
    REQUIRE(&response->getResult() == resultPtr);
  }

}
