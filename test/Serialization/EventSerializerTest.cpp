#include "Utils/Testing.hpp"

#include "Serialization/EventSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

using namespace fakeit;
using namespace std::placeholders;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize a request", "[EventSerializer]") {
  auto content = Content::makeShared();
  auto event = Event::makeUnique("get", "res", content);

  Mock<ISerializationContext> context;

  When(Method(context, setString).Using("eventType","get")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, setString).Using("resource", "res")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "content");
    REQUIRE(&entity == content.get());
    return Status::OK;
  });

  ISerializer::Unique serializer = EventSerializer::makeUnique();

  auto result = serializer->serialize(*event, context.get());
  REQUIRE(result.isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("event serialization fails", "[EventSerializer]") {
  Mock<ISerializationContext> context;

  SECTION("if setString fails for eventType") {
    When(Method(context, setString).Using("eventType","get")).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setString fails for resource") {
    When(Method(context, setString).Using("eventType","get")).Return(
      Status::OK
    );
    When(Method(context, setString).Using("resource", "res")).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setEntity fails") {
    When(Method(context, setString).Using("eventType","get")).Return(
      Status::OK
    );
    When(Method(context, setString).Using("resource", "res")).Return(
      Status::OK
    );
    When(Method(context, setEntity)).Return(
      Status::NotImplemented
    );
  }

  auto event = Event::makeUnique("get", "res", Content::makeShared());

  ISerializer::Unique serializer = EventSerializer::makeUnique();
  auto result = serializer->serialize(*event, context.get());

  REQUIRE(result.isOk() == false);
}

/*
TEST_CASE("serialize fails if setString for resource fails", "[EventSerializer]") {
  Mock<ISerializationContext> context;

  When(Method(context, setString).Using("eventType","get")).Do([](const std::string&, const std::string&) {
    return Status::OK;
  });

  When(Method(context, setString).Using("resource", "res")).Do([](const std::string&, const std::string&) {
    return Status(StatusCode::InternalServerError, "error");
  });

  ISerializer::Unique serializer = EventSerializer::makeUnique();

  auto event = Event::makeUnique("get", "res");
  auto result = serializer->serialize(*event, context.get());
  REQUIRE(result.isOk() == false);

  Verify(Method(context, setString));
}
*/

TEST_CASE("event deserialization is not implemented", "[EventSerializer]") {
  IEntity::Unique entity;
  Mock<IDeserializationContext> context;

  ISerializer::Unique serializer = EventSerializer::makeUnique();

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}
