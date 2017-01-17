// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_SERIALIZATION_CONTEXT_FACTORY_HPP
#define SERIALIZATION_I_SERIALIZATION_CONTEXT_FACTORY_HPP

#include "ISerializationContext.hpp"
#include "ISerializationService.hpp"

#include <memory>

namespace Serialization {

class ISerializationContextFactory {
  public:
    virtual ~ISerializationContextFactory() = default;

    virtual Core::StatusResult::Unique create(
      const ISerializationService& serializationService,
      ISerializationContext::Unique& context) const = 0;

    virtual Core::StatusResult::Unique create(
      const ISerializationService& serializationService, const std::string& json,
      ISerializationContext::Unique& context) const = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_SERIALIZATION_CONTEXT_FACTORY_HPP */
