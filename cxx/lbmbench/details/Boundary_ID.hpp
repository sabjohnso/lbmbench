#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  enum class Boundary {
    Lower = -1,
    NA = 0,
    Upper = 1,
  };

  template <size_type N>
  class Boundary_ID : public array<Boundary, N> {
  public:
    using Base = array<Boundary, N>;

    constexpr Boundary_ID() = default;
    constexpr Boundary_ID(auto i, auto j, auto... ks)
        : Base{{Boundary(i), Boundary(j), Boundary(ks)...}} {}

    friend void
    to_json(json &j, const Boundary_ID id) {
      j = json::object();
      j["boundary"] = json::array();
      transform(std::begin(id), std::end(id), back_inserter(j["boundary"]), [](const Boundary &x) {
        return int(x);
      });
    }

    friend void
    from_json(const json &j, Boundary_ID &id) {
      transform(std::begin(j["boundary"]),
                std::end(j["boundary"]),
                std::begin(id),
                [](const auto &x) { return Boundary(x); });
    }

    friend ostream &
    operator<<(ostream &os, const Boundary_ID &id) {
      return os << json(id);
    }

    friend istream &
    operator>>(istream &is, Boundary_ID &id) {
      id = json::parse(is);
      return is;
    }
  };

  Boundary_ID(auto i, auto j, auto... ks) -> Boundary_ID<2 + sizeof...(ks)>;

} // end of namespace lbm::details
