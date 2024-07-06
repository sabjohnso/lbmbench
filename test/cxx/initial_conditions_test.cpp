//
// ... LBM Bench header files
//
#include <lbm/core/Initial_Conditions.hpp>

//
// ... Testing header files
//
#include <catch2/catch_test_macros.hpp>

//
// ... Standard header files
//
#include <sstream>

namespace lbm::core::testing {

  TEST_CASE("2 Dimensional Uniform Density and Velocity") {
    using Coordinates = Initial_Conditions::Coordinates;
    using Velocity = Initial_Conditions::Velocity;
    constexpr double rho = 1.0;
    constexpr double vx = 2.0;
    constexpr double vy = 3.0;
    const Velocity v = {vx, vy};
    const Initial_Conditions ic{parse_json_expr(json(rho)),
                                {parse_json_expr(json(vx)), parse_json_expr(json(vy))}};

    constexpr double x1 = 4.0;
    constexpr double y1 = 5.0;
    const Coordinates coord1 = {x1, y1};

    constexpr double x2 = 6.0;
    constexpr double y2 = 7.0;
    const Coordinates coord2 = {x2, y2};

    SECTION("evaluation") {
      const auto rho1 = ic.density(coord1);
      const auto rho2 = ic.density(coord2);
      const auto v1 = ic.velocity(coord1);
      const auto v2 = ic.velocity(coord1);
      CHECK(rho1 == rho);
      CHECK(rho2 == rho);
      CHECK(v1[0] == v[0]);
      CHECK(v1[1] == v[1]);
      CHECK(v2[0] == v[0]);
      CHECK(v2[1] == v[1]);
    }

    SECTION("conversion to and from JSON") {
      json json_ic = ic;
      Initial_Conditions ic_from_json = ic;
      CHECK(ic == ic_from_json);
    }

    SECTION("conversion to and from text") {
      std::stringstream ss{};
      ss << ic;
      Initial_Conditions ic_from_text{};
      ss >> ic_from_text;
      CHECK(ic == ic_from_text);
    }
  }

} // end of namespace lbm::core::testing
