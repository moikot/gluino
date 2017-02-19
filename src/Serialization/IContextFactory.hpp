// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_CONTEXT_FACTORY_HPP
#define SERIALIZATION_I_CONTEXT_FACTORY_HPP

#include "ISerializationContext.hpp"
#include "IDeserializationContext.hpp"
#include "ISerializationService.hpp"

#include <memory>

namespace Serialization {

struct IContextFactory {
    virtual ~IContextFactory() = default;

    virtual Core::Status createSerializationContext(
      const ISerializationService& serializationService,
      std::unique_ptr<ISerializationContext>& context) const = 0;

    virtual Core::Status createDeserializationContext(
      const ISerializationService& serializationService, const std::string& json,
      std::unique_ptr<IDeserializationContext>& context) const = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_CONTEXT_FACTORY_HPP */
