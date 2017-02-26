// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_EVENT_SERIALIZER_HPP
#define SERIALIZATION_EVENT_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Messaging/Event.hpp"

namespace Serialization {

class EventSerializer : public Serializer<Messaging::Event> {
  protected:
    // From Serializer
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Messaging::Event& event) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Messaging::Event>>
      deserializeImpl(const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_EVENT_SERIALIZER_HPP */
