// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_REQUEST_SERIALIZER_HPP
#define JSON_REQUEST_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/Request.hpp"

namespace Json {

class RequestSerializer : public Serializer<Core::Request> {
  TYPE_PTRS(RequestSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::Request& request,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Core::Request::Unique& request,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_SETTINGS_SERIALIZER_HPP */
