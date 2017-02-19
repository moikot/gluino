#include "EventSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_EVENT_TYPE "eventType"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Status
EventSerializer::serialize(
  const Messaging::Event& event,
  ISerializationContext& context) const {

  auto result = context.setString(FIELD_EVENT_TYPE, event.getEventType());
  if (!result.isOk())
    return result;

  result = context.setString(FIELD_RESOURCE, event.getResource());
  if (!result.isOk())
    return result;

  auto content = event.getContent();
  if (content) {
    result = context.setEntity(FIELD_CONTENT, *content);
    if (!result.isOk())
      return result;
  }

  return Status::OK;
}

Status
EventSerializer::deserialize(std::unique_ptr<Event>&, IDeserializationContext&) const {
  return Status::NotImplemented;
}
