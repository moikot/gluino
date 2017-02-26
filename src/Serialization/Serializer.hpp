// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_SERIALIZER_HPP
#define SERIALIZATION_SERIALIZER_HPP

#include "ISerializer.hpp"

#include "Core/Status.hpp"

namespace Serialization {

template <typename T>
class Serializer : public ISerializer {
  public:
    // From ISerializer
    virtual const std::string& getTypeId() const override {
      return T::TypeId();
    }

    virtual Core::Status serialize(ISerializationContext& context,
      const Core::IEntity& entity) const override {

      auto result = serializeImpl(context, static_cast<const T&>(entity));
      if (!result.isOk()) {
        return Core::Status(Core::StatusCode::InternalServerError,
          "Unable to serialize an instance of type """ + getTypeId() + """.", result);
      }
      return result;
    }

    virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
      deserialize(const IDeserializationContext& context) const override {

      Core::Status result;
      std::unique_ptr<T> entity;
      std::tie(result, entity) = deserializeImpl(context);
      if (!result.isOk()) {
        return Core::Status(Core::StatusCode::InternalServerError,
          "Unable to deserialize an instance of type """ + getTypeId() + """.", result);
      }
      return std::make_tuple(result, std::move(entity));
    }

  protected:
    virtual Core::Status serializeImpl(ISerializationContext& context,
      const T& entity) const = 0;

    virtual std::tuple<Core::Status, std::unique_ptr<T>>
      deserializeImpl(const IDeserializationContext& context) const = 0;
 };

}

#endif /* end of include guard: SERIALIZATION_SERIALIZER_HPP */
