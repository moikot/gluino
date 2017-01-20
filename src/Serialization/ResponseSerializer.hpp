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
  TYPE_PTRS(ResponseSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Messaging::Response& response,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Messaging::Response::Unique& response,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_SETTINGS_SERIALIZER_HPP */
