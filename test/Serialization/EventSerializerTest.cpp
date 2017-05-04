#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Serialization/EventSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize a request", "[EventSerializer]") {
  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();

  auto event = std::make_unique<Event>(EventType::Created, "res", std::move(content));

  Mock<ISerializationContext> context;

  When(Method(context, setString).Using("eventType", "created")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, setString).Using("resource", "res")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "content");
    REQUIRE(&entity == contentPtr);
    return Status::OK;
  });

  std::unique_ptr<ISerializer> serializer = std::make_unique<EventSerializer>();

  auto result = serializer->serialize(context.get(), *event);
  REQUIRE(result.isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("event serialization fails", "[EventSerializer]") {
  Mock<ISerializationContext> context;

  SECTION("if setString fails for eventType") {
    When(Method(context, setString).Using("eventType", "created")).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setString fails for resource") {
    When(Method(context, setString).Using("eventType", "created")).Return(
      Status::OK
    );
    When(Method(context, setString).Using("resource", "res")).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setEntity fails") {
    When(Method(context, setString).Using("eventType", "created")).Return(
      Status::OK
    );
    When(Method(context, setString).Using("resource", "res")).Return(
      Status::OK
    );
    When(Method(context, setEntity)).Return(
      Status::NotImplemented
    );
  }

  auto event = std::make_unique<Event>(EventType::Created, "res", std::make_unique<Content>());

  std::unique_ptr<ISerializer> serializer = std::make_unique<EventSerializer>();
  auto result = serializer->serialize(context.get(), *event);

  REQUIRE(result.isOk() == false);
}

TEST_CASE("event deserialization is not implemented", "[EventSerializer]") {
  Status result;
  std::unique_ptr<IEntity> entity;
  Mock<IDeserializationContext> context;

  std::unique_ptr<ISerializer> serializer = std::make_unique<EventSerializer>();

  std::tie(result, entity) = serializer->deserialize(context.get());
  REQUIRE(result.getCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getCode() == StatusCode::NotImplemented);
}
