#include "Utils/Testing.hpp"

#include "Serialization/ResponseSerializer.hpp"

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

TEST_CASE("can serialize a response", "[ResponseSerializer]") {
  auto content = Content::makeShared();
  auto response = Response::makeUnique("get", "rec", "res", content);

  Mock<ISerializationContext> context;

  When(Method(context, setString).Using("requestType","get")).Do([](const std::string&, const std::string&) {
    return Status::OK();
  });

  When(Method(context, setString).Using("resource", "res")).Do([](const std::string&, const std::string&) {
    return Status::OK();
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "content");
    REQUIRE(&entity == content.get());
    return Status::OK();
  });

  ISerializer::Unique serializer = ResponseSerializer::makeUnique();

  auto result = serializer->serialize(*response, context.get());
  REQUIRE(result->isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}

TEST_CASE("response deserialization is not implemented", "[ResponseSerializer]") {
  IEntity::Unique entity;
  Mock<IDeserializationContext> context;

  ISerializer::Unique serializer = ResponseSerializer::makeUnique();

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result->getStatusCode() == StatusCode::InternalServerError);
  REQUIRE(result->getInnerResult()->getStatusCode() == StatusCode::NotImplemented);
}
