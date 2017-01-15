#include "catch.hpp"

#include "Messaging/ActionType.hpp"

using namespace Messaging;

TEST_CASE("equality", "[ActionType]") {

  SECTION("same action types are equal") {
    auto type1 = ActionType("action");
    auto type2 = ActionType("action");
    REQUIRE(type1 == type2);
  }

  SECTION("different action types are not equal") {
    auto type1 = ActionType("action_1");
    auto type2 = ActionType("action_2");
    REQUIRE(type1 != type2);
  }

}
