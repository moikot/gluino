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

TEST_CASE("test", "[EventSerializer]") {
  auto content = Content::makeShared();
  auto event = Event::makeUnique("get", "resource", content);

  Mock<ISerializationContext> context;
  When(OverloadedMethod(context,setValue,Core::StatusResult::Unique
    (const std::string& key, const std::string& value))).AlwaysDo([](const std::string& key, const std::string& value) {
    return StatusResult::OK();
  });
  When(OverloadedMethod(context,setValue,Core::StatusResult::Unique
    (const std::string& key, const Core::IEntity& entity))).AlwaysDo([](const std::string& key, const Core::IEntity& entity) {
    return StatusResult::OK();
  });

  ISerializer::Unique serializer = EventSerializer::makeUnique();
  serializer->serialize(*event, context.get());
}
