//
// ... LBM Bench header files
//
#include <lbmbench/utility.hpp>

//
// ... Third-party header files header files
//
#include <nlohmann/json.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

namespace lbm::tsting {

  TEST_CASE("Shape") {
    constexpr size_type a = 2;
    constexpr size_type b = 3;
    constexpr size_type c = 4;

    Shape shape{a, b, c};

    SECTION("element access") {
      CHECK(shape[0] == a);
      CHECK(shape[1] == b);
      CHECK(shape[2] == c);
    }

    SECTION("degree") { CHECK(shape.degree() == 3); }

    SECTION("total size") { CHECK(shape.total_size() == a * b * c); }

    SECTION("conversion to json") {
      nlohmann::json json_shape = shape;
      Shape<3> shape_from_json = json_shape;
      CHECK(shape_from_json == shape);
    }

    SECTION("conversion to text") {
      std::stringstream ss;
      ss << shape;
      Shape<3> shape_from_text;
      ss >> shape_from_text;
      CHECK(shape == shape_from_text);
    }
  }

} // end of namespace lbm::tsting
