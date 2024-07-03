#pragma once

namespace lbm::details {

  template <class T, size_type N>
  class Vector : public array<T, N>, public JSON_Convertible {
  public:
    using Value_Type = T;
    using Reference = T &;
    using Const_Reference = const T &;
    using Base = array<T, N>;

    constexpr Vector() = default;

    constexpr Vector(T x1, T x2, same_as<T> auto... xs) : Base{{x1, x2, xs...}} {}

    constexpr friend Vector
    operator+(const Vector &u, const Vector &v) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Vector{u[Index] + v[Index]...};
      }(make_index_sequence<N>());
    }

    constexpr friend Vector
    operator-(const Vector &u, const Vector &v) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Vector{u[Index] - v[Index]...};
      }(make_index_sequence<N>());
    }

    constexpr friend Vector
    operator*(const Vector &u, Value_Type s) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Vector{u[Index] * s...};
      }(make_index_sequence<N>());
    }

    constexpr friend Vector
    operator*(Value_Type s, const Vector &v) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Vector{s * v[Index]...};
      }(make_index_sequence<N>());
    }

    constexpr friend Vector
    operator/(const Vector &u, Value_Type s) {
      return [&]<std::size_t... Index>(index_sequence<Index...>) {
        return Vector{u[Index] / s...};
      }(make_index_sequence<N>());
    }

    constexpr friend Value_Type
    dot(const Vector &u, const Vector &v) {
      return transform_reduce(std::begin(u), std::end(u), std::begin(v), T(0));
    }

    friend constexpr bool
    operator==(const Vector &u, const Vector &v) {
      return transform_reduce(
          std::cbegin(u), std::cend(u), std::begin(v), true, logical_and{}, equal_to{});
    }

    friend constexpr bool
    operator!=(const Vector &u, const Vector &v) {
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
  Vector(Ts &&...) -> Vector<common_type_t<Ts...>, sizeof...(Ts)>;

} // end of namespace lbm::details
