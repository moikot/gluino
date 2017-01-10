#include "Notification.hpp"

using namespace Messaging;

Notification::Notification(std::string sender, std::string receiver,
  ActionType actionType, std::string resource, IEntity::Shared content) :
  Message(sender, receiver, actionType, resource, Priority::Low), content(content) {
}
