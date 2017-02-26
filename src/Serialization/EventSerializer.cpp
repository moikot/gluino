#include "EventSerializer.hpp"

using namespace Core;
using namespace Messaging;
using namespace Serialization;

#define FIELD_EVENT_TYPE "eventType"
#define FIELD_RESOURCE "resource"
#define FIELD_CONTENT "content"

Status
EventSerializer::serializeImpl(ISerializationContext& context,
  const Messaging::Event& event) const {

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

std::tuple<Core::Status, std::unique_ptr<Messaging::Event>>
EventSerializer::deserializeImpl(const IDeserializationContext&) const {
  return std::make_tuple(Status::NotImplemented, nullptr);
}
