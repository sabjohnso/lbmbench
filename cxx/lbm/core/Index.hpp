#pragma once

//
// ... LGM Bench header files
//
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  template <size_type N_Dims>
  class Index : public array<size_type, N_Dims> {
  public:
    using Base = array<size_type, N_Dims>;

    constexpr Index() = default;

    constexpr Index(integral auto i, integral auto j, integral auto... ks)
        : Base{{size_type(i), size_type(j), size_type(ks)...}} {}

    friend constexpr bool
    operator<=>(const Index &, const Index &) = default;

    friend void
    to_json(json &j, const Index &index) {
      j = json::object();
      j["Index"] = static_cast<const Base &>(index);
    }

    friend void
    from_json(const json &j, Index &index) {
      static_cast<Base &>(index) = j["Index"];
    }

    friend ostream &
    operator<<(ostream &os, const Index &index) {
      return os << json(index);
    }

    friend istream &
    operator>>(istream &is, Index &index) {
      index = json::parse(is);
      return is;
    }
  };

  Index(integral auto i1, integral auto i2, integral auto... is) -> Index<2 + sizeof...(is)>;

} // namespace lbm::core
