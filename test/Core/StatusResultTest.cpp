
#include <gtest/gtest.h>

#include "Core/StatusResult.hpp"

using namespace Core;

TEST(StatusResult, Status_Code_Retained) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_EQ(result->getStatusCode(), StatusCode::OK);
}

TEST(StatusResult, Message_Retained) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_EQ(result->getMessage(), "test");
}
