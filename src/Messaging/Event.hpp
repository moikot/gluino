// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_EVENT_HPP
#define MESSAGING_EVENT_HPP

#include "EventType.hpp"
#include "Core/IEntity.hpp"

#include <memory>

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
    Event(const EventType& eventType, const std::string& resource);

  	/**
  	  Constructs an event.
  	*/
    Event(const EventType& eventType, const std::string& resource, std::unique_ptr<IEntity> content);

    /**
      The event type (created, updated, deleted etc.).
    */
    EventType getEventType() const { return eventType; }

    /**
      The resource.
    */
    std::string getResource() const { return resource; }

    /**
      The notification content.
    */
    const IEntity* getContent() const { return content.get(); };

  private:
    EventType       eventType;
    std::string     resource;
    std::unique_ptr<IEntity> content;
};

}

#endif /* end of include guard: MESSAGING_EVENT_HPP */
