// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef JSON_RESPONSE_SERIALIZER_HPP
#define JSON_RESPONSE_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/Response.hpp"

namespace Json {

class ResponseSerializer : public Serializer<Core::Response> {
  TYPE_PTRS(ResponseSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::Response& response,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Core::Response::Unique& response,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_HPP */
