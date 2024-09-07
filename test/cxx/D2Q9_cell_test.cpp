//
// ... LBM Bench header files
//
#include <lbm/D2Q9/Cell.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::D2Q9::testing {
  TEST_CASE("Cell") {
    Cell<double> cell{};

    SECTION("Conversion to and from JSON") {
      json json_cell = cell;
      Cell<double> cell_from_json = json_cell;
      CHECK(cell == cell_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << cell;
      Cell<double> cell_from_text{};
      ss >> cell_from_text;
      CHECK(cell == cell_from_text);
    }
  }

} // end of namespace lbm::D2Q9::testing
