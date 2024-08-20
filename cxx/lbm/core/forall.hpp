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

  /**
   * @brief Function passing every iterator from two half-open ranges to
   * an input binary function, which is return.
   *
   * @details This function is similar to the `std::for_each`, whith
   * notable exception that it passes the iterator to the function,
   * not the dereferenced value, and accepts to ranges.
   */
  template <class Input_Iter1, class Input_Iter2, class Binary_Function>
  Unary_Function
  forall(Input_Iter first1, Input_Iter last1, Input_Iter first2, Binary_Function func) {
    while (first1 != last1) {
      func(first1++, first2++);
    }
    return func;
  }

} // end of namespace lbm::core
