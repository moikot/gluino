#include "catch.hpp"
#include "fakeit.hpp"

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

TEST_CASE("can deserialize a request", "[RequestSerializer]") {

  auto content = Content::makeUnique();
  auto contentPtr = content.get();
  Mock<ISerializationContext> context;

  When(Method(context, getString).Using("requestType", _)).Do([](const std::string&, std::string& value) {
    value = "requestType";
    return StatusResult::OK();
  });

  When(Method(context, getString).Using("resource", _)).Do([](const std::string&, std::string& value) {
    value = "resource";
    return StatusResult::OK();
  });

  When(Method(context, hasKey).Using("content")).Return(true);
  When(Method(context, getEntity).Using("content", _)).Do([&](const std::string&, Core::IEntity::Unique& entity) {
    entity = std::move(content);
    return StatusResult::OK();
  });

  ISerializer::Unique serializer = RequestSerializer::makeUnique();
  IEntity::Unique entity;

  auto result = serializer->deserialize(entity, context.get());
  REQUIRE(result->isOk() == true);

  auto request = castToUnique<Request>(std::move(entity));
  REQUIRE(request->getRequestType() == "requestType");
  REQUIRE(request->getSender() == "");
  REQUIRE(request->getResource() == "resource");
  REQUIRE(request->getContent() == contentPtr);

  Verify(Method(context, getString));
  Verify(Method(context, hasKey));
  Verify(Method(context, getEntity));
}