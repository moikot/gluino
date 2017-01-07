// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_ACTION_TYPE_HPP
#define CORE_ACTION_TYPE_HPP

#include <string>

namespace Core {

class ActionType {
public:
  static const ActionType Unknown;
  static const ActionType Get;
  static const ActionType Create;
  static const ActionType Update;
  static const ActionType Delete;

  std::string  getId() const { return id; }

  bool operator==(const ActionType& other) const {
    return id == other.id;
  }

  bool operator!=(const ActionType& other) const {
    return !(*this == other);
  }

  static ActionType getById(std::string id) {
    if (id == Get.getId())
      return ActionType::Get;
    if (id == Update.getId())
      return ActionType::Update;
    if (id == Create.getId())
      return ActionType::Create;
    if (id == Delete.getId())
      return ActionType::Delete;
    return ActionType::Unknown;
  }

private:
  explicit ActionType(const std::string& id) : id(id) {
  }

  std::string  id;
};

}

#endif /* end of include guard: CORE_ACTION_TYPE_HPP */
