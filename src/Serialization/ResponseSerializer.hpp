// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_RESPONSE_SERIALIZER_HPP
#define SERIALIZATION_RESPONSE_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Messaging/Response.hpp"

namespace Serialization {

class ResponseSerializer : public Serializer<Messaging::Response> {
  protected:
    // From Serializer
    virtual Core::Status serializeImpl(
      ISerializationContext& context,
      const Messaging::Response& response) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Messaging::Response>>
    deserializeImpl(const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_SETTINGS_SERIALIZER_HPP */
