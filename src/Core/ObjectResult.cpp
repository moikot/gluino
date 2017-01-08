#include "ObjectResult.hpp"

using namespace Core;

ObjectResult::ObjectResult(StatusCode statusCode, IEntity::Unique entity) : 
  ActionResult(statusCode),
  entity(std::move(entity)) {

}
