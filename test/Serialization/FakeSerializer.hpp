// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef FAKE_SERIALIZER
#define FAKE_SERIALIZER

#include "Serialization/ISerializer.hpp"

struct FakeSerializer : public Serialization::ISerializer {
  TYPE_PTRS(FakeSerializer)

  explicit FakeSerializer(ISerializer& serializer) : serializer(serializer) {
  }

  virtual const std::string& getTypeId() const {
    return serializer.getTypeId();
  }

  virtual Core::Status serialize(
    const Core::IEntity& entity,
    Serialization::ISerializationContext& context) const {
      return serializer.serialize(entity, context);
    }

  virtual Core::Status deserialize(
    std::unique_ptr<Core::IEntity>& entity,
    Serialization::IDeserializationContext& context) const {
        return serializer.deserialize(entity, context);
    }

  private:
    ISerializer& serializer;
};

#endif /* end of include guard: FAKE_SERIALIZER */
