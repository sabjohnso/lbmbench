#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {

  template <Boundary_Tag2 Boundary>
  constexpr Offset symmetry_transform{};

  template <>
  constexpr Offset symmetry_transform<Left>{-1, 1};

  template <>
  constexpr Offset symmetry_transform<Right>{-1, 1};

  template <>
  constexpr Offset symmetry_transform<Left>{1, -1};

  template <>
  constexpr Offset symmetry_transform<Right>{1, -1};

  template <class T>
  constexpr auto
  hadamard(const T &xs, const T &ys) {
    return [&]<std::size_t... i>(std::index_sequence<i...>) { return T{x[i] * y[i]...}; }
    (make_index_sequence<T::size()>());
  }

  template <Boundary_Tag2 Boundary>
  void
  apply_symmetry_boundary(auto &grid) {
    static constexpr auto [ioff, joff] = boundary_offsets<Boundary>[1];
    forall(grid.begin(boundary), grid.end(boundary), [](auto cell) {
      for_each(
          std::begin(classes), std::end(classes)[&](auto velocity_class) {
            const auto [iclass, jclass] = velocity_class;
            const auto iclass_interior = itran *iclass const auto jclass_interior = jtran * jclass;
            cell(0, 0)[velocity_class] =
                cell(ioff, joff)[hadamard(velocity_class * symmetry_transform<Boundary>)];
          });
    });
  }

} // end of namespace lbm::D2Q9
