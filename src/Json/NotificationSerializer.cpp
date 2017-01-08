#include "NotificationSerializer.hpp"

using namespace Core;
using namespace Json;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Core::StatusResult::Unique
NotificationSerializer::serialize(
  const Notification& notification,
  ISerializationContext& context) const {

  auto result = context.setValue(FIELD_ACTION, notification.getActionType().getId());
  if (!result->isOk())
    return result;

  result = context.setValue(FIELD_RESOURCE, notification.getResource());
  if (!result->isOk())
    return result;

  auto content = notification.getContent();
  if (content) {
    result = context.setValue(FIELD_CONTENT, *content);
    if (!result->isOk())
      return result;
  }

  return StatusResult::OK();
}

Core::StatusResult::Unique
NotificationSerializer::deserialize(Notification::Unique&, ISerializationContext&) const {
  return StatusResult::NotImplemented();
}
