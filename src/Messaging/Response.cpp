#include "Response.hpp"

using namespace Messaging;

Response::Response(
  std::string requestType,
  std::string sender,
  std::string receiver,
  std::string resource,
  IEntity::Shared content
) :
  requestType(requestType),
  sender(sender),
  receiver(receiver),
  resource(resource),
  content(content) {
}
