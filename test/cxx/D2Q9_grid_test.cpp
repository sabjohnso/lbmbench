//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Grid.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::D2Q9::testing {

  TEST_CASE("Grid") {

    SECTION("Left") {
      STATIC_CHECK(boundary_offsets<Left>[0] == Offset{1, -1});
      STATIC_CHECK(boundary_offsets<Left>[1] == Offset{1, 0});
      STATIC_CHECK(boundary_offsets<Left>[2] == Offset{1, 1});
    }

    SECTION("Right") {
      STATIC_CHECK(boundary_offsets<Right>[0] == Offset{-1, -1});
      STATIC_CHECK(boundary_offsets<Right>[1] == Offset{-1, 0});
      STATIC_CHECK(boundary_offsets<Right>[2] == Offset{-1, 1});
    }

    SECTION("Bottom") {
      STATIC_CHECK(boundary_offsets<Bottom>[0] == Offset{-1, 1});
      STATIC_CHECK(boundary_offsets<Bottom>[1] == Offset{0, 1});
      STATIC_CHECK(boundary_offsets<Bottom>[2] == Offset{1, 1});
    }

    SECTION("Too") {
      STATIC_CHECK(boundary_offsets<Top>[0] == Offset{-1, -1});
      STATIC_CHECK(boundary_offsets<Top>[1] == Offset{0, -1});
      STATIC_CHECK(boundary_offsets<Top>[2] == Offset{1, -1});
    }
  }
} // end of namespace lbm::D2Q9::testing
