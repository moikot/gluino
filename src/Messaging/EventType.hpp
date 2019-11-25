// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_EVENT_TYPE_HPP
#define MESSAGING_EVENT_TYPE_HPP

#include <string>

namespace Messaging {

/**
  The notification message.
*/
class EventType {
  public:

    /**
  	  A resource was created.
  	*/
    static EventType Created;

    /**
  	  A resource was updated.
  	*/
    static EventType Updated;

    /**
      A resource was deleted.
    */
    static EventType Deleted;

  	/**
  	  Constructs an event type.
  	*/
    explicit EventType(const std::string& eventType);

    /**
  	  Equality operators.
  	*/
    bool operator==(const EventType& other) const {
      return eventType == other.eventType;
    }

    bool operator!=(const EventType& other) const {
      return !(*this == other);
    }

    /**
  	  Convert to string.
  	*/
    operator const std::string() const { return eventType; }

  private:
    std::string     eventType;
};

}

#endif /* end of include guard: MESSAGING_EVENT_HPP */
