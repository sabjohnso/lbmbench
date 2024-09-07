#pragma once

//
// ... LBM Bench header files header files
//
#include <lbm/D2Q9/Grid.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <Boundary_Tag2 Boundary>
  void
  apply_inlet_boundary(auto &grid, auto /* speed */, auto /*density*/) {
    using Value_Type = typename Grid::Value_Type;
    using Velocity_Type = typename Cell<Value_Type>::Velocity;
    forall(grid.begin(boundary), grid.end(boundary), [&](auto cell) {
      cell->init(density, velocity);
    });
  }

} // end of namespace lbm::D2Q9
