#include "catch.hpp"
#include "fakeit.hpp"

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
    return StatusResult::OK();
  });

  When(Method(context, setString).Using("resource", "res")).Do([](const std::string&, const std::string&) {
    return StatusResult::OK();
  });

  When(Method(context, setEntity)).Do([=](const std::string& key, const Core::IEntity& entity) {
    REQUIRE(key == "content");
    REQUIRE(&entity == content.get());
    return StatusResult::OK();
  });

  ISerializer::Unique serializer = EventSerializer::makeUnique();

  auto result = serializer->serialize(*event, context.get());
  REQUIRE(result->isOk() == true);

  Verify(Method(context, setString));
  Verify(Method(context, setEntity));
}
