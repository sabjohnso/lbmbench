#pragma once

namespace lbm::core {

  struct Nil {
  } constexpr nil{};

  constexpr auto
  sqr(auto x) {
    return x * x;
  };

  constexpr auto
  unroll_horizontally(auto &&){};

} // end of namespace lbm::core
