//
// ... LBM Bench header files
//
#include <lbm/core/Boundary_Condition.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::core {
  TEST_CASE("Boundary Condition") {
    SECTION("Wall") {
      Boundary_Condition boundary_condition{Wall{Boundary_ID{Boundary::Lower, Boundary::NA}}};
      SECTION("Conversion to and from json") {
        json json_boundary_condition = boundary_condition;
        Boundary_Condition boundary_condition_from_json = json_boundary_condition;
        CHECK(boundary_condition_from_json == boundary_condition);
      }
      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << boundary_condition;
        Boundary_Condition boundary_condition_from_text{};
        ss >> boundary_condition_from_text;
        CHECK(boundary_condition_from_text == boundary_condition);
      }
    }

    SECTION("Symmetry") {
      Boundary_Condition boundary_condition{Symmetry{Boundary_ID{Boundary::NA, Boundary::Upper}}};
      SECTION("Conversion to and from json") {
        json json_boundary_condition = boundary_condition;
        std::cout << json_boundary_condition << std::endl;
        Boundary_Condition boundary_condition_from_json = json_boundary_condition;
        CHECK(boundary_condition_from_json == boundary_condition);
      }
      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << boundary_condition;
        Boundary_Condition boundary_condition_from_text{};
        ss >> boundary_condition_from_text;
        CHECK(boundary_condition_from_text == boundary_condition);
      }
    }

    SECTION("Inlet") {
      Boundary_Condition boundary_condition{Inlet{Boundary_ID{Boundary::NA, Boundary::Lower}, 3.0}};
      SECTION("Conversion to and from json") {
        json json_boundary_condition = boundary_condition;
        std::cout << json_boundary_condition << std::endl;
        Boundary_Condition boundary_condition_from_json = json_boundary_condition;
        CHECK(boundary_condition_from_json == boundary_condition);
      }
      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << boundary_condition;
        Boundary_Condition boundary_condition_from_text{};
        ss >> boundary_condition_from_text;
        CHECK(boundary_condition_from_text == boundary_condition);
      }
    }

    SECTION("Outlet") {
      Boundary_Condition boundary_condition{
          Outlet{Boundary_ID{Boundary::NA, Boundary::Lower}, 3.0}};
      SECTION("Conversion to and from json") {
        json json_boundary_condition = boundary_condition;
        Boundary_Condition boundary_condition_from_json = json_boundary_condition;
        CHECK(boundary_condition_from_json == boundary_condition);
      }
      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << boundary_condition;
        Boundary_Condition boundary_condition_from_text{};
        ss >> boundary_condition_from_text;
        CHECK(boundary_condition_from_text == boundary_condition);
      }
    }

    SECTION("Pressure Drop") {
      Boundary_Condition boundary_condition{
          Pressure_Drop{Boundary_ID{Boundary::Upper, Boundary::NA}, 3.0}};
      SECTION("Conversion to and from json") {
        json json_boundary_condition = boundary_condition;
        Boundary_Condition boundary_condition_from_json = json_boundary_condition;
        CHECK(boundary_condition_from_json == boundary_condition);
      }
      SECTION("Conversion to and from text") {
        std::stringstream ss{};
        ss << boundary_condition;
        Boundary_Condition boundary_condition_from_text{};
        ss >> boundary_condition_from_text;
        CHECK(boundary_condition_from_text == boundary_condition);
      }
    }
  }

} // end of namespace lbm::core
