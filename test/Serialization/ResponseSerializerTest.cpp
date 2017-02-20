#include "Utils/Testing.hpp"

#include "Core/Memory.hpp"
#include "Serialization/ResponseSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

using namespace fakeit;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize a response", "[ResponseSerializer]") {
  auto content = std::make_unique<Content>();
  auto contentPtr = content.get();

  auto response = std::make_unique<Response>("rec", "get", "res", std::move(content));

  Mock<ISerializationContext> context;

  When(Method(context, setString).Using("requestType","get")).Do([](const std::string&, const std::string&) {
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

  std::unique_ptr<ISerializer> serializer = std::make_unique<ResponseSerializer>();

  auto result = serializer->serialize(*response, context.get());
  REQUIRE(result.isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("response serialization fails", "[ResponseSerializer]") {
  Mock<ISerializationContext> context;

  SECTION("if setString for requestType fails") {
    When(Method(context, setString).Using("requestType","get")).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setString for resource fails") {
    When(Method(context, setString).Using("requestType","get")).Return(
      Status::OK
    );
    When(Method(context, setString).Using("resource", "res")).Return(
      Status::NotImplemented
    );
  }

  SECTION("if setEntity fails") {
    When(Method(context, setString).Using("requestType","get")).Return(
      Status::OK
    );
    When(Method(context, setString).Using("resource", "res")).Return(
      Status::OK
    );
    When(Method(context, setEntity)).Return(
      Status::NotImplemented
    );
  }

  auto response = std::make_unique<Response>("rec", "get", "res", std::make_unique<Content>());

  std::unique_ptr<ISerializer> serializer = std::make_unique<ResponseSerializer>();
  auto result = serializer->serialize(*response, context.get());

  REQUIRE(result.isOk() == false);
}

TEST_CASE("response deserialization is not implemented", "[ResponseSerializer]") {
  std::unique_ptr<IEntity> entity;
  Mock<IDeserializationContext> context;

  std::unique_ptr<ISerializer> serializer = std::make_unique<ResponseSerializer>();

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result.getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result.getInnerStatus()->getStatusCode() == StatusCode::NotImplemented);
}
