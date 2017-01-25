// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_EVENT_HPP
#define MESSAGING_EVENT_HPP

#include "Core/IEntity.hpp"

namespace Messaging {

/**
  The notification message.
*/
class Event : public Core::IEntity {
  TYPE_INFO(Event, IEntity, "event")
  public:
  	/**
  	Constructs an event.
  	*/
    Event(std::string eventType, std::string resource);

  	/**
  	Constructs an event.
  	*/
    Event(std::string eventType, std::string resource, IEntity::Shared content);

    /**
      The event type (created, updated, deleted etc.).
    */
    std::string getEventType() const { return eventType; }

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
    std::string     resource;
    IEntity::Shared content;
};

}

#endif /* end of include guard: MESSAGING_EVENT_HPP */
