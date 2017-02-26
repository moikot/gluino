// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_REQUEST_SERIALIZER_HPP
#define SERIALIZATION_REQUEST_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Messaging/Request.hpp"

namespace Serialization {

class RequestSerializer : public Serializer<Messaging::Request> {
  protected:
    // From Serializer
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Messaging::Request& request) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Messaging::Request>>
      deserializeImpl(const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_SETTINGS_SERIALIZER_HPP */
