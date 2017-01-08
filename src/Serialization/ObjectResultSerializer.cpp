#include "ObjectResultSerializer.hpp"

using namespace Core;
using namespace Serialization;

#define FIELD_CODE "code"
#define FIELD_OBJECT "object"

Core::StatusResult::Unique
ObjectResultSerializer::serialize(
  const ObjectResult& objectResult,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_CODE, (int)objectResult.getStatusCode());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_OBJECT, objectResult.getObject());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
ObjectResultSerializer::deserialize(ObjectResult::Unique&, ISerializationContext&) const {
  return StatusResult::NotImplemented();
}
