// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef MESSAGING_ACTION_TYPE_HPP
#define MESSAGING_ACTION_TYPE_HPP

#include <string>

namespace Messaging {

/**
  The action type (e.g. get/create/update/delete etc.)
*/
class ActionType {
public:
  explicit ActionType(const std::string& type) : type(type) {
  }

  /**
    The action type.
  */
  std::string getType() const { return type; }

  bool operator==(const ActionType& other) const {
    return type == other.type;
  }
  bool operator!=(const ActionType& other) const {
    return !(*this == other);
  }

private:
  std::string  type;
};

}

#endif /* end of include guard: MESSAGING_ACTION_TYPE_HPP */
