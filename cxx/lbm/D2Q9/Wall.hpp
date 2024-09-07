#pragma once

//
// ... LBM Bench  header files
//
#include <lbm/D2Q9/Grid.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <Boundary_Tag2 Boundary>
  void
  apply_noslip_boundary(auto &grid) {
    static constexpr auto internal_offsets = boundary_offsets<Boundary>;
    static constexpr Boundary boundary{};
    forall(grid.begin(boundary), grid.end(boundary), [&](auto cell) {
      for_each(std::begin(internal_offsets), std::end(internal_offsets), [&](const auto offset) {
        const auto [i, j] = offset;
        cell(0, 0)(i, j) = cell(i, j)(-i, -j);
      });
    });
  }

} // namespace lbm::D2Q9
