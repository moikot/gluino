// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_NOTIFICATION_HPP
#define CORE_NOTIFICATION_HPP

#include "Message.hpp"

namespace Core {

class Notification : public Message {
  TYPE_INFO(Notification, Message, "notification")
  public:
    Notification(std::string sender, std::string receiver,
      ActionType actionType, std::string resource, IEntity::Shared result);

    const IEntity* getContent() const { return result.get(); };

  private:
    IEntity::Shared result;
};

}

#endif /* end of include guard: CORE_NOTIFICATION_HPP */
