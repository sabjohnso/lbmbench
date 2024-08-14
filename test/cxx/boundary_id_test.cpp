//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_ID.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::core::testing {

  TEST_CASE("D2 Boundary ID") {
    Boundary_ID boundary_id = Boundary_ID::Left;

    SECTION("Conversion to and from JSON") {
      json json_boundary_id = boundary_id;
      Boundary_ID boundary_id_from_json = json_boundary_id;
      CHECK(boundary_id_from_json == boundary_id);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << boundary_id;
      Boundary_ID boundary_id_from_text{};
      ss >> boundary_id_from_text;
      CHECK(boundary_id_from_text == boundary_id);
    }
  }

} // end of namespace lbm::core::testing
