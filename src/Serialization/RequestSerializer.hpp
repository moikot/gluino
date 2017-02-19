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
  TYPE_PTRS(RequestSerializer)
  protected:
    // From Serializer
    virtual Core::Status serialize(
      const Messaging::Request& request,
      ISerializationContext& context) const override;

    virtual Core::Status deserialize(
      std::unique_ptr<Messaging::Request>& request,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_SETTINGS_SERIALIZER_HPP */
