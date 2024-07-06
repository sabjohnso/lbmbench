//
// ... LBM Bench header files
//
#include <lbm/core/Bounding_Box.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::core::testing {
  TEST_CASE("Bounding Box") {
    SECTION("2 Dimensional") {
      constexpr double width = 200.0;
      constexpr double height = 100.0;
      Bounding_Box bounding_box{width, height};

      SECTION("Values") {
        CHECK(bounding_box.size() == 2);
        CHECK(bounding_box[0] == width);
        CHECK(bounding_box[1] == height);
      }

      SECTION("Conversion to and from JSON") {
        json json_bounding_box = bounding_box;
        Bounding_Box bounding_box_from_json = json_bounding_box;
        CHECK(bounding_box == bounding_box_from_json);
      }

      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << bounding_box;
        Bounding_Box bounding_box_from_text{};
        ss >> bounding_box_from_text;
        CHECK(bounding_box == bounding_box_from_text);
      }
    }

    SECTION("3 Dimensional") {
      constexpr double width = 200.0;
      constexpr double height = 100.0;
      constexpr double depth = 150.0;
      Bounding_Box bounding_box{width, height, depth};

      SECTION("Values") {
        CHECK(bounding_box.size() == 3);
        CHECK(bounding_box[0] == width);
        CHECK(bounding_box[1] == height);
        CHECK(bounding_box[2] == depth);
      }

      SECTION("Conversion to and from JSON") {
        json json_bounding_box = bounding_box;
        Bounding_Box bounding_box_from_json = json_bounding_box;
        CHECK(bounding_box == bounding_box_from_json);
      }

      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << bounding_box;
        Bounding_Box bounding_box_from_text{};
        ss >> bounding_box_from_text;
        CHECK(bounding_box == bounding_box_from_text);
      }
    }
  }
} // end of namespace lbm::core::testing
