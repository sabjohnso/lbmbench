//
// ... LBM Bench header files
//
#include <lbm/utility.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {
  TEST_CASE("2 Dimensional Input") {
    Input
        input{}; //{Lattice{}, Initial_Conditions{}, Boundary_Conditions{}, Obstacles{}, viscosity};
    CHECK(input == input);

    SECTION("Conversion to and from JSON") {}
  }

  TEST_CASE("3 Dimensional Input") {}
} // end of namespace lbm::core::testing
