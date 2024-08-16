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
    using enum Boundary_ID;
    SECTION("Wall") {
      Boundary_ID west = Left;
      Boundary_Condition boundary_condition{Wall{west}};

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

      SECTION("Boundary ID access") { CHECK(boundary_condition.boundary() == west); }
    }

    SECTION("Symmetry") {
      Boundary_ID north = Top;
      Boundary_Condition boundary_condition{Symmetry{north}};
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
      SECTION("Boundary ID access") { CHECK(boundary_condition.boundary() == north); }
    }

    SECTION("Inlet") {
      constexpr Boundary_ID south = Bottom;
      constexpr double density = 1.0;
      constexpr double speed = 3.0;
      Boundary_Condition boundary_condition{Inlet{south, density, speed}};
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
      SECTION("Boundary ID access") { CHECK(boundary_condition.boundary() == south); }
      SECTION("Density access") { CHECK(std::get<Inlet>(boundary_condition).density() == density); }
      SECTION("Speed access") { CHECK(std::get<Inlet>(boundary_condition).speed() == speed); }
    }

    SECTION("Outlet") {
      constexpr Boundary_ID south = Bottom;
      constexpr double density = 1.0;
      constexpr double speed = 3.0;
      Boundary_Condition boundary_condition{Outlet{south, density, speed}};

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
      SECTION("Boundary ID access") { CHECK(boundary_condition.boundary() == south); }
      SECTION("Density access") {
        CHECK(std::get<Outlet>(boundary_condition).density() == density);
      }
      SECTION("Speed access") { CHECK(std::get<Outlet>(boundary_condition).speed() == speed); }
    }

    SECTION("Pressure Drop") {
      Boundary_ID east = Right;
      Boundary_Condition boundary_condition{Pressure_Drop{east, 3.0}};
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
