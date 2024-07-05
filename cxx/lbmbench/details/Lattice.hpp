#pragma once

//
// ... LBM Bench header files
//
#include <lbmbench/details/Bounding_Box.hpp>
#include <lbmbench/details/JSON_Convertible.hpp>
#include <lbmbench/details/base_types.hpp>
#include <lbmbench/details/import.hpp>

namespace lbm::details {

  class Lattice final : public JSON_Convertible {
  public:
    Lattice() = default;
    Lattice(Bounding_Box bounding_box, double lattice_spacing);

    size_type
    size() const;

    size_type
    size(size_type idim) const;

    double
    extent(size_type idim) const;

    double
    lattice_spacing() const;

    friend bool
    operator==(const Lattice &l1, const Lattice &l2);

  private:
    json
    get_json() const override;

    void
    set_json(const json &j) override;

    Bounding_Box bounding_box_{};
    double lattice_spacing_{};
  };
} // namespace lbm::details
