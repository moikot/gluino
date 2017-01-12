#include "catch.hpp"

#include "Messaging/ActionType.hpp"

using namespace Messaging;

TEST_CASE("equality", "[ActionType]") {

  SECTION("same action types are equal") {
    auto type1 = ActionType::getById(ActionType::Unknown.getId());
    auto type2 = ActionType::getById(ActionType::Unknown.getId());
    REQUIRE(type1 == type2);
  }

  SECTION("different action types are not equal") {
    auto type1 = ActionType::getById(ActionType::Get.getId());
    auto type2 = ActionType::getById(ActionType::Unknown.getId());
    REQUIRE(type1 != type2);
  }

}

TEST_CASE("getting action type by id", "[ActionType]") {

  SECTION("can get Get action type") {
    auto type = ActionType::getById(ActionType::Get.getId());
    REQUIRE(type == ActionType::Get);
  }

  SECTION("can get Create action type") {
    auto type = ActionType::getById(ActionType::Create.getId());
    REQUIRE(type == ActionType::Create);
  }

  SECTION("can get Update action type") {
    auto type = ActionType::getById(ActionType::Update.getId());
    REQUIRE(type == ActionType::Update);
  }

  SECTION("can get Delete action type") {
    auto type = ActionType::getById(ActionType::Delete.getId());
    REQUIRE(type == ActionType::Delete);
  }

  SECTION("can get Unknown action type") {
    auto type = ActionType::getById(ActionType::Unknown.getId());
    REQUIRE(type == ActionType::Unknown);
  }

  SECTION("can get Unknown action type by empty id") {
    auto type = ActionType::getById("");
    REQUIRE(type == ActionType::Unknown);
  }

}
