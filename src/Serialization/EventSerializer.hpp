// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_NOTIFICATION_SERIALIZER_HPP
#define SERIALIZATION_NOTIFICATION_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Messaging/Event.hpp"

namespace Serialization {

class EventSerializer : public Serializer<Messaging::Event> {
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Messaging::Event& event,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      std::unique_ptr<Messaging::Event>& event,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_NOTIFICATION_SERIALIZER_HPP */
