//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Array2.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::D2Q9::testing {

  TEST_CASE("Node Array") {
    using enum Boundary_ID;
    constexpr size_type nx = 2;
    constexpr size_type ny = 3;
    constexpr size_type nxm1 = nx - 1;
    constexpr size_type nym1 = ny - 1;
    Array2<int> array{Lexical{Shape{nx, ny}}};
    std::fill(std::begin(array), std::end(array), 0);

    SECTION("Left Boundary Iterator") {
      std::fill(array.begin<Left>(), array.end<Left>(), 1);
      for (size_type j = 1; j < nym1; ++j) {
        CHECK(array(0, j) == 1);
      }
    }

    SECTION("Right Boundary Iterator") {
      std::fill(array.begin<Right>(), array.end<Right>(), 1);
      for (size_type j = 1; j < nym1; ++j) {
        CHECK(array(nxm1, j) == 1);
      }
    }

    SECTION("Bottom Boundary Iterator") {
      std::fill(array.begin<Bottom>(), array.end<Bottom>(), 1);
      for (size_type i = 1; i < nxm1; ++i) {
        CHECK(array(i, 0) == 1);
      }
    }

    SECTION("Top Boundary Iterator") {
      std::fill(array.begin<Bottom>(), array.end<Bottom>(), 1);
      for (size_type i = 1; i < nxm1; ++i) {
        CHECK(array(i, nym1) == 1);
      }
    }
  }

} // end of namespace lbm::D2Q9::testing
