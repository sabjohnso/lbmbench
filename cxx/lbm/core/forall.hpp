#pragma once

namespace lbm::core {

  /**
   * @brief Function passing every iterator in a half-open range to
   * an input function.
   *
   * @details This function is similar to the `std::for_each`, whith
   * notable exception that it passes the iterator to the function,
   * not the dereferenced value.
   */
  template <class Input_Iter, class Unary_Function>
  Unary_Function
  forall(Input_Iter first, Input_Iter last, Unary_Function func) {
    while (first != last) {
      func(first++);
    }
    return func;
  }
} // end of namespace lbm::core
