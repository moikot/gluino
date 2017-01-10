#include <gtest/gtest.h>

#include "Messaging/Request.hpp"

using namespace Messaging;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

  Request::Unique createRequest(Content::Unique content) {
    return Request::makeUnique("sender", ActionType::Get, "resource", std::move(content));
  }

}

TEST(Request, Sender_Retained) {
  auto response = createRequest(nullptr);
  ASSERT_EQ(response->getSender(), "sender");
}

TEST(Request, ActionType_Retained) {
  auto response = createRequest(nullptr);
  ASSERT_EQ(response->getActionType(), ActionType::Get);
}

TEST(Request, Resource_Retained) {
  auto response = createRequest(nullptr);
  ASSERT_EQ(response->getResource(), "resource");
}

TEST(Request, Result_Retained) {
  auto content = Content::makeUnique();
  auto contentPtr = content.get();
  auto response = createRequest(std::move(content));
  ASSERT_EQ(response->getContent(), contentPtr);
}
