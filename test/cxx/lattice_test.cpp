//
// ... LBM Bench header files
//
#include <lbm/core/Lattice.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::core::testing {
  TEST_CASE("2 Dimensional Lattice") {
    constexpr double width = 200.0;
    constexpr double height = 100.0;
    constexpr double lattice_spacing = 0.5;
    Lattice lattice{Bounding_Box{width, height}, lattice_spacing};

    SECTION("Values") {
      CHECK(lattice.size(0) == width / lattice_spacing);
      CHECK(lattice.size(1) == height / lattice_spacing);
      CHECK(lattice.size() == lattice.size(0) * lattice.size(1));
      CHECK(lattice.extent(0) == width);
      CHECK(lattice.extent(1) == height);
    }

    SECTION("Conversion to and from JSON") {
      json json_lattice = lattice;
      Lattice lattice_from_json = json_lattice;
      CHECK(lattice == lattice_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << lattice;
      Lattice lattice_from_text{};
      ss >> lattice_from_text;
      CHECK(lattice == lattice_from_text);
    }
  }

  TEST_CASE("3 Dimensional Lattice") {
    constexpr double width = 200.0;
    constexpr double height = 100.0;
    constexpr double depth = 150.0;
    constexpr double lattice_spacing = 0.5;
    Lattice lattice{Bounding_Box{width, height, depth}, lattice_spacing};

    SECTION("Values") {
      CHECK(lattice.size(0) == width / lattice_spacing);
      CHECK(lattice.size(1) == height / lattice_spacing);
      CHECK(lattice.size(2) == depth / lattice_spacing);
      CHECK(lattice.size() == lattice.size(0) * lattice.size(1) * lattice.size(2));
      CHECK(lattice.extent(0) == width);
      CHECK(lattice.extent(1) == height);
      CHECK(lattice.extent(2) == depth);
    }

    SECTION("Conversion to and from JSON") {
      json json_lattice = lattice;
      Lattice lattice_from_json = json_lattice;
      CHECK(lattice == lattice_from_json);
    }

    SECTION("Conversion to and from text") {
      std::stringstream ss{};
      ss << lattice;
      Lattice lattice_from_text{};
      ss >> lattice_from_text;
      CHECK(lattice == lattice_from_text);
    }
  }
} // end of namespace lbm::core::testing
