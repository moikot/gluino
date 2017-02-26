// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_STATUS_SERIALIZER_HPP
#define SERIALIZATION_STATUS_SERIALIZER_HPP

#include "Serializer.hpp"
#include "Core/Status.hpp"

namespace Serialization {

class StatusSerializer : public Serializer<Core::Status> {
  protected:
    // From Serializer
    virtual Core::Status
      serializeImpl(ISerializationContext& context, const Core::Status& status) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Core::Status>>
      deserializeImpl(const IDeserializationContext& context) const override;
};

}

#endif /* end of include guard: SERIALIZATION_STATUS_SERIALIZER_HPP */
