// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef JSON_I_SERIALIZATION_SERVICE_HPP
#define JSON_I_SERIALIZATION_SERVICE_HPP

#include "ISerializationContext.hpp"

#include "Core/IEntity.hpp"

#include <memory>

namespace Json {

class ISerializationService {
  TYPE_PTRS_ABSTRACT(ISerializationService)
  public:
    virtual ~ISerializationService();

    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& object,
      std::string& json) const = 0;

    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& object,
      ISerializationContext& context) const = 0;

    virtual Core::StatusResult::Unique deserialize(
      const std::string& json,
      Core::IEntity::Unique& entity) const = 0;

    virtual Core::StatusResult::Unique deserialize(
      ISerializationContext& context,
      Core::IEntity::Unique& entity) const = 0;
};

}

#endif /* end of include guard: SERVICES_I_SERIALIZATION_SERVICE_HPP */
