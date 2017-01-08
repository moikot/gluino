#include "NotificationSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_ACTION "action"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

StatusResult::Unique
NotificationSerializer::serialize(
  const Messaging::Notification& notification,
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

StatusResult::Unique
NotificationSerializer::deserialize(Notification::Unique&, ISerializationContext&) const {
  return StatusResult::NotImplemented();
}
