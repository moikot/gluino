
#include <gtest/gtest.h>

#include "Core/ActionType.hpp"

using namespace Core;

TEST(ActionType, Same_Action_Types_Are_Equal) {
  auto type1 = ActionType::getById(ActionType::Unknown.getId());
  auto type2 = ActionType::getById(ActionType::Unknown.getId());
  ASSERT_EQ(type1, type2);
}

TEST(ActionType, Different_Action_Types_Are_Not_Equal) {
  auto type1 = ActionType::getById(ActionType::Unknown.getId());
  auto type2 = ActionType::getById(ActionType::Get.getId());
  ASSERT_NE(type1, type2);
}

TEST(ActionType, Can_Get_Action_Type_Get_By_Id) {
  auto type = ActionType::getById(ActionType::Get.getId());
  ASSERT_EQ(type, ActionType::Get);
}

TEST(ActionType, Can_Get_Action_Type_Create_By_Id) {
  auto type = ActionType::getById(ActionType::Create.getId());
  ASSERT_EQ(type, ActionType::Create);
}

TEST(ActionType, Can_Get_Action_Type_Update_By_Id) {
  auto type = ActionType::getById(ActionType::Update.getId());
  ASSERT_EQ(type, ActionType::Update);
}

TEST(ActionType, Can_Get_Action_Type_Delete_By_Id) {
  auto type = ActionType::getById(ActionType::Delete.getId());
  ASSERT_EQ(type, ActionType::Delete);
}

TEST(ActionType, Can_Get_Action_Type_Unknown_By_Id) {
  auto type = ActionType::getById(ActionType::Unknown.getId());
  ASSERT_EQ(type, ActionType::Unknown);
}

TEST(ActionType, Can_Get_Action_Type_Unknown_By_Empty_Id) {
  auto type = ActionType::getById("");
  ASSERT_EQ(type, ActionType::Unknown);
}
