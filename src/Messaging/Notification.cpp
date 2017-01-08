#include "Notification.hpp"

using namespace Core;

Notification::Notification(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, IEntity::Shared result) :
  Message(sender, receiver, actionType, resource, Priority::Low), result(result) {
}
