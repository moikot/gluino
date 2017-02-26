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
  virtual ~IDeserializationContext() = default;

  virtual bool hasKey(const std::string& key) const = 0;

  virtual std::tuple<Core::Status, std::string>
    getString(const std::string& key) const = 0;
  virtual std::tuple<Core::Status, int>
    getInt(const std::string& key) const = 0;
  virtual std::tuple<Core::Status, bool>
    getBool(const std::string& key) const = 0;
  virtual std::tuple<Core::Status, std::unique_ptr<Core::IEntity>>
    getEntity(const std::string& key) const = 0;
};

}

#endif /* end of include guard: SERIALIZATION_I_DESERIALIZATION_CONTEXT_HPP */
