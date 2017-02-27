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
    typedef std::tuple<Core::Status, std::unique_ptr<ISerializationContext>> SerializationContextResult;
    typedef std::tuple<Core::Status, std::unique_ptr<IDeserializationContext>> DeserializationContextResult;

    virtual ~IContextFactory() = default;

    virtual SerializationContextResult createSerializationContext(
      const ISerializationService& serializationService) const = 0;

    virtual DeserializationContextResult createDeserializationContext(
      const ISerializationService& serializationService, const std::string& json) const = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_CONTEXT_FACTORY_HPP */
