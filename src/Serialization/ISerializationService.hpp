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

  virtual std::tuple<Core::Status, std::string>
    serialize(const Core::IEntity& object) const = 0;

  virtual Core::Status
    serialize(ISerializationContext& context, const Core::IEntity& object) const = 0;

  virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
    deserialize(const std::string& json) const = 0;

  virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
    deserialize(const IDeserializationContext& context) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_SERVICE_HPP */
