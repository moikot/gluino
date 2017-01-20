#include "SerializationService.hpp"

#include <algorithm>

using namespace Serialization;
using namespace Core;

#define TYPE_FIELD "_type"

SerializationService::SerializationService(
  std::shared_ptr<const IContextFactory> contextFactory) :
  contextFactory(contextFactory) {
}

Core::StatusResult::Unique
SerializationService::serialize(
  const IEntity& entity,
  std::string& json) const {

  ISerializationContext::Unique context;
  auto result = contextFactory->createSerializationContext(*this, context);
  if (!result->isOk())
    return result;

  result = serialize(entity, *context);
  if (!result->isOk())
    return result;

  json = context->toString();
  return StatusResult::OK();
}

Core::StatusResult::Unique
SerializationService::serialize (
  const IEntity& entity,
  ISerializationContext& context) const {

  std::string typeId = entity.getTypeId();
  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return StatusResult::makeUnique(StatusCode::BadRequest,
      "Unable to find a serializer for type """ + typeId + """.");
  }
  context.setString(TYPE_FIELD, typeId);
  return serializer->serialize(entity, context);
}

Core::StatusResult::Unique
SerializationService::deserialize(
  const std::string& json,
  Core::IEntity::Unique& entity) const {

  IDeserializationContext::Unique context;
  auto actionResult = contextFactory->createDeserializationContext(*this, json, context);
  if (!actionResult->isOk())
    return actionResult;

  return deserialize(*context, entity);
}

Core::StatusResult::Unique
SerializationService::deserialize(
  IDeserializationContext& context,
  Core::IEntity::Unique& entity) const {

  std::string typeId;
  auto actionResult = context.getString(TYPE_FIELD, typeId);
  if (!actionResult->isOk())
    return actionResult;

  auto serializer = getSerialzier(typeId);
  if (!serializer) {
    return StatusResult::makeUnique(StatusCode::BadRequest,
      "Unable to find serializer for type """ + typeId + """.");
  }
  return serializer->deserialize(entity, context);
}

void
SerializationService::addSerializer(
  std::shared_ptr<const ISerializer> serializer) {
  serializers.push_back(serializer);
}

std::shared_ptr<const ISerializer>
SerializationService::getSerialzier(std::string typeId) const {

  auto findIter = std::find_if(serializers.begin(), serializers.end(),
    [&](std::shared_ptr<const ISerializer> serializer){
      return serializer->getTypeId() == typeId;
    });

  if (findIter == serializers.end())
    return nullptr;

  return *findIter;
}
