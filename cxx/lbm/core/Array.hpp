#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/Lexical.hpp>
#include <lbm/core/base_types.hpp>

namespace lbm::core {

  template <class T, size_type N, class Order_Type = Lexical<N>>
  class MD_Array : public vector<T> {
  public:
    using Base = vector<T>;
    using value_type = T;
    using reference = T &;
    using const_reference = const T &;
    using Index_Type = Index<2>;
    using Storage = vector<T>;
    using iterator = typename Storage::iterator;
    using const_iterator = typename Storage::const_iterator;

    using Order = Order_Type;

    MD_Array() = default;
    MD_Array(Order order, T init = T{})
        : Base(order.total_size(), init)
        , order_{std::move(order)} {}

    friend void
    from_json(const json &j, MD_Array &array) {
      assert(j.contains("order"));
      array.order_ = j["order"];

      assert(j.contains("values"));
      array.clear();
      array.reserve(std::size(j["values"]));
      copy(std::cbegin(j["values"]), std::cend(j["values"]), back_inserter(array));
    }

    friend void
    to_json(json &j, const MD_Array &array) {
      j = json::object();
      j["order"] = array.order_;
      j["values"] = json::array();
      copy(std::cbegin(array), std::cend(array), back_inserter(j["values"]));
    }

    friend ostream &
    operator<<(ostream &os, const MD_Array &array) {
      return os << json(array);
    }

    friend istream &
    operator>>(istream &is, MD_Array &array) {
      array = json::parse(is);
      return is;
    }

    friend bool
    operator<=>(const MD_Array &, const MD_Array &) = default;

    const_reference
    operator()(integral auto i, integral auto j, integral auto... ks) const {
      static_assert(2 + sizeof...(ks) == N);
      return Base::operator[](order_.storage_index(Index{i, j, ks...}));
    }

    reference
    operator()(integral auto i, integral auto j, integral auto... ks) {
      static_assert(2 + sizeof...(ks) == N);
      return Base::operator[](order_.storage_index(Index_Type{i, j, ks...}));
    }

    const_reference
    operator()(const Index_Type &index) const {
      return Base::operator[](order_.storage_index(index));
    }

    reference
    operator()(const Index_Type &index) {
      return Base::operator[](order_.storage_index(index));
    }

    size_type
    size() const {
      return order_.size();
    }

    size_type
    size(size_type idim) const {
      return order_.size(idim);
    }

  private:
    Order order_{};
  };

} // namespace lbm::core
