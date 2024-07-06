#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  enum class Boundary {
    Lower = -1,
    NA = 0,
    Upper = 1,
  };

  class Boundary_ID
      : public vector<Boundary>
      , public JSON_Convertible {
  public:
    using Base = vector<Boundary>;

    constexpr Boundary_ID() = default;
    constexpr Boundary_ID(auto i, auto j, auto... ks)
        : Base{Boundary(i), Boundary(j), Boundary(ks)...} {}

  private:
    json
    get_json() const override {
      json j = json::array();

      transform(std::begin(*this), std::end(*this), back_inserter(j), [](const Boundary &x) {
        return int(x);
      });
      return j;
    }

    void
    set_json(const json &j) override {
      this->clear();
      transform(std::begin(j), std::end(j), back_inserter(*this), [](const auto &x) {
        return Boundary(x);
      });
    }
  };
} // end of namespace lbm::core
