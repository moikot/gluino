#include "SerializationService.hpp"

#include <algorithm>

using namespace Serialization;
using namespace Core;

#define TYPE_FIELD "_type"

SerializationService::SerializationService(const IContextFactory& contextFactory) :
  contextFactory(contextFactory) {
}

std::tuple<Core::Status, std::string>
SerializationService::serialize(const IEntity& entity) const {
  Core::Status result;
  std::unique_ptr<ISerializationContext> context;
  std::tie(result, context) = contextFactory.createSerializationContext(*this);
  if (!result.isOk())
    return std::make_tuple(result, "");

  result = serialize(*context, entity);
  if (!result.isOk())
    return std::make_tuple(result, "");

  return std::make_tuple(Status::OK, context->toString());
}

Core::Status
SerializationService::serialize(ISerializationContext& context, const IEntity& entity) const {
  std::string typeId = entity.getTypeId();
  auto result = context.setString(TYPE_FIELD, typeId);
  if (!result.isOk())
    return result;

  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return Status(StatusCode::BadRequest,
      "Unable to find a serializer for type """ + typeId + """.");
  }
  return serializer->serialize(context, entity);
}

std::tuple<Core::Status, std::unique_ptr<IEntity>>
SerializationService::deserialize(const std::string& json) const {
  Core::Status result;
  std::unique_ptr<IDeserializationContext> context;
  std::tie(result, context) = contextFactory.createDeserializationContext(*this, json);
  if (!result.isOk())
    return result;

  return deserialize(*context);
}

std::tuple<Core::Status, std::unique_ptr<IEntity>>
SerializationService::deserialize(const IDeserializationContext& context) const {
  Core::Status result;
  std::string typeId;
  std::tie(result, typeId) = context.getString(TYPE_FIELD);
  if (!result.isOk())
    return result;

  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return Status(StatusCode::BadRequest,
      "Unable to find serializer for type """ + typeId + """.");
  }
  return serializer->deserialize(context);
}

void
SerializationService::addSerializer(std::unique_ptr<ISerializer> serializer) {
  serializers.push_back(std::move(serializer));
}

const ISerializer*
SerializationService::getSerialzier(std::string typeId) const {
  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](const std::unique_ptr<ISerializer>& serializer){
      return serializer->getTypeId() == typeId;
    });

  if (findIter == serializers.end())
    return nullptr;

  return findIter->get();
}
