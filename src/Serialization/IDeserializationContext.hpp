// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP
#define SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP

#include "Core/Status.hpp"
#include "Core/IList.hpp"

namespace Serialization {

struct IDeserializationContext {
  TYPE_PTRS_ABSTRACT(IDeserializationContext)
  virtual ~IDeserializationContext() = default;

  virtual bool hasKey(const std::string& key) = 0;

  virtual Core::Status
    getString(const std::string& key, std::string& value) = 0;
  virtual Core::Status
    getInt(const std::string& key, int& value) = 0;
  virtual Core::Status
    getBool(const std::string& key, bool& value) = 0;
  virtual Core::Status
    getEntity(const std::string& key, std::unique_ptr<Core::IEntity>& entity) = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP */
