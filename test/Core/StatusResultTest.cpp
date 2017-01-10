#include <gtest/gtest.h>

#include "Core/StatusResult.hpp"

using namespace Core;

TEST(StatusResult, OK_Status_Result_Has_OK_Status_Code) {
  ASSERT_EQ(StatusCode::OK, StatusResult::OK()->getStatusCode());
}

TEST(StatusResult, NotImplimented_Status_Result_Has_NotImplemented_Status_Code) {
  ASSERT_EQ(StatusCode::NotImplemented, StatusResult::NotImplemented()->getStatusCode());
}

TEST(StatusResult, Is_OK_When_Status_Code_Is_OK) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_TRUE(result->isOk());
}

TEST(StatusResult, Is_Not_OK_When_Status_Code_Is_Not_OK) {
  auto result = StatusResult::makeUnique(StatusCode::Accepted, "test");
  ASSERT_FALSE(result->isOk());
}

TEST(StatusResult, Is_Accepted_When_Status_Code_Is_Accepted) {
  auto result = StatusResult::makeUnique(StatusCode::Accepted, "test");
  ASSERT_TRUE(result->isAccepted());
}

TEST(StatusResult, Is_Not_Accepted_When_Status_Code_Is_Not_Accepted) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_FALSE(result->isAccepted());
}

TEST(StatusResult, Status_Code_Retained) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_EQ(result->getStatusCode(), StatusCode::OK);
}

TEST(StatusResult, Message_Retained) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_EQ(result->getMessage(), "test");
}

TEST(StatusResult, Inner_Result_Is_Null_By_Default) {
  auto result = StatusResult::makeUnique(StatusCode::OK, "test");
  ASSERT_EQ(result->getInnerReuslt(), nullptr);
}

TEST(StatusResult, Inner_Result_Is_Retained) {
  auto inner = StatusResult::makeUnique(StatusCode::OK, "test");
  auto innerPtr = inner.get();
  auto result = StatusResult::makeUnique(StatusCode::OK, "test", std::move(inner));
  ASSERT_EQ(result->getInnerReuslt(), innerPtr);
}
