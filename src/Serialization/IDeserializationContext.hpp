// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP
#define SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP

#include "Core/StatusResult.hpp"
#include "Core/IList.hpp"

namespace Serialization {

class IDeserializationContext {
  TYPE_PTRS_ABSTRACT(IDeserializationContext)
  public:
    virtual ~IDeserializationContext() = default;

    virtual bool hasKey(const std::string& key) = 0;

    virtual Core::StatusResult::Unique
      getString(const std::string& key, std::string& value) = 0;
    virtual Core::StatusResult::Unique
      getInt(const std::string& key, int& value) = 0;
    virtual Core::StatusResult::Unique
      getBool(const std::string& key, bool& value) = 0;
    virtual Core::StatusResult::Unique
      getEntity(const std::string& key, Core::IEntity::Unique& entity) = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP */
