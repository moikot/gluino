// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESOURCE_EVENT_HANDLER_HPP
#define MESSAGING_RESOURCE_EVENT_HANDLER_HPP

#include "Event.hpp"

#include <functional>

namespace Messaging {

  class ResourceEventHandler {
    TYPE_PTRS_ABSTRACT(ResourceEventHandler)
    virtual std::string getEventType() const = 0;
    virtual std::string getContentType() const = 0;
    virtual void processEvent(const Event& event) const = 0;
  };

  class ResourceEventHandlerVoid : public ResourceEventHandler {
    TYPE_PTRS(ResourceEventHandlerVoid)
    public:
      ResourceEventHandlerVoid(
        std::string eventType,
        std::function<void()> onEvent) :
        eventType(eventType),
        onEvent(onEvent) {
      }

      virtual std::string getEventType() const override {
        return eventType;
      }

      virtual std::string getContentType() const override {
        return "";
      }

      virtual void processEvent(const Event&) const override {
          onEvent();
      }

    private:
      const std::string eventType;
      const std::function<void()> onEvent;
  };

  template<class T>
  class ResourceEventHandlerTyped : public ResourceEventHandler {
    TYPE_PTRS(ResourceEventHandlerTyped)
    public:
      ResourceEventHandlerTyped(
        std::string eventType,
        std::function<void(const T&)> onEvent) :
        eventType(eventType),
        onEvent(onEvent) {
      }

      virtual std::string getEventType() const override {
        return eventType;
      }

      virtual std::string getContentType() const override {
        return T::getType();
      }

      virtual void processEvent(const Event& event) const override {
        onEvent(event.getContent());
      }

    private:
      const std::string eventType;
      const std::function<void(const T&)> onEvent;
  };

}

#endif /* end of include guard: MESSAGING_RESOURCE_EVENT_HANDLER_HPP */
