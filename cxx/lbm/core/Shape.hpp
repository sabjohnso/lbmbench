#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  template <size_type N>
  class Shape
      : public JSON_Convertible
      , array<size_type, N> {
  public:
    using Base = array<size_type, N>;
    constexpr Shape() = default;
    constexpr Shape(integral auto n1, integral auto n2, integral auto... ns)
        : Base{{size_type(n1), size_type(n2), size_type(ns)...}} {
      static_assert(2 + sizeof...(ns) == N);
    }

    using Base::operator[];
    using Base::at;

    static constexpr size_type
    degree() {
      return N;
    }

    size_type
    total_size() const {
      return reduce(Base::begin(), Base::end(), size_type(1), multiplies{});
    }

  private:
    json
    get_json() const override {
      json j = json::object();
      j["Shape"] = json::array();
      copy(Base::cbegin(), Base::cend(), back_inserter(j["Shape"]));
      return j;
    }

    void
    set_json(json const &j) override {
      copy(std::cbegin(j["Shape"]), std::cend(j["Shape"]), Base::begin());
    }
  };

  Shape(integral auto n1, integral auto n2, integral auto... ns) -> Shape<2 + sizeof...(ns)>;

} // end of namespace lbm::core
