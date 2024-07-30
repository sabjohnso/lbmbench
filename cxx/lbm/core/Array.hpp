#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Lexical.hpp>
#include <lbm/core/base_types.hpp>

namespace lbm::core {

  template <class T, size_type N, class Order_Type = Lexical<N>>
  class Array {

  public:
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using Index_Type = Index<2>;
    using Storage = vector<T>;
    using iterator = Storage::iterator;
    using const_iterator = Storage::const_iterator;

    using Order = Order_Type;

    Array() = default;
    Array(Order order, T init = T{})
        : order_{std::move(order)}
        , values_(order_.total_size(), init) {}

    friend bool
    operator<=>(const Array &, const Array &) = default;

    const_reference
    operator()(integral auto i, integral auto j, integral auto... ks) const {
      static_assert(2 + sizeof...(ks) == N);
      return values_[order_.storage_index(Index{i, j, ks...})];
    }

    reference
    operator()(integral auto i, integral auto j, integral auto... ks) {
      static_assert(2 + sizeof...(ks) == N);
      return values_[order_.storage_index(Index_Type{i, j, ks...})];
    }

    const_reference
    operator()(const Index_Type &index) const {
      return values_[order_.storage_index(index)];
    }

    reference
    operator()(const Index_Type &index) {
      return values_[order_.storage_index(index)];
    }

    size_type
    size() const {
      return order_.size();
    }

    size_type
    size(size_type idim) const {
      return order_.size(idim);
    }

    iterator
    begin() {
      return values_.begin();
    }

    iterator
    end() {
      return values_.end();
    }

    const_iterator
    begin() const {
      return values_.begin();
    }

    const_iterator
    end() const {
      return values_.end();
    }

    const_iterator
    cbegin() const {
      return begin();
    }

    const_iterator
    cend() const {
      return end();
    }

    iterator
    rbegin() {
      return values_.rbegin();
    }

    iterator
    rend() {
      return values_.rend();
    }

    const_iterator
    rbegin() const {
      return values_.rbegin();
    }

    const_iterator
    rend() const {
      return values_.rend();
    }

    const_iterator
    crbegin() const {
      return rbegin();
    }

    const_iterator
    crend() const {
      return rend();
    }

    friend void
    to_json(json &j, const Array &array) {
      j = json::object();
      j["Array"] = json::object();
      j["Array"]["order"] = array.order_;
      j["Array"]["values"] = array.values_;
    }

    friend void
    from_json(const json &j, Array &array) {
      array.order_ = j["Array"]["order"];
      array.values_.resize(j["Array"]["values"].size());
      copy(std::begin(j["Array"]["values"]),
           std::end(j["Array"]["values"]),
           std::begin(array.values_));
    }

    friend ostream &
    operator<<(ostream &os, const Array &array) {
      return os << json(array);
    }

    friend istream &
    operator>>(istream &is, Array &array) {
      array = json::parse(is);
      return is;
    }

  private:
    Order order_{};
    vector<T> values_{};
  };

} // namespace lbm::core
