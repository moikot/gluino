#include "Response.hpp"

using namespace Messaging;

Response::Response(
  const std::string& id,
  const std::string& receiver,
  const RequestType& requestType,
  const std::string& resource,
  std::unique_ptr<IEntity> content) :
  id(id),
  receiver(receiver),
  requestType(requestType),
  resource(resource),
  content(std::move(content)) {
}
