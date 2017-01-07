// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef JSON_SERIALIZATION_SERVICE_HPP
#define JSON_SERIALIZATION_SERVICE_HPP

#include "ISerializer.hpp"
#include "ISerializationService.hpp"
#include "ISerializationContextFactory.hpp"

#include <memory>
#include <list>

namespace Json {

class SerializationService : public ISerializationService {
  TYPE_PTRS(SerializationService)
  public:
    explicit SerializationService(
      std::shared_ptr<const ISerializationContextFactory> contextFactory);

    // From ISerializationService
    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& entity,
      std::string& json) const override;

    virtual Core::StatusResult::Unique serialize(
      const Core::IEntity& entity,
      ISerializationContext& context) const override;

    virtual Core::StatusResult::Unique deserialize(
      const std::string& json,
      Core::IEntity::Unique& entity) const override;

    virtual Core::StatusResult::Unique deserialize(
      ISerializationContext& context,
      Core::IEntity::Unique& entity) const override;

    // Methods
    void addSerializer(
      std::shared_ptr<const ISerializer> serializer);

  private:
    std::shared_ptr<const ISerializationContextFactory>   contextFactory;
    std::list<std::shared_ptr<const ISerializer>>         serializers;

    std::shared_ptr<const ISerializer> getSerialzier(std::string typeId) const;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_HPP */
