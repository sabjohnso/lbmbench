#pragma once

//
// ... LBM Bench header files
//
#include <lbm/core/Bounding_Box.hpp>
#include <lbm/core/JSON_Convertible.hpp>
#include <lbm/core/base_types.hpp>
#include <lbm/core/import.hpp>

namespace lbm::core {

  class Lattice final : public JSON_Convertible {
  public:
    Lattice() = default;
    Lattice(Bounding_Box bounding_box, double lattice_spacing);

    size_type
    ndims() const;

    size_type
    nnodes() const;

    size_type
    nnodes(size_type idim) const;

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
} // namespace lbm::core
