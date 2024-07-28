#pragma once

//
// ... Standard header files
//
#include <cstdint>

namespace lbm::core {

  using size_type = std::ptrdiff_t;
  using integer = std::ptrdiff_t;
  using float32_t = float;
  using float64_t = double;

  static_assert(sizeof(float32_t) == 4);
  static_assert(sizeof(float64_t) == 8);

} // end of namespace lbm::core
