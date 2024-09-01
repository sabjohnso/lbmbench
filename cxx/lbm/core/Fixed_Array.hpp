#pragma once

//
// ... import header files
//
#include <lbm/core/Fixed_Lexical.hpp>
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/base_types.hpp>

//
// ... Standard header files
//
#include <algorithm>
#include <array>

namespace lbm::core {

  template <class T, class Order>
  class Fixed_MD_Array;

  template <class T, size_type... N>
  class Fixed_MD_Array<T, Fixed_Lexical<N...>> : public JSON_Convertible {
  public:
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;

    static constexpr size_type degree = sizeof...(N);

    using Order = Fixed_Lexical<N...>;
    static constexpr size_type storage_size = (N * ...);
    using Storage = std::array<T, storage_size>;

    constexpr Fixed_MD_Array() = default;
    constexpr explicit Fixed_MD_Array(T init) { std::fill(cbegin(storage_), cend(storage_), init); }

    constexpr Fixed_MD_Array(T x1, T x2, same_as<T> auto... xs)
        : storage_{{x1, x2, xs...}} {
      static_assert(2 + sizeof...(xs) == size());
    }

    friend constexpr Fixed_MD_Array
    operator+(const Fixed_MD_Array &xs, const Fixed_MD_Array &ys) {
      return [&]<std::size_t... i>(index_sequence<i...>) {
        return Fixed_MD_Array{xs[i] + ys[i]...};
      }
      (make_index_sequence<storage_size>());
    }

    friend constexpr Fixed_MD_Array
    operator-(const Fixed_MD_Array &xs, const Fixed_MD_Array &ys) {
      return [&]<std::size_t... i>(index_sequence<i...>) {
        return Fixed_MD_Array{xs[i] - ys[i]...};
      }
      (make_index_sequence<storage_size>());
    }

    Fixed_MD_Array &
    fill(Value_Type x) {
      using std::fill;
      fill(std::begin(storage_), std::end(storage_), x);
      return *this;
    }

    constexpr Const_Reference
    at(size_type i) const {
      return storage_.at(i);
    }

    Reference
    at(size_type i) {
      return storage_.at(i);
    }

    constexpr Const_Reference
    operator[](size_type i) const {
      return storage_[i];
    }

    constexpr Reference
    operator[](size_type i) {
      return storage_[i];
    }

    constexpr Const_Reference
    operator()(size_type i, size_type j, integral auto... ks) const {
      static_assert(2 + sizeof...(ks) == degree);
      static_assert(Order::degree == degree);
      assert(Order::storage_index(Fixed_MD_Array_Index<degree>(i, j, size_type(ks)...)) <
             storage_size);
      return storage_[Order::storage_index(Fixed_MD_Array_Index<degree>(i, j, size_type(ks)...))];
    }

    Reference
    operator()(size_type i, size_type j, integral auto... ks) {
      static_assert(2 + sizeof...(ks) == degree);
      static_assert(Order::degree == degree);
      return storage_[Order::storage_index(Fixed_MD_Array_Index(i, j, size_type(ks)...))];
    }

    constexpr Const_Reference
    at(size_type i, size_type j, integral auto... ks) const {
      static_assert(2 + sizeof...(ks) == degree);
      static_assert(Order::degree == degree);
      assert(Order::storage_index(Fixed_MD_Array_Index<degree>(i, j, size_type(ks)...)) <
             storage_size);
      return storage_[Order::storage_index(Fixed_MD_Array_Index<degree>(i, j, size_type(ks)...))];
    }

    Reference
    at(size_type i, size_type j, integral auto... ks) {
      static_assert(2 + sizeof...(ks) == degree);
      static_assert(Order::degree == degree);
      return storage_[Order::storage_index(Fixed_MD_Array_Index(i, j, size_type(ks)...))];
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

    friend bool
    operator==(const Fixed_MD_Array &x, const Fixed_MD_Array &y) {
      return transform_reduce(
          std::begin(x), std::end(x), std::begin(y), true, logical_and{}, equal_to{});
    }

    friend bool
    operator!=(const Fixed_MD_Array &x, const Fixed_MD_Array &y) {
      return !(x == y);
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["FixedArray"] = json::object();
      j["FixedArray"]["order"] = Order{};
      j["FixedArray"]["values"] = storage_;
      return j;
    }

    void
    set_json(const json &j) override {
      assert(j.contains("/FixedArray/order"_json_pointer));
      assert(j.contains("/FixedArray/values"_json_pointer));
      const auto &values = j["FixedArray"]["values"];
      copy(std::begin(values), std::end(values), std::begin(storage_));
    }

    Storage storage_{};
  };

} // end of namespace lbm::core
