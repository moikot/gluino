// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_SERIALIZATION_SERVICE_HPP
#define SERIALIZATION_I_SERIALIZATION_SERVICE_HPP

#include "ISerializationContext.hpp"
#include "IDeserializationContext.hpp"

#include <memory>

namespace Serialization {

struct ISerializationService  {
  virtual ~ISerializationService() = default;

  virtual Core::Status serialize(
    const Core::IEntity& object,
    std::string& json) const = 0;

  virtual Core::Status serialize(
    const Core::IEntity& object,
    ISerializationContext& context) const = 0;

  virtual Core::Status deserialize(
    const std::string& json,
    std::unique_ptr<Core::IEntity>& entity) const = 0;

  virtual Core::Status deserialize(
    IDeserializationContext& context,
    std::unique_ptr<Core::IEntity>& entity) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_SERVICE_HPP */
