#include "RequestSerializer.hpp"

using namespace Core;
using namespace Json;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Core::StatusResult::Unique
RequestSerializer::serialize(
  const Request& request,
  ISerializationContext& context) const {
  return StatusResult::NotImplemented();
}

Core::StatusResult::Unique
RequestSerializer::deserialize(
  Request::Unique& request,
  ISerializationContext& context) const {

  std::string actionTypeStr;
  auto result = context.getStringValue(FIELD_ACTION, actionTypeStr);
  if (!result->isOk())
    return result;

  ActionType actionType = ActionType::getById(actionTypeStr);
  if (actionType == ActionType::Unknown)
    return StatusResult::makeUnique(StatusCode::BadRequest,
      "Action type '" + actionTypeStr + "' is not supported.");

  std::string resource;
  result = context.getStringValue(FIELD_RESOURCE, resource);
  if (!result->isOk())
    return result;

  Core::IEntity::Unique content;
  if (context.hasKey(FIELD_CONTENT)) {
    result = context.getEntity(FIELD_CONTENT, content);
    if (!result->isOk())
      return result;
  }

  request = Request::makeUnique(actionType, resource, std::move(content));
  return StatusResult::OK();
}
