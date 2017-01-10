#include <gtest/gtest.h>

#include "Core/StatusResult.hpp"
#include "Messaging/Response.hpp"

using namespace Core;
using namespace Messaging;

namespace {

  Response::Unique createResponse(Core::ActionResult::Unique result) {
    return Response::makeUnique("sender", "receiver", ActionType::Get, "resource", std::move(result));
  }

}

TEST(Response, Sender_Retained) {
  auto response = createResponse(nullptr);
  ASSERT_EQ(response->getSender(), "sender");
}

TEST(Response, Receiver_Retained) {
  auto response = createResponse(nullptr);
  ASSERT_EQ(response->getReceiver(), "receiver");
}

TEST(Response, ActionType_Retained) {
  auto response = createResponse(nullptr);
  ASSERT_EQ(response->getActionType(), ActionType::Get);
}

TEST(Response, Resource_Retained) {
  auto response = createResponse(nullptr);
  ASSERT_EQ(response->getResource(), "resource");
}

TEST(Response, Result_Retained) {
  auto result = StatusResult::OK();
  auto response = createResponse(std::move(result));
  ASSERT_EQ(response->getResult().getStatusCode(), StatusCode::OK);
}
