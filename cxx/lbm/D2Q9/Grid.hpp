#pragma once

//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Cell.hpp>
#include <lbm/D2Q9/import.hpp>

namespace lbm::D2Q9 {
  using Offset = array<size_type, 2>;

  constexpr inline array<Offset, 9> classes{
      // clang-format off
    {{-1, -1}, {0, -1}, {1, -1},
     {-1,  0}, {0,  0}, {1,  0},
     {-1,  1}, {0,  1}, {1,  1}}
      // clang-format on
  };

  constexpr array<Offset, 8> neighbor_offsets{
      // clang-format off
      {{-1, -1}, {0, -1}, {1, -1},
       {-1,  0},          {1,  0},
       {-1,  1}, {0,  1}, {1,  1}}
      // clang-format on
  };

  using Internal_Offsets = array<Offset, 3>;

  template <Boundary_Tag2 Boundary>
  constexpr Internal_Offsets boundary_offsets{};

  template <>
  constexpr inline Internal_Offsets boundary_offsets<Left>{
      // clang-format off
    {{1, -1},
     {1,  0},
     {1,  1}}
      // clang-format on
  };

  template <>
  constexpr inline Internal_Offsets boundary_offsets<Right>{
      // clang-format off
      {{-1, -1},
       {-1,  0},
       {-1,  1}}
      // clang-format on
  };

  template <>
  constexpr inline Internal_Offsets boundary_offsets<Bottom>{
      // clang-format off
      {{-1, 1}, {0,  1}, {1,  1}}
      // clang-format on
  };

  template <>
  constexpr inline Internal_Offsets boundary_offsets<Top>{
      // clang-format off
      {{-1, -1}, {0, -1}, {1, -1}}
      // clang-format on
  };

  template <class T>
  class Grid : public Array2<Cell<T>> {
  public:
    using Base = Array2<Cell<T>>;
    using Base::Base;
  };

} // end of namespace lbm::D2Q9
