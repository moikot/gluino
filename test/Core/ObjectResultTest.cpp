#include <gtest/gtest.h>

#include "Core/StatusResult.hpp"
#include "Core/ObjectResult.hpp"

using namespace Core;

TEST(ObjectResult, Status_Code_Retained) {
  auto obj = StatusResult::makeUnique(StatusCode::OK, "test");
  auto result = ObjectResult::makeUnique(StatusCode::OK, std::move(obj));
  ASSERT_EQ(result->getStatusCode(), StatusCode::OK);
}

TEST(ObjectResult, Object_Retained) {
  auto obj = StatusResult::makeUnique(StatusCode::OK, "test");
  auto objPtr = obj.get();
  auto result = ObjectResult::makeUnique(StatusCode::OK, std::move(obj));
  ASSERT_EQ(&result->getObject(), objPtr);
}
