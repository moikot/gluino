#include "Utils/Testing.hpp"

#include "Serialization/RequestSerializer.hpp"
#include "Core/Memory.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("request serialization is not implemented", "[RequestSerializer]") {
  auto event = std::make_unique<Request>("sender", RequestType::Read, "res", std::make_unique<Content>());

  Mock<ISerializationContext> context;
  std::unique_ptr<ISerializer> serializer = std::make_unique<RequestSerializer>();

  auto result = serializer->serialize(context.get(), *event);
  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}

TEST_CASE("can deserialize a request", "[RequestSerializer]") {

  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();
  Mock<IDeserializationContext> context;

  When(Method(context, getString).Using("requestType")).Do([](const std::string&) {
    return std::make_tuple(Status::OK, "read");
  });

  When(Method(context, getString).Using("resource")).Do([](const std::string&) {
    return std::make_tuple(Status::OK, "resource");
  });

  When(Method(context, hasKey).Using("content")).Return(true);

  When(Method(context, getEntity).Using("content")).Do([&](const std::string&) {
    return std::make_tuple(Status::OK, std::move(content));
  });

  std::unique_ptr<ISerializer> serializer = std::make_unique<RequestSerializer>();
  Status result;
  std::unique_ptr<IEntity> entity;

  std::tie(result, entity) = serializer->deserialize(context.get());
  REQUIRE(result.isOk() == true);

  auto request = castToUnique<Request>(std::move(entity));
  REQUIRE(request->getRequestType() == RequestType::Read);
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
    When(Method(context, getString).Using("requestType")).Do([](const std::string&) {
      return std::make_tuple(Status::NotImplemented, "");
    });
  }

  SECTION("if getString for resource fails") {
    When(Method(context, getString).Using("requestType")).Do([](const std::string&) {
      return std::make_tuple(Status::OK, "read");
    });
    When(Method(context, getString).Using("resource")).Do([](const std::string&) {
      return std::make_tuple(Status::NotImplemented, "");
    });
  }

  SECTION("if getEntity fails") {
    When(Method(context, getString).Using("requestType")).Do([](const std::string&) {
      return std::make_tuple(Status::OK, "read");
    });
    When(Method(context, getString).Using("resource")).Do([](const std::string&) {
      return std::make_tuple(Status::OK, "resource");
    });
    When(Method(context, hasKey).Using("content")).Return(true);
    When(Method(context, getEntity).Using("content")).Do([](const std::string&) {
      return std::make_tuple(Status::NotImplemented, nullptr);
    });
  }

  std::unique_ptr<ISerializer> serializer = std::make_unique<RequestSerializer>();

  std::unique_ptr<IEntity> entity;
  Status result;
  std::tie(result, entity) = serializer->deserialize(context.get());

  REQUIRE(result.isOk() == false);
}
