#include "ResponseSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

StatusResult::Unique
ResponseSerializer::serialize(
  const Response& response,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ACTION, response.getActionType().getType());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RESOURCE, response.getResource());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_CONTENT, response.getContent());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

StatusResult::Unique
ResponseSerializer::deserialize(Response::Unique&, ISerializationContext&) const {
  return StatusResult::NotImplemented();
}
