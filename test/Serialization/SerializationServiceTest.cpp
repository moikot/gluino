#include "catch.hpp"
#include "fakeit.hpp"

#include "Serialization/SerializationService.hpp"

using namespace Core;
using namespace Serialization;

using namespace fakeit;
using namespace std::placeholders;

namespace {

  class Content : public Core::IEntity {
    TYPE_INFO(Content, Core::IEntity, "content")
  };

}

TEST_CASE("can serialize an entity", "[SerializationService]") {

  Mock<ISerializationContext> contextInstance;
  When(Dtor(contextInstance)).Do([](){});

  When(Method(contextInstance, setString).Using("_type","content")).Do([](const std::string&, const std::string&) {
    return Status::OK();
  });

  When(Method(contextInstance, toString)).Return("serialized");

  Mock<IContextFactory> factoryInstance;
  When(Dtor(factoryInstance)).Do([](){});

  When(Method(factoryInstance, createSerializationContext)).Do([&](
    const ISerializationService& serializationService,
    ISerializationContext::Unique& context) {
    ISerializationContext::Unique con(&contextInstance.get());
    context = std::move(con);
    return Status::OK();
  });

  Mock<ISerializer> serializerInstance;
  When(Dtor(serializerInstance)).Do([](){});

  When(Method(serializerInstance, getTypeId)).Return(Content::TypeId());

  When(Method(serializerInstance, serialize)).Do([](
    const Core::IEntity& entity,
    ISerializationContext& context) {
    return Status::OK();
  });

  ISerializer::Shared serializer(&serializerInstance.get());
  IContextFactory::Shared factory(&factoryInstance.get());

  auto service = SerializationService::makeUnique(factory);
  service->addSerializer(serializer);

  auto entity = Content::makeUnique();
  std::string json;
  auto result = service->serialize(*entity, json);
  REQUIRE(result->isOk() == true);
}
