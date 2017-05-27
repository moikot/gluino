// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_RESOURCE_EVENT_HANDLER_HPP
#define MESSAGING_RESOURCE_EVENT_HANDLER_HPP

#include "Event.hpp"
#include "Core/Traits.hpp"

#include <functional>

namespace Messaging {

  struct ResourceEventHandler {
    virtual ~ResourceEventHandler() = default;
    virtual EventType getEventType() const = 0;
    virtual std::string getContentType() const = 0;
    virtual void processEvent(const Event& event) const = 0;
  };

  template <typename T, class = void>
  class ResourceEventHandlerImpl;

  template<typename T>
  class ResourceEventHandlerImpl<T,
    typename std::enable_if<Core::function_traits<T>::value == 0>::type> : public ResourceEventHandler {
    public:
      ResourceEventHandlerImpl(
        const EventType& eventType,
        T onEvent) :
        eventType(eventType),
        onEvent(onEvent) {
      }

      virtual EventType getEventType() const override {
        return eventType;
      }

      virtual std::string getContentType() const override {
        return "";
      }

      virtual void processEvent(const Event&) const override {
          onEvent();
      }

    private:
      const EventType eventType;
      const T onEvent;
  };

  template<typename T>
  class ResourceEventHandlerImpl<T,
    typename std::enable_if<Core::function_traits<T>::value == 1>::type> : public ResourceEventHandler {
    typedef typename Core::function_traits<T> traits;
    public:
      ResourceEventHandlerImpl(
        const EventType& eventType,
        T onEvent) :
        eventType(eventType),
        onEvent(onEvent) {
      }

      virtual EventType getEventType() const override {
        return eventType;
      }

      virtual std::string getContentType() const override {
        return Core::base_type<typename traits::template arg<0>::type>::TypeId();
      }

      virtual void processEvent(const Event& event) const override {
        onEvent(static_cast<typename traits::template arg<0>::type>(*event.getContent()));
      }

    private:
      const EventType eventType;
      const T onEvent;
  };

}

#endif /* end of include guard: MESSAGING_RESOURCE_EVENT_HANDLER_HPP */
