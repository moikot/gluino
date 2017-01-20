// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_STATUS_SERIALIZER_HPP
#define SERIALIZATION_STATUS_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/StatusResult.hpp"

namespace Serialization {

class StatusResultSerializer : public Serializer<Core::StatusResult> {
  TYPE_PTRS(StatusResultSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::StatusResult& statusResult,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Core::StatusResult::Unique& statusResult,
      IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_STATUS_SERIALIZER_HPP */
