// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Moikot
// https://github.com/anisimovsergey/moikot

#ifndef JSON_STATUS_SERIALIZER_HPP
#define JSON_STATUS_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/ActionResult.hpp"

namespace Json {

class StatusResultSerializer : public Serializer<Core::StatusResult> {
  TYPE_PTRS(StatusResultSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::StatusResult& statusResult,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Core::StatusResult::Unique& statusResult,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: JSON_STATUS_SERIALIZER_HPP */
