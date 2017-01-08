#include "ResponseSerializer.hpp"

using namespace Core;
using namespace Json;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_RESULT "result"

Core::StatusResult::Unique
ResponseSerializer::serialize(
  const Response& response,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ACTION, response.getActionType().getId());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RESOURCE, response.getResource());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RESULT, response.getResult());
  if (!result->isOk())
    return result;

  return StatusResult::OK();
}

Core::StatusResult::Unique
ResponseSerializer::deserialize(
  Response::Unique& response,
  ISerializationContext& context) const {

  return StatusResult::NotImplemented();
}
