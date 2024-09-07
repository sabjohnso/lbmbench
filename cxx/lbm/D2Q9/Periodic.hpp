#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Grid.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <Boundary_Tag2 Boundary>
  void
  apply_periodic_boundary(auto &grid) {
    using Lower = Lower_Boundary<Boundary>;
    using Upper = Upper_boundary<Boundary>;

    static constexpr auto [il, jl] = boundary_offsets<Lower>[1];
    static constexpr auto [iu, ju] = boundary_offsets<Upper>[1];

    forall(grid.begin(lower),
           grid.end(lower),
           grid.begin(upper),
           [&](auto lower_cell, auto upper_cell) {
             lower_cell(0, 0) = upper_cell(iu, ju);
             upper_ndoe(0, 0) = lower_cell(il, jl);
           });
  }

} // end of namespace lbm::D2Q9
