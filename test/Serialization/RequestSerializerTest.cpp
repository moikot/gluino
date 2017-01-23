#include "Utils/Testing.hpp"

#include "Serialization/RequestSerializer.hpp"
#include "Core/Casting.hpp"

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

TEST_CASE("request serialization is not implemented", "[RequestSerializer]") {
  auto content = Content::makeShared();
  auto event = Request::makeUnique("get", "sender", "res", content);

  Mock<ISerializationContext> context;
  ISerializer::Unique serializer = RequestSerializer::makeUnique();

  auto result = serializer->serialize(*event, context.get());
  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}

TEST_CASE("can deserialize a request", "[RequestSerializer]") {

  auto content = Content::makeUnique();
  auto contentPtr = content.get();
  Mock<IDeserializationContext> context;

  When(Method(context, getString).Using("requestType", _)).Do([](const std::string&, std::string& value) {
    value = "requestType";
    return Status::OK;
  });

  When(Method(context, getString).Using("resource", _)).Do([](const std::string&, std::string& value) {
    value = "resource";
    return Status::OK;
  });

  When(Method(context, hasKey).Using("content")).Return(true);

  When(Method(context, getEntity).Using("content", _)).Do([&](const std::string&, Core::IEntity::Unique& entity) {
    entity = std::move(content);
    return Status::OK;
  });

  ISerializer::Unique serializer = RequestSerializer::makeUnique();
  IEntity::Unique entity;

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result.isOk() == true);

  auto request = castToUnique<Request>(std::move(entity));
  REQUIRE(request->getRequestType() == "requestType");
  REQUIRE(request->getSender() == "");
  REQUIRE(request->getResource() == "resource");
  REQUIRE(request->getContent() == contentPtr);

  Verify(Method(context, getString));
  Verify(Method(context, hasKey));
  Verify(Method(context, getEntity));
}

TEST_CASE("request deserialization fails", "[RequestSerializer]") {
  Mock<IDeserializationContext> context;

  SECTION("if getString for requestType fails") {
    When(Method(context, getString).Using("requestType", _)).Do([](const std::string&, std::string&) {
      return Status::NotImplemented;
    });
  }

  SECTION("if getString for resource fails") {
    When(Method(context, getString).Using("requestType", _)).Do([](const std::string&, std::string& value) {
      value = "requestType";
      return Status::OK;
    });
    When(Method(context, getString).Using("resource", _)).Do([](const std::string&, std::string&) {
      return Status::NotImplemented;
    });
  }

  SECTION("if getEntity fails") {
    When(Method(context, getString).Using("requestType", _)).Do([](const std::string&, std::string& value) {
      value = "requestType";
      return Status::OK;
    });
    When(Method(context, getString).Using("resource", _)).Do([](const std::string&, std::string& value) {
      value = "resource";
      return Status::OK;
    });
    When(Method(context, hasKey).Using("content")).Return(true);
    When(Method(context, getEntity).Using("content", _)).Do([&](const std::string&, Core::IEntity::Unique&) {
      return Status::NotImplemented;
    });
  }

  ISerializer::Unique serializer = RequestSerializer::makeUnique();

  IEntity::Unique entity;
  auto result = serializer->deserialize(entity, context.get());

  REQUIRE(result.isOk() == false);
}
