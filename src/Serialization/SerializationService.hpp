// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_SERIALIZATION_SERVICE_HPP
#define SERIALIZATION_SERIALIZATION_SERVICE_HPP

#include "ISerializer.hpp"
#include "ISerializationService.hpp"
#include "IContextFactory.hpp"

#include <memory>
#include <list>

namespace Serialization {

class SerializationService : public ISerializationService {
  TYPE_PTRS(SerializationService)
  public:
    explicit SerializationService(
      std::shared_ptr<const IContextFactory> contextFactory);

    // From ISerializationService
    virtual Core::Status::Unique serialize(
      const Core::IEntity& entity,
      std::string& json) const override;

    virtual Core::Status::Unique serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override;

    virtual Core::Status::Unique deserialize(
      const std::string& json,
      Core::IEntity::Unique& entity) const override;

    virtual Core::Status::Unique deserialize(
      IDeserializationContext& context,
      Core::IEntity::Unique& entity) const override;

    void addSerializer(ISerializer::Shared serializer);

  private:
    std::shared_ptr<const IContextFactory>   contextFactory;
    std::list<std::shared_ptr<const ISerializer>>         serializers;

    std::shared_ptr<const ISerializer> getSerialzier(std::string typeId) const;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_HPP */
