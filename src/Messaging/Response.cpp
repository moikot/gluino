#include "Response.hpp"

using namespace Messaging;

Response::Response(
  std::string id,
  std::string receiver,
  RequestType requestType,
  std::string resource,
  std::unique_ptr<IEntity> content) :
  id(id),
  receiver(receiver),
  requestType(requestType),
  resource(resource),
  content(std::move(content)) {
}
