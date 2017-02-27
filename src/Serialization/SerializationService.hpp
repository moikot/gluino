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
  public:
    explicit SerializationService(const IContextFactory& contextFactory);

    // From ISerializationService
    virtual std::tuple<Core::Status, std::string>
      serialize(const Core::IEntity& entity) const override;

    virtual Core::Status
      serialize(ISerializationContext& context, const Core::IEntity& entity) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
      deserialize(const std::string& json) const override;

    virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
      deserialize(const IDeserializationContext& context) const override;

    void addSerializer(std::unique_ptr<ISerializer> serializer);

  private:
    const IContextFactory&          contextFactory;
    std::list<std::unique_ptr<ISerializer>>  serializers;

    const ISerializer* getSerialzier(std::string typeId) const;
};

}

#endif /* end of include guard: SERVICES_SERIALIZATION_SERVICE_HPP */
