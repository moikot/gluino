// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_NOTIFICATION_HPP
#define CORE_NOTIFICATION_HPP

#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The notification message.
*/
class Event : public Core::IEntity {
  TYPE_INFO(Event, IEntity, "notification")
  public:
    Event(
      std::string     eventType,
      std::string     sender,
      std::string     resource,
      IEntity::Shared content
    );

    /**
      The event type (created, updated, deleted stc.).
    */
    std::string getEventType() const { return eventType; }

    /**
      The notification sender.
    */
    std::string getSender() const { return sender; };

    /**
      The resource.
    */
    std::string getResource() const { return resource; }

    /**
      The notification content.
    */
    const IEntity* getContent() const { return content.get(); };

  private:
    std::string     eventType;
    std::string     sender;
    std::string     resource;
    IEntity::Shared content;
};

}

#endif /* end of include guard: CORE_NOTIFICATION_HPP */
