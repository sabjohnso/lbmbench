#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/base_types.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details::D2Q9 {

  class Lattice final : public JSON_Convertible {
  public:
    Lattice() = default;
    Lattice(double width, double height, double spacing);

    size_type
    nx() const;

    size_type
    ny() const;

    double
    width() const;

    double
    height() const;

    double
    spacing() const;

    friend bool
    operator==(const Lattice &l1, const Lattice &l2);

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    double width_{};
    double height_{};
    double spacing_{};
  };
} // namespace lbm::details::D2Q9
