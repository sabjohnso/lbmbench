#pragma once

//
// ... import header files
//
#include <lbmbench/details/Fixed_Lexical.hpp>
#include <lbmbench/details/base_types.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <array>

namespace lbm::details {

  template <class T, class Shape>
  class Fixed_Array;

  template <class T, size_type... N>
  class Fixed_Array<T, std::index_sequence<N...>> {
  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;

    static constexpr size_type degree = sizeof...(N);

    using Order = Fixed_Lexical<N...>;
    static constexpr size_type storage_size = (N * ...);
    using Storage = std::array<T, storage_size>;

    constexpr Fixed_Array() = default;
    constexpr explicit Fixed_Array(T init) { std::fill(cbegin(storage_), cend(storage_), init); }

    constexpr const_reference
    operator[](integral auto... i) const {
      static_assert(sizeof...(i) == degree);
      static_assert(Order::degree == degree);
      assert(Order::storage_index(Fixed_Array_Index<degree>(size_type(i)...)) < storage_size);

      return storage_[Order::storage_index(Fixed_Array_Index<degree>(size_type(i)...))];
    }

    reference
    operator[](integral auto... i) {
      static_assert(sizeof...(i) == degree);
      static_assert(Order::degree == degree);
      return storage_[Order::storage_index(Fixed_Array_Index(size_type(i)...))];
    }

    auto
    begin() {
      return storage_.begin();
    }
    auto
    end() {
      return storage_.end();
    }

    auto
    begin() const {
      return storage_.begin();
    }

    auto
    end() const {
      return storage_.end();
    }

    auto
    cbegin() const {
      return begin();
    }

    auto
    cend() const {
      return end();
    }

    static constexpr size_type
    size() {
      return storage_size;
    }

  private:
    Storage storage_{};
  };

} // end of namespace lbm::details
