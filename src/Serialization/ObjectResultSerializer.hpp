// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_OBJECT_RESULT_SERIALIZER_HPP
#define SERIALIZATION_OBJECT_RESULT_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/ObjectResult.hpp"
#include "Core/ObjectResult.hpp"

namespace Serialization {

class ObjectResultSerializer : public Serializer<Core::ObjectResult> {
  TYPE_PTRS(ObjectResultSerializer)
  protected:
    // From Serializer
    virtual Core::StatusResult::Unique serialize(
      const Core::ObjectResult& objectResult,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      Core::ObjectResult::Unique& objectResult,
      ISerializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_OBJECT_RESULT_SERIALIZER_HPP */
