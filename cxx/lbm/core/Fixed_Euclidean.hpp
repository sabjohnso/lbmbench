#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  template <class T, size_type N>
  class Fixed_Euclidean
      : public array<T, N>
      , public JSON_Convertible {
  public:
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;
    using Base = array<T, N>;

    constexpr Fixed_Euclidean() = default;

    constexpr Fixed_Euclidean(T x1, T x2, same_as<T> auto... xs)
        : Base{{x1, x2, xs...}} {}

    constexpr friend Fixed_Euclidean
    operator+(const Fixed_Euclidean &u, const Fixed_Euclidean &v) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Fixed_Euclidean{u[Index] + v[Index]...};
      }
      (make_index_sequence<N>());
    }

    constexpr friend Fixed_Euclidean
    operator-(const Fixed_Euclidean &u, const Fixed_Euclidean &v) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Fixed_Euclidean{u[Index] - v[Index]...};
      }
      (make_index_sequence<N>());
    }

    constexpr friend Fixed_Euclidean
    operator*(const Fixed_Euclidean &u, Value_Type s) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Fixed_Euclidean{u[Index] * s...};
      }
      (make_index_sequence<N>());
    }

    constexpr friend Fixed_Euclidean
    operator*(Value_Type s, const Fixed_Euclidean &v) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Fixed_Euclidean{s * v[Index]...};
      }
      (make_index_sequence<N>());
    }

    constexpr friend Fixed_Euclidean
    operator/(const Fixed_Euclidean &u, Value_Type s) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Fixed_Euclidean{u[Index] / s...};
      }
      (make_index_sequence<N>());
    }

    constexpr friend Value_Type
    dot(const Fixed_Euclidean &u, const Fixed_Euclidean &v) {
      return transform_reduce(std::begin(u), std::end(u), std::begin(v), T(0));
    }

    friend constexpr bool
    operator==(const Fixed_Euclidean &u, const Fixed_Euclidean &v) {
      return transform_reduce(
          std::cbegin(u), std::cend(u), std::begin(v), true, logical_and{}, equal_to{});
    }

    friend constexpr bool
    operator!=(const Fixed_Euclidean &u, const Fixed_Euclidean &v) {
      return !(u == v);
    }

  private:
    json
    get_json() const override {
      json j = static_cast<const Base &>(*this);
      return j;
    }

    void
    set_json(const json &j) override {
      static_cast<Base &>(*this) = j;
    }
  };

  template <class... Ts>
  Fixed_Euclidean(Ts &&...) -> Fixed_Euclidean<common_type_t<Ts...>, sizeof...(Ts)>;

} // end of namespace lbm::core
