#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <Boundary_Tag2 Boundary>
  void
  apply_outlet_boundary(Boundary boundary, auto &grid) {
    forall(grid.begin(boundary), grid.end(boundary), [&](auto cell) { *cell = Cell{}; });
  }

} // end of namespace lbm::D2Q9
