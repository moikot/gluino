// Copyright Sergey Anisimov 2016-2017
// MIT License
//
// Gluino
// https://github.com/anisimovsergey/gluino

#ifndef CORE_TYPE_PTRS_HPP
#define CORE_TYPE_PTRS_HPP

#include <memory>

namespace Core {

template<typename T>
using base_type = typename std::remove_cv<typename std::remove_reference<T>::type>::type;

template <typename T>
struct function_traits
  : public function_traits<decltype(&T::operator())>
{
  ~function_traits() = delete;
};

template <typename ClassType, typename ReturnType, typename... Args>
struct function_traits<ReturnType(ClassType::*)(Args...) const>
{
  static constexpr size_t value = sizeof...(Args);

  template <size_t i>
  struct arg
  {
    typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
  };
};

}

#endif /* end of include guard: CORE_TYPE_PTRS_HPP */
