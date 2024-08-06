#pragma once

//
// ... LBM Benchmarks header files
//
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>
//
// ... Standard header files
//
#include <array>
#include <concepts>

namespace lbm::core {

  template <size_type N>
  class Fixed_Array_Index : public array<size_type, N> {
  public:
    using Base = array<size_type, N>;
    using Base::Base;
    constexpr Fixed_Array_Index(integral auto n1,
                                integral auto n2,
                                convertible_to<size_type> auto... ns)
        : Base{{size_type(n1), size_type(n2), size_type(ns)...}} {}

    friend constexpr bool
    operator<=>(const Fixed_Array_Index &idx1, const Fixed_Array_Index &idx2) = default;

    friend void
    from_json(const json &j, Fixed_Array_Index &idx) {
      static_cast<Base &>(idx) = j["FixedArrayIndex"];
    }

    friend void
    to_json(json &j, const Fixed_Array_Index &idx) {
      j = json::object();
      j["FixedArrayIndex"] = static_cast<const Base &>(idx);
    }

    friend ostream &
    operator<<(ostream &os, const Fixed_Array_Index &idx) {
      return os << json(idx);
    }

    friend istream &
    operator>>(istream &is, Fixed_Array_Index &idx) {
      idx = json::parse(is);
      return is;
    }
  };

  Fixed_Array_Index(size_type, size_type, convertible_to<size_type> auto... ns)
      -> Fixed_Array_Index<sizeof...(ns) + 2>;

} // end of namespace lbm::core

namespace std {

  template <lbm::core::size_type N>
  struct tuple_size<lbm::core::Fixed_Array_Index<N>> : integral_constant<size_t, N> {};

} // end of namespace std
