#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  template <size_type N>
  class Shape : public array<size_type, N> {
  public:
    using Base = array<size_type, N>;
    constexpr Shape() = default;
    constexpr Shape(integral auto n1, integral auto n2, integral auto... ns)
        : Base{{size_type(n1), size_type(n2), size_type(ns)...}} {
      static_assert(2 + sizeof...(ns) == N);
    }

    friend void
    to_json(json &j, const Shape &shape) {
      j = json::object();
      j["Shape"] = static_cast<const Base &>(shape);
    }

    friend void
    from_json(const json &j, Shape &shape) {
      static_cast<Base &>(shape) = j["Shape"];
    }

    friend ostream &
    operator<<(ostream &os, const Shape &shape) {
      return os << json(shape);
    }

    friend istream &
    operator>>(istream &is, Shape &shape) {
      shape = json::parse(is);
      return is;
    }

    static constexpr size_type
    degree() {
      return N;
    }

    size_type
    total_size() const {
      return reduce(Base::begin(), Base::end(), size_type(1), multiplies{});
    }
  };

  Shape(integral auto n1, integral auto n2, integral auto... ns) -> Shape<2 + sizeof...(ns)>;

} // end of namespace lbm::core
