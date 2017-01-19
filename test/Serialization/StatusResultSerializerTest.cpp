#include "catch.hpp"
#include "fakeit.hpp"

#include "Serialization/StatusResultSerializer.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;
using namespace std::placeholders;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize a status result", "[StatusResultSerializer]") {
  auto innerResult = StatusResult::makeUnique(StatusCode::NotImplemented, "notImplemented");
  auto innerResultPtr = innerResult.get();
  auto statusResult = StatusResult::makeUnique(StatusCode::InternalServerError, "serverError", std::move(innerResult));

  Mock<ISerializationContext> context;
  
  When(Method(context, setInt).Using("code", (int)StatusCode::InternalServerError)).Do([](const std::string&, int) {
    return StatusResult::OK();
  });

  When(Method(context, setString).Using("message", "serverError")).Do([](const std::string&, const std::string&) {
    return StatusResult::OK();
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "innerResult");
    REQUIRE(&entity == innerResultPtr);
    return StatusResult::OK();
  });

  ISerializer::Unique serializer = StatusResultSerializer::makeUnique();

  auto result = serializer->serialize(*statusResult, context.get());
  REQUIRE(result->isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}
