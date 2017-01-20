// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_SERIALIZER_HPP
#define SERIALIZATION_SERIALIZER_HPP

#include "ISerializer.hpp"

#include "Core/StatusResult.hpp"

namespace Serialization {

template <typename T>
class Serializer : public ISerializer {
  typedef typename T::Unique TUnique;
  public:
    // From ISerializer
    virtual const std::string& getTypeId() const override {
      return T::TypeId();
    }

    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override {

      auto& entityT = static_cast<const T&>(entity);
      auto result = serialize(entityT, context);
      if (!result->isOk()) {
        return Core::StatusResult::makeUnique(Core::StatusCode::InternalServerError,
          "Unable to serialize an instance of type """ + getTypeId() + """.",
          std::move(result));
      }
      return result;
    }

    virtual Core::StatusResult::Unique deserialize(
      Core::IEntity::Unique& entity,
      IDeserializationContext& context) const override {
      TUnique entityT;
      auto result = deserialize(entityT, context);
      if (!result->isOk()) {
        return Core::StatusResult::makeUnique(Core::StatusCode::InternalServerError,
          "Unable to deserialize an instance of type """ + getTypeId() + """.",
          std::move(result));
      }
      entity = std::move(entityT);
      return result;
    }

  protected:
    virtual Core::StatusResult::Unique serialize(
      const T& entity,
      ISerializationContext& context) const = 0;

    virtual Core::StatusResult::Unique deserialize(
      TUnique& entity,
      IDeserializationContext& context) const = 0;
 };

}

#endif /* end of include guard: SERIALIZATION_SERIALIZER_HPP */
